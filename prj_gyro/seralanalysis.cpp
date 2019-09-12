#include "seralanalysis.h"
#include "stdint.h"

seralAnalysis::seralAnalysis(QObject *parent) : QObject(parent)
{
    gSerial = new QSerialPort;

    gSerial->setBaudRate(QSerialPort::Baud115200);//设置波特率为115200
    gSerial->setDataBits(QSerialPort::Data8);
    gSerial->setParity(QSerialPort::NoParity);//设置校验位
    gSerial->setStopBits(QSerialPort::OneStop);//停止位设置为1
    gSerial->setFlowControl(QSerialPort::NoFlowControl);//设置为无流控制
    //connect(gSerial,&QSerialPort::readyRead,this,&seralAnalysis::slotSeralRead);


}

void seralAnalysis::do_openSeral(QString PortName, int crol)
{
    gSerial->setPortName(PortName);
    if( crol == 0)
    {
        gSerial->close();
    }
    else
    {
        gSerial->open(QIODevice::ReadWrite);
    }
}

void seralAnalysis::run()
{
#if 1
    qDebug()<<"seralAnalysis running"<<gGyroSensitivity;
    QByteArray buf;
    while(1 && BusType == 0)
    {
        buf.clear();
        if( !gSerial->isOpen() ){continue;}
        buf = gSerial->readAll();

        if( buf.isEmpty() )
        {
            continue;
        }

        QByteArrayList bufList = buf.split('Z');
        bufList.removeAll("");
        //qDebug()<<"==="<<bufList<<"\r\n"<<buf;
        int i = 0, j = 0;

        while(bufList.length())
        {
            QByteArray ArrayTemp = bufList.first();
            char *ptr = (char *)ArrayTemp.data();
            //查看头或者长度是否ok
            if( ptr[0] != 0x02 || ptr[1] != 0x06 || ArrayTemp.length() != 9)
            {
                bufList.removeFirst();
                continue;
            }
            //校验是否通过
            uint8_t checkSum = ptr[2] + ptr[3] + ptr[4] + ptr[5] + ptr[6] + ptr[7];
            if( checkSum != (uint8_t)ptr[8])
            {
                bufList.removeFirst();
                continue;
            }
            //解析
            //qDebug()<<"OKOK =="<<ArrayTemp;

            SerialGro[0] = (float)(ptr[2] << 8 | ptr[3]) / gGyroSensitivity;
            SerialGro[1] = (float)(ptr[4] << 8 | ptr[5]) / gGyroSensitivity;
            SerialGro[2] = (float)(ptr[6] << 8 | ptr[7]) /  gGyroSensitivity;

            //滤波
            //SerialGro[2] = filter_z(SerialGro[2]);

            QString groStr = "";
            groStr.append(QString("%1  %2  %3 \r\n")
                          .arg(QString::number(SerialGro[0]),20,QLatin1Char(' ') )
                          .arg(QString::number(SerialGro[1]),20,QLatin1Char(' ') )
                          .arg(QString::number(SerialGro[2]),20,QLatin1Char(' ') )

                          );
            emit sigGro("SPHY_Serial",SerialGro);

            bufList.removeFirst();
        }

    }
    qDebug()<<"seralAnalysis End";
#endif
}

void seralAnalysis::slotSeralRead()
{
    QByteArray buf;
    char *datepre;
    buf = gSerial->readAll();

    //量程
    //float sensitivity = (float)pow(2,16)/2/250;
    qDebug()<<gGyroSensitivity;
    if( buf.size() == 11)
    {
        char *ptr = (char *)buf.data();

        //解析 角度/s
        if( ptr[2] == 0x02 && ptr[3] == 0x06)
        {
            SerialGro[0] = (float)(ptr[4] << 8 | ptr[5]) / gGyroSensitivity;
            SerialGro[1] = (float)(ptr[6] << 8 | ptr[7]) / gGyroSensitivity;
            SerialGro[2] = (float)(ptr[8] << 8 | ptr[9]) / gGyroSensitivity;

            QString groStr = "";
            groStr.append(QString("%1  %2  %3 \r\n")
                          .arg(QString::number(SerialGro[0]),20,QLatin1Char(' ') )
                          .arg(QString::number(SerialGro[1]),20,QLatin1Char(' ') )
                          .arg(QString::number(SerialGro[2]),20,QLatin1Char(' ') )

                          );
            emit sigGro("0",SerialGro);
            //qDebug()<<SerialGro[0];

        }
    }
}

