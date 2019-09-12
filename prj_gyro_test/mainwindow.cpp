#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "stdint.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Bus_Init();
}

void MainWindow::Bus_Init()
{
    //Find usb
    if(ui->cBox_seralSW->currentText() == "" || ui->cBox_seralSW->count() == 0)
    {
        //没有可用设备
        Can_search();
    }
    CanBus_init();

    //CAN默认参数
    CanInfo.deviceIdx = 0;
    CanInfo.CH = 0;
    CanInfo.rate = 0;
}

void MainWindow::Can_search()
{
    //CAN查找
    if (CanBusInterface::IsExist(0))
    {
        if(ui->cBox_seralSW->itemText(0) != "CAN")
        {
            ui->cBox_seralSW->insertItem(0, "CAN");
        }
        CAN_DEV_IDX = 0;
    }
    else
    {
        if(ui->cBox_seralSW->itemText(0) == "CAN")
        {
            ui->cBox_seralSW->removeItem(0);
        }
    }

    //查找可用的串口
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->cBox_seralSW->addItem(serial.portName());
            qDebug()<<" serial.portName() = "<<serial.portName();
            serial.close();
        }
    }
    //设置波特率下拉菜单默认显示第0项
    ui->cBox_seralSW->setCurrentIndex(0);

    //单线程管串口
    pThreadSeral = new QThread;
    connect(&gSeralAnalysis ,&seralAnalysis::sigGro,this ,&MainWindow::slotGetGro);

    //用轮询方式，需要转到线程跑while(1)
    gSeralAnalysis.moveToThread(pThreadSeral);
    connect(pThreadSeral ,&QThread::started,&gSeralAnalysis ,&seralAnalysis::run);
    connect(this ,&MainWindow::sig_SetGyroRange,&gSeralAnalysis ,&seralAnalysis::slotGyroRangeSet , Qt::QueuedConnection);
}


void MainWindow::CanBus_init()
{
    pThreadCan = new QThread;
    pCanBus = new CanBusInterface;
    pCanBus->moveToThread(pThreadCan);

    connect(pThreadCan , &QThread::started , pCanBus , &CanBusInterface::slotRun);//CAn线程启动，单独跑，不影响主进程
    //子线程解析
    connect(pCanBus , &CanBusInterface::sigReadDataFromCan , &gSeralAnalysis , &seralAnalysis::slot_Receive_CanData , Qt::QueuedConnection);
}

void MainWindow::slotGetGro(QString type ,float *gro)
{

    QString groStr = "";
    groStr.append(QString("deg/s = %1%2%3 \r\n")
                   //度/秒
                  .arg(QString::number(gro[0],'f',3),10,QLatin1Char(' ') )
                  .arg(QString::number(gro[1],'f',3),10,QLatin1Char(' ') )
                  .arg(QString::number(gro[2],'f',3),10,QLatin1Char(' ') )
            );

    if( type.left(1).contains("S") )
    {
        ui->tEdit_Gro->append(type.remove(0,1)+" "+groStr);

        //存文件
        if( SaveFlag )
        {
            //qDebug()<<"SaveFlag ="<<SaveFlag<<FrameTargetCount;
            qint64 SysTimerStr3 = QDateTime::currentDateTime().toMSecsSinceEpoch();
            QString OneFrame;

            OneFrame.append(QString("%1,%2,%3,%4\r\n")
                            .arg(QString::number((SysTimerStr3)))
                            .arg(QString::number(gro[0]))
                            .arg(QString::number(gro[1]))
                            .arg(QString::number(gro[2])) );
            rawFile->write(OneFrame.toLatin1());
            FrameTargetCount++;
            ui->pButtonSave->setText(QString::number(FrameTargetCount));
        }
    }
    else
    {
        ui->tEdit_log->append(type);
    }
}

MainWindow::~MainWindow()
{
    if( SaveFlag )
    {
        rawFile->close();
        delete rawFile;
        rawFile = nullptr;
    }

    delete ui;
}

