#ifndef SERALANALYSIS_H
#define SERALANALYSIS_H

#include <QObject>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class seralAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit seralAnalysis(QObject *parent = 0);
    void run();
    void setBusType(int type);
    float filter_x(float data);
    float filter_y(float data);
    float filter_z(float data);

signals:
    void sigGro(QString type ,float *gro);

public slots:
    void slotSeralRead();
    void slot_Receive_CanData( int CanCH,int id ,QByteArray datAry );
    void slotGyroRangeSet(float range);

public:
    void do_openSeral(QString PortName ,int crol);
    float gGyroSensitivity = (float)pow(2,16)/2/2000;

private:
    QSerialPort *gSerial;
    float SerialGro[3];

    //使用总线类型
    int BusType = 0; //0-串口  1-CAN

};

#endif // SERALANALYSIS_H
