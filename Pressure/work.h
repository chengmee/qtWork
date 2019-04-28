#ifndef WORK_H
#define WORK_H

#include <QObject>
#include <QUdpSocket>
#include <argument.h>
#include <synchapi.h>
#include <QThread>
#include <QString>
#include <QtMath>
#include <QDebug>

class Work:public QObject
{
    Q_OBJECT

public:
    Work();

    void tx(uint16_t,int);

    void setData4(uint16_t,uint16_t,timestamp *,timestamp *,timestamp *,timestamp *,uint8_t,point);

    void setData2(uint16_t,uint16_t,timestamp *,timestamp *,uint8_t,point);

    void setData3(uint16_t,uint16_t,timestamp *,timestamp *,timestamp *,uint8_t,point);

    uint32_t getMainTime(point,point);

    uint32_t getSubTime(point,point,point);

    void ttime(int,uint8_t *);

public slots:

    void doWork(uint32_t,uint32_t,uint32_t,uint32_t,point,point,point,point,int,int,int,QString,ushort,uint16_t);

private:
    uint32_t stn1;
    uint32_t stn2;
    uint32_t stn3;
    uint32_t stn4;

    point s1;
    point s2;
    point s3;
    point s4;

    int stNum;

    int groupNum;
    int groupTagNum;

    int tagNum;

    QString ip;
    ushort port;
    QHostAddress address;

};

#endif // WORK_H