void MainWindow::on_pButtonOpen_clicked()
{
    //设置量程
    float GyroRange = ui->cBox_gyroRange->currentText().toFloat();

    if( GyroRange > 0 && GyroRange <= 2000)
    {
        gSeralAnalysis.gGyroSensitivity = (float)pow(2,16)/2/GyroRange;
        //qDebug()<<GyroRange;
        DelayMSec(50);
    }

    if( ui->cBox_seralSW->currentText().contains("CAN"))
    {
        //设置总线类型
        gSeralAnalysis.setBusType(1);

        if(ui->pButtonOpen->text()== "Open")
        {
            //开始线程
            pThreadCan->start();

            //开始CAN
            if ( pCanBus->openCan(CanInfo.deviceIdx,CanInfo.CH,CanInfo.rate) == false){ return ;}
            ui->pButtonOpen->setText("Stop");
            pThreadSeral->start();
            ui->cBox_seralSW->setEnabled(false);
        }
        else
        {
            //关闭Can
            if ( pCanBus->closeCan(CanInfo.deviceIdx) == false){ return ;}
            ui->pButtonOpen->setText("Open");
            pThreadSeral->wait(10);
            pThreadSeral->exit(0);
            ui->cBox_seralSW->setEnabled(true);
        }
    }
    else
    {
        //设置总线类型
        gSeralAnalysis.setBusType(0);

        if(ui->pButtonOpen->text() == "Open")
        {
            gSeralAnalysis.do_openSeral(ui->cBox_seralSW->currentText(),1);
            ui->pButtonOpen->setText("Close");
            pThreadSeral->start();
            ui->cBox_seralSW->setEnabled(false);
        }
        else
        {
            gSeralAnalysis.do_openSeral(ui->cBox_seralSW->currentText(),0);
            ui->pButtonOpen->setText("Open");
            pThreadSeral->exit(0);
            ui->cBox_seralSW->setEnabled(true);
        }
    }
}

void MainWindow::DelayMSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::on_pButtonSave_clicked()
{
    QString FilePath = QDir::currentPath() + "/data/";
    QDir dir(FilePath);
    if(!dir.exists())
    {
        dir.mkpath(FilePath);
    }
    QString SysTimerStr3 = QDateTime::currentDateTime().toString("MM_dd_SS");
    QString TSaveFileName = ui->lEditFileName->text();
    QString FilePathAndName = FilePath + TSaveFileName + SysTimerStr3 + "_YawTateModuleData.csv";
    if(ui->pButtonSave->text() == "Save")
    {
        if (rawFile == nullptr)
        {
            rawFile = new QFile(FilePathAndName);
            if (!rawFile->open(QIODevice::WriteOnly | QIODevice::Truncate))
            {
                qDebug()<<"Save Error , OPen error!";
                return;
            }
        }
        SaveFlag = 1;
        ui->pButtonSave->setText("123");
    }
    else
    {
        rawFile->close();
        delete rawFile;
        rawFile = nullptr;
        ui->pButtonSave->setText("Save");
        SaveFlag = 0;
        FrameTargetCount = 0;
    }
}

void MainWindow::on_pButtonImport_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),QDir::currentPath() + "/data/",tr("Excel(*.csv)"));

    if(!(fileName.endsWith(".csv")))
    {
        return;
    }

    //显示文件名
    ui->lEditFileName->setText(fileName);
    qDebug()<<"ok";

    //读取所有文件
    QDir dir = QDir::current();
    QFile file(dir.filePath(fileName));
    if(!file.open(QIODevice::ReadOnly))
        qDebug()<<"OPEN FILE FAILED";
    QTextStream * out = new QTextStream(&file);//文本流
    allDataBuf = out->readAll().split("\r\n");
    //qDebug()<<allDataBuf.length()<<allDataBuf[0];
}




