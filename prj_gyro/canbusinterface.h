#ifndef CANBUSINTERFACE_H
#define CANBUSINTERFACE_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QCoreApplication>
#include <QDateTime>
#include <QFile>
#include <QIODevice>
#include <QThread>
#include "ECanVci.h"

#define CAN_DEV_TYPE USBCAN2//USBCAN2
//#define CAN_DEV_IDX 0

#define CAN_REQ_UPGRADE_CMD_01 0x0001
#define CAN_DATA_UPGRADE_CMD_02 0x0002
#define CAN_CHECK_UPGRADE_CMD_03 0x0003
#define CAN_RESULT_UPGRADE_CMD_04 0x0004

typedef struct {
    quint16 id;
    quint8 dat[8];
    quint8 flag;
}_can_rec_struct;

typedef struct {
    int deviceIdx;
    int CH;
    int rate; //0 -- 500k ,1--1M
}_canInfo;

class CanBusInterface : public QObject
{
    Q_OBJECT
public:
    explicit CanBusInterface(QObject *parent = 0);
    ~CanBusInterface();

private:
    void buildCmdStruct(quint32 id, QByteArray dat , CAN_OBJ *frameinfo);
    bool CanControl(bool ctrlOPenCan, quint16 idx , quint16 CanCH, quint8 rate); //CanCH 是设备的CAN通道
    bool CanControl(bool ctrlOPenCan, quint16 idx);
    void clearbuf();
    void delay(int ms);
    void canTransmit(CAN_OBJ *frameinfo, int CanCH);
    void canReceive(int CanCH);
    void canReceive1(int CanCH);

public:
    void SetFlagCanReceive(bool CanRecv);
    static bool IsExist(int can_devIDX);
    void CanSend(int CanCH, quint32 id, QByteArray Ary);
    bool openCan(int Can_dev_idx, int CanCH, int Rate);
    bool closeCan(int Can_dev_idx);

signals:
    void sigErrorCode(quint16 err , QString txt);
    void sigReadDataFromCan( int CanCH , quint32 id , QByteArray datAry); //哪一路通道的数据

public slots:
    void slotRun();
    void slotStop();

private:
    _can_rec_struct can_rec_buf[1000];
    INIT_CONFIG init_config;
    //quint16 canindex;

public:
    //int CAN_DEV_IDX = 0;
    bool IsCanOpen;
    bool IsCanRecv;
    bool isRunning;
    //quint8 rate;
    _canInfo CanInfo;

    int sdfa = 0;
};

#endif // CANBUSINTERFACE_H