void seralAnalysis::slotGyroRangeSet(float range)
{
    qDebug()<<"sensitivity = "<<gGyroSensitivity;
    gGyroSensitivity = range;
}

//CAN
void seralAnalysis::slot_Receive_CanData( int CanCH,int id ,QByteArray datAry )
{
    //qDebug()<<CanCH<<id<<datAry;
    if( id == 0x505 ) //戴世陀螺仪
    {
        unsigned char *p = (unsigned char *)(datAry.data());
        int16_t dat;
        float gyro[3];
        //x
        dat = (int16_t)(p[1] << 8 | p[0]);
        gyro[0] = (float)(dat * 0.01f);

        //y
        dat = (int16_t)(p[3] << 8 | p[2]);
        gyro[1] = (float)(dat * 0.01f);

        //z
        dat = (int16_t)(p[5] << 8 | p[4]);
        gyro[2] = (float)(dat * 0.01f);

        QString strTemp;
        strTemp.append(QString("CAN gyro =%1\t%2\t%3")
                       .arg(gyro[0],8)
                       .arg(gyro[1],8)
                       .arg(gyro[2],8)
                       );
        emit sigGro("SDai Shi",gyro);
        emit sigGro(datAry.toHex() +"\t"+ strTemp,gyro);
    }

    if( id == 0x3F6 ) //PHY
    {
        unsigned char *p = (unsigned char *)(datAry.data());
        int16_t dat;
        float YawRate[3]={0,0,0};
        //x
        dat = p[1] << 8 | p[0];
        YawRate[0] = (float)(dat/100.0f);

        //y
        dat = p[3] << 8 | p[2];
        YawRate[1] = (float)(dat/100.0f);

        //z
        dat = p[5] << 8 | p[4];
        YawRate[2] = (float)(dat/100.0f);

        qDebug()<<"YawRateDec = "<<YawRate[0]<<YawRate[1]<<YawRate[2];

        emit sigGro("SPHY-1",YawRate);
    }

    if( id == 0x3F7 ) //
    {
        unsigned char *p = (unsigned char *)(datAry.data());
        int16_t dat;
        float YawRate[3]={0,0,0};
        //x
        dat = p[1] << 8 | p[0];
        YawRate[0] = (float)(dat/100.0f);

        //y
        dat = p[3] << 8 | p[2];
        YawRate[1] = (float)(dat/100.0f);

        //z
        dat = p[5] << 8 | p[4];
        YawRate[2] = (float)(dat/100.0f);

        qDebug()<<"YawRateDec = "<<YawRate[0]<<YawRate[1]<<YawRate[2];

        emit sigGro("SPHY-2",YawRate);
    }
}

float seralAnalysis::filter_x(float data)
{
    static float a = 0.01;
    static float last_data = 0.0f;
    data = a * data  + (1.0f - a) * last_data;

    last_data = data;

    return data;
}
float seralAnalysis::filter_y(float data)
{
    static float a = 0.01;
    static float last_data = 0.0f;
    data = a * data  + (1.0f - a) * last_data;

    last_data = data;

    return data;
}
float seralAnalysis::filter_z(float data)
{
    static float a = 0.01;
    static float last_data = 0.0f;
    data = a * data  + (1.0f - a) * last_data;

    last_data = data;

    return data;
}


void seralAnalysis::setBusType(int type)
{
    BusType = type;
}
