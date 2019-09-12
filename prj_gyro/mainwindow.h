#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "seralanalysis.h"
#include <qthread.h>
#include "qmath.h"
#include <QFile>
#include <QtConcurrent>
#include <QDir>
#include "canbusinterface.h"

//角度速度直方图
#define DV_HIST_NUM             400 + 1
#define DV_HistIdxCalc(dv)      (int)((dv * 10.0f) + 200)
#define DV_HistValueCalc(Idx)   (float)((Idx-200) / 10.0f)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //CAN
    void Bus_Init();
    void Can_search();
    void CanBus_init();
    float gyroProcess(float NewValue);
    void DelayMSec(unsigned int msec);

public slots:
    void slotGetGro(QString type, float *gro);

private slots:
    void on_pButtonOpen_clicked();
    void on_pButtonSave_clicked();
    void on_pButtonImport_clicked();
    void on_cBoxFileProcess_clicked(bool checked);

signals:
    void sig_SetGyroRange(float Range);

private:
    void do_openSeral();

private:
    Ui::MainWindow *ui;
    QThread * pThreadSeral;
    seralAnalysis gSeralAnalysis;

private:
    QFile *ProFile = nullptr;
    QFile *rawFile = nullptr;
    int FrameTargetCount = 0;
    int SaveFlag = 0;//0未保存 1保存

    //数据处理
    QStringList allDataBuf;
    int allFrameCnt = 0;
    int fileProcessState = 0; //不处理 1-处理中

    //CAN
    CanBusInterface * pCanBus;
    QThread * pThreadCan;
    int CAN_DEV_IDX ;
    //Can 设备信息
    _canInfo CanInfo;
};

#endif // MAINWINDOW_H