void MainWindow::on_cBoxFileProcess_clicked(bool checked)
{
    if( checked == true)
    {
        if(allDataBuf.isEmpty())
        {
            ui->cBoxFileProcess->setChecked(false);
            return;
        }
        //获取一包数据
        fileProcessState = 1;
        QStringList dataTemp = allDataBuf;
        allFrameCnt = dataTemp.length()-1;
        int FrameCnt = 0;
        QStringList OneFrame;
        //打开一个文件准备保存
        QString FilePath = QDir::currentPath() + "/data/";
        QDir dir(FilePath);
        if(!dir.exists()) {dir.mkpath(FilePath);}
        QString SysTimerStr = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
        QString FilePathAndName = FilePath + SysTimerStr + "_gyroProcessData.csv";
        ProFile = new QFile(FilePathAndName);
        if (!ProFile->open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qDebug()<<"Save Error , OPen error!";
            return;
        }
        //下面处理了直接保存
        QString SaveOneFrame,prodata[3];
        qDebug()<<"Process ing ~ ~ ~";
        float ProcessedValue[3];
        while(fileProcessState && FrameCnt < allFrameCnt)
        {
            OneFrame = allDataBuf[FrameCnt].split(",");
            FrameCnt++;
            //调用库处理
            //ProcessedValue[0] = gyroProcess(OneFrame[1].toFloat());
            ProcessedValue[1] = fabsf(gyroProcess(OneFrame[2].toFloat())) <= 0.5 ? 0 : gyroProcess(OneFrame[2].toFloat());
            //ProcessedValue[1] = fabsf(gyroProcess(OneFrame[2].toFloat())) <= 0.5 ? 0 : fabsf(gyroProcess(OneFrame[2].toFloat()));
            //ProcessedValue[2] = gyroProcess(OneFrame[2].toFloat());

            ProcessedValue[0] = OneFrame[1].toFloat();
//            ProcessedValue[1] = OneFrame[2].toFloat();
            ProcessedValue[2] = OneFrame[3].toFloat();

            //保存文件
            SaveOneFrame.append(QString("%1,%2,%3,%4\r\n")
                            .arg(OneFrame[0])
                            .arg(QString::number(ProcessedValue[0]))
                            .arg(QString::number(ProcessedValue[1]))
                            .arg(QString::number(ProcessedValue[2])) );
            ProFile->write(SaveOneFrame.toLatin1());

            SaveOneFrame.clear();
            //显示进度
            QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
        }
        qDebug()<<"Process End ~ ~ ~";
        //关闭文件
        ProFile->close();
        delete ProFile;
        ProFile = nullptr;
        ui->cBoxFileProcess->setChecked(false);
    }
    else
    {
        fileProcessState = 0;
    }
}

static int dV_HistBuf[DV_HIST_NUM];
static float Old_dv =  0;
static int dv_Cnt = 0;

float MainWindow::gyroProcess(float NewValue)
{
    //大于20 当成20处理
    int Idx = 0,maxIdx,i;
    if( fabsf(NewValue) > 20)
    {
        NewValue = 0;
    }

    dV_HistBuf[DV_HistIdxCalc(NewValue)]++;
    dv_Cnt++;

    if( dv_Cnt >= 10 )
    {
        //计算新值 -- 查找最多的
        //设定一个最低值
        for( maxIdx = i = 0;i < DV_HIST_NUM;i++)
        {
            if( dV_HistBuf[maxIdx] < dV_HistBuf[i])
            {
                maxIdx = i;
            }
        }

        //清空
        for( i = 0;i < DV_HIST_NUM;i++ )
        {
            dV_HistBuf[i] = 0;
            dv_Cnt = 0;
        }

        //新值
        if( fabsf(DV_HistValueCalc(maxIdx)-Old_dv) < 4 )
        {
            Old_dv = DV_HistValueCalc(maxIdx);
        }
    }
    return Old_dv;
}

