#include "canbusinterface.h"

CanBusInterface::CanBusInterface(QObject *parent) : QObject(parent)
{
    //canindex = 0;
    //CAN_DEV_IDX = 0;
    IsCanOpen = false;
    IsCanRecv = false;
    //rate = 0;   //默认是500k
    memset(can_rec_buf , 0 , sizeof(can_rec_buf));
}

CanBusInterface::~CanBusInterface()
{
    IsCanOpen = false;
    IsCanRecv = false;
}

void CanBusInterface::canReceive(int CanCH) //CanCH Can通道 通道1或者 通道2
{

    QByteArray datAry;
    datAry.resize(8);
    //qDebug()<<"***************************"<<IsCanOpen<<CanCH;
    if( IsCanOpen == false ) {
        return;
    }
    //qDebug()<<"***************************";
    int len;
    int len_num;
    CAN_OBJ recFrame[10];
    len_num = GetReceiveNum(CAN_DEV_TYPE , CanInfo.deviceIdx , CanCH);
    len = Receive(CAN_DEV_TYPE , CanInfo.deviceIdx , CanCH , recFrame , 1 , 0);
    QCoreApplication::processEvents(QEventLoop::AllEvents , 100);

    if(len == 0) {
        return;
    }
    for(int i=0 ; i < len;i++)
    {
        quint32 canid = recFrame[i].ID;
        if(canid == 0)
        {
            continue;
        }

        datAry[0] = recFrame[i].Data[0];
        datAry[1] = recFrame[i].Data[1];
        datAry[2] = recFrame[i].Data[2];
        datAry[3] = recFrame[i].Data[3];
        datAry[4] = recFrame[i].Data[4];
        datAry[5] = recFrame[i].Data[5];
        datAry[6] = recFrame[i].Data[6];
        datAry[7] = recFrame[i].Data[7];

        emit sigReadDataFromCan(CanCH , canid ,datAry );
//        qDebug()<<canid;
    }
}

void CanBusInterface::canReceive1(int CanCH) //CanCH Can通道 通道1或者 通道2
{

    QByteArray datAry;
    datAry.resize(8);
    //qDebug()<<"***************************"<<IsCanOpen<<CanCH;
    if( IsCanOpen == false ) {
        return;
    }
    //qDebug()<<"***************************";
    int len;
    int len_num;
    CAN_OBJ recFrame[10];
    len_num = GetReceiveNum(CAN_DEV_TYPE , CanInfo.deviceIdx , CanCH);
    len = Receive(CAN_DEV_TYPE , CanInfo.deviceIdx , CanCH , recFrame , 1 , 0);
    QCoreApplication::processEvents(QEventLoop::AllEvents , 100);
    if( recFrame[0].ID == 0x5ff)
    qDebug()<<"***************************"<<IsCanOpen<<len<<CanCH<<recFrame[0].ID;

    if(len == 0) {
        return;
    }
    for(int i=0 ; i < len;i++)
    {
        quint32 canid = recFrame[i].ID;
        if(canid == 0)
        {
            continue;
        }

        datAry[0] = recFrame[i].Data[0];
        datAry[1] = recFrame[i].Data[1];
        datAry[2] = recFrame[i].Data[2];
        datAry[3] = recFrame[i].Data[3];
        datAry[4] = recFrame[i].Data[4];
        datAry[5] = recFrame[i].Data[5];
        datAry[6] = recFrame[i].Data[6];
        datAry[7] = recFrame[i].Data[7];

        emit sigReadDataFromCan(CanCH , canid ,datAry );
    }
}

void CanBusInterface::canTransmit(CAN_OBJ * frameinfo,int CanCH)
{
    if(IsCanOpen == false) {
        return;
    }
    int trycnt = 1;
    //char tmp[8];
    //memcpy(tmp , frameinfo->Data , 8);
    //QString str = QString("TX id=%1,dat=%2\n").arg(frameinfo->ID).arg(tmpAry.toHex().toStdString().c_str());
    //qDebug()<<str;
    frameinfo->SendType = 1; //不自动重复发送
    frameinfo->RemoteFlag = 0;
    frameinfo->ExternFlag = 0;
    frameinfo->DataLen = 8;

    while(trycnt--)
    {
        if(Transmit(CAN_DEV_TYPE , CanInfo.deviceIdx, CanCH , frameinfo , 1) != 1)
        {
            //qDebug()<<"can transmit error!\n";
        }
        else
        {
            break;
        }
    }

    //qDebug()<<"transmit dat end";
}

void CanBusInterface::delay(int ms)
{
    QDateTime cur=QDateTime::currentDateTime();

    while(cur.msecsTo(QDateTime::currentDateTime()) < ms)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents , 10);
    }
}

void CanBusInterface::buildCmdStruct(quint32 id,  QByteArray dat , CAN_OBJ * frameinfo)
{
    int len = dat.length();

    if(len != 8)   //有效长度为7
    {
        qDebug()<<"len != 7";
        dat.append(QByteArray((8-len),0x00));
        qDebug()<<"dat len = "<<dat.length();
    }

    frameinfo->SendType = 1; //不自动重复发送
    frameinfo->RemoteFlag = 0;
    frameinfo->ExternFlag = 0;
    frameinfo->DataLen = 8;
    frameinfo->ID = id;

    memcpy(frameinfo->Data, dat.data() , frameinfo->DataLen);
}

void CanBusInterface::clearbuf()
{
    CAN_OBJ recFrame[10];
    int len_left;
    int len,total;
    if(IsCanOpen == false)
    {
        return;
    }
    ClearBuffer(CAN_DEV_TYPE , CanInfo.deviceIdx , CanInfo.CH);
    len_left = GetReceiveNum(CAN_DEV_TYPE , CanInfo.deviceIdx , CanInfo.CH);
    total = 0;
    while(true)
    {
        len = Receive(CAN_DEV_TYPE , CanInfo.deviceIdx , CanInfo.CH , recFrame , 1 , 0);
        QCoreApplication::processEvents(QEventLoop::AllEvents , 10);
        total += len;
        if(total >= len_left)
        {
            return;
        }
    }
}

void CanBusInterface::slotRun()
{
    qDebug()<<"CAN BUS 1 interface thread run...";
    isRunning = true;
    while(isRunning)
    {
        if(IsCanRecv == true)
        {
            //canReceive(1);
            //canReceive1(1);
            canReceive(CanInfo.CH);
            //qDebug()<<IsCanRecv<<CanInfo.CH;
            //QCoreApplication::processEvents(QEventLoop::AllEvents , 10);
        }
        else
        {
            QThread::msleep(100);
        }
    }

    qDebug()<<"quit thread 1111111111!";
}

void CanBusInterface::slotStop()
{
    qDebug()<<"slot stop 11111111111";
    isRunning = false;
}

bool CanBusInterface::CanControl(bool ctrlOPenCan ,quint16 idx )
{
    if ( (ctrlOPenCan == false ) && ( IsCanOpen == true) ) {

        if(CloseDevice(CAN_DEV_TYPE , idx) == STATUS_OK)
        {
            qDebug()<<"close ok 1!";
            SetFlagCanReceive(false);
            IsCanOpen = ctrlOPenCan;
            return true;
        }
        else
        {
            qDebug()<<"close error!";
            return false;
        }
    }
}

bool CanBusInterface::CanControl(bool ctrlOPenCan ,quint16 idx ,quint16 CanCH ,quint8 rate)
{
    //先打开设备
    if( OpenDevice(CAN_DEV_TYPE , idx  , 0) == STATUS_ERR) {

        qDebug()<<"OpenDevice Error";
        return false;
    }

    if ( ctrlOPenCan && ( IsCanOpen == false) ) {

        qDebug()<<"will open CAN BUS";
        init_config.AccCode = 0;
        init_config.AccMask = 0xffffffff;
        init_config.Filter = 0;

        if(rate == 0) {
            init_config.Timing0 = 0;
            init_config.Timing1 = 0x1c;//500k
        }
        else {
            init_config.Timing0 = 0;
            init_config.Timing1 = 0x14;//1M速度  //0x1c
        }

        init_config.Mode = 0;

        //
        if(InitCAN(CAN_DEV_TYPE,idx,CanCH,&init_config) != STATUS_OK) {
            emit sigErrorCode(0xff , "init can fault!");
            qDebug()<<"InitCAN";
            return false;
        }
        if(StartCAN(CAN_DEV_TYPE,idx,CanCH) != STATUS_OK) {
            emit sigErrorCode(0xff , "start can fault!");
            qDebug()<<"StartCAN";
            return false;
        }

        SetFlagCanReceive(true);
    }

    //close
    if ( (ctrlOPenCan == false ) && ( IsCanOpen == true) )
    {
        qDebug()<<"will close CAN BUS";

        if(CloseDevice(CAN_DEV_TYPE ,idx) == STATUS_OK) {
            return true;
        }
        else {
            qDebug()<<"close error!";
            return false;
        }
        SetFlagCanReceive(false);
    }

    IsCanOpen = ctrlOPenCan;
    return true;
}

void CanBusInterface::SetFlagCanReceive(bool CanRecv)
{
    IsCanRecv = CanRecv;
}

void CanBusInterface::CanSend(int CanCH ,quint32 id, QByteArray Ary)
{
    CAN_OBJ frameinfo;
    qDebug()<<"CanSendAry=="<<QString::number(id,16)<<"->"<<Ary;
    buildCmdStruct(id , Ary , &frameinfo);
    canTransmit(&frameinfo,CanCH);
}

bool CanBusInterface::IsExist(int can_devIDX)
{
    if (OpenDevice(CAN_DEV_TYPE, can_devIDX, 0) == 1) {
        CloseDevice(CAN_DEV_TYPE, can_devIDX);
        return true;
    }
    else {
        return false;
    }
}

bool CanBusInterface::openCan(int Can_dev_idx,int CanCH,int Rate)  //Rate 0 是500K， 其他是1M
{
    //Can_dev_idx : 设备索引
    //CanCH     :设备的通道，0 或者 1
    //Rate      :波特率 0 是500K
    CanInfo.deviceIdx = Can_dev_idx;
    CanInfo.CH = CanCH;
    CanInfo.rate = Rate;


    if( CanControl(true,Can_dev_idx,CanCH,Rate) == STATUS_OK) {
        return STATUS_OK;
    }
    else{
        return STATUS_ERR;
    }

}

bool CanBusInterface::closeCan(int Can_dev_idx)
{
    if( CanControl(false,Can_dev_idx) == STATUS_OK ) {
        return STATUS_OK;
    }
    else{
        return STATUS_ERR;
    }
}
