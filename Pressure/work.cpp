#include "work.h"
#include "ui_mainwindow.h"


Work::Work()
{

}

void Work::doWork(uint32_t spn0,uint32_t spn1,uint32_t spn2,uint32_t spn3,point sp0,point sp1,point sp2,point sp3,int sn,int gn,int tn,QString ipstr,ushort pt,uint16_t ig)
{
    qDebug()<< "new thread!!!!"<<endl;
    stn1 = spn0;
    stn2 = spn1;
    stn3 = spn2;
    stn4 = spn3;

    s1 = sp0;
    s2 = sp1;
    s3 = sp2;
    s4 = sp3;

    stNum = sn;

    groupNum = gn;
    groupTagNum = tn;

    ip = ipstr;
    port = pt;
    address.setAddress(ip);

    int h = 700 / groupNum;

    tx(ig,h);
}

void Work::tx(uint16_t gn,int h)
{
    QUdpSocket *udpsocket;
    udpsocket = new QUdpSocket(this);


    timestamp *data1= new timestamp;
    timestamp *data2= new timestamp;
    timestamp *data3= new timestamp;
    timestamp *data4= new timestamp;

    uint8_t tim = 0x01;

    int d = 1000 / groupTagNum;
    uint16_t tag = 0;
    while(1)
    {
       for(int i = 1;i < groupTagNum;i++)
       {
           tim++;
           tag++;

           point p={double(148 + i*d),double(800 + groupNum*h), 140};
           int sleeptime = 1000 / groupTagNum;
           Sleep((DWORD)sleeptime);

           setData4(gn,tag,data1,data2,data3,data4,tim,p);
           udpsocket->writeDatagram((char *)data1,23,address,port);
           udpsocket->writeDatagram((char *)data2,23,address,port);
           udpsocket->writeDatagram((char *)data3,23,address,port);
           udpsocket->writeDatagram((char *)data4,23,address,port);
//           for(int i = 0 ;i<23 ;i++)
//           {
//               qDebug()<< ((unsigned char*)data1)[i] <<endl;
//           }
//            qDebug()<<"----------" <<endl;
//           qDebug()<< data2<<endl;
//           qDebug()<< data3<<endl;
//           qDebug()<< data4<<endl;

       }
    }
}


uint32_t Work::getSubTime(point s, point s1, point tag)
{
    double C = 29979245800;
    //uint8_t ad[4];
    double dis0 = sqrt((s1.x - tag.x)*(s1.x - tag.x) + (s1.y - tag.y)*(s1.y - tag.y) + (s1.z - tag.z)*(s1.z - tag.z));
    double dis = sqrt((s.x - tag.x)*(s.x - tag.x) + (s.y - tag.y)*(s.y - tag.y) + (s.z - tag.z)*(s.z - tag.z));
    double dss = sqrt((s1.x - s.x)*(s1.x - s.x) + (s1.y - s.y)*(s1.y - s.y) + (s1.z - s.z)*(s1.z - s.z));
    double ti = dis0 * 2 / C + (dis - dis0 - dss) / C  + 0.00000000112961461268 + 0.00050025463366155432;
    int bi = int(ti / 15.65e-12);
    uint32_t mm = (uint32_t)bi;
    return mm;
}

uint32_t Work::getMainTime(point s1, point tag)
{
    double C = 29979245800;
    double dis = sqrt((s1.x - tag.x)*(s1.x - tag.x) + (s1.y - tag.y)*(s1.y - tag.y) + (s1.z - tag.z)*(s1.z - tag.z));
    double ti = dis * 2 / C + 0.00050025463366155432;
    int bi =int(ti / 15.65e-12);
    uint32_t mm = (uint32_t)bi;
    return mm;
}

void Work::ttime(int time, uint8_t *t)
{
    t[0] = (uint8_t)(time >> 24);
     //time /= 256;
    t[1] = (uint8_t)(time >> 16);
     //time /= 256;
    t[2] = (uint8_t)(time >> 8);
     //time /= 256;
    t[3] = (uint8_t)(time);
}

void Work::setData4(uint16_t groupNum, uint16_t tagNum, timestamp *st0, timestamp *st1, timestamp *st2, timestamp *st3, uint8_t timeNum, point p)
{

    st0->t = getMainTime(s1,p) + unsigned(rand() % 50);
    st1->t = getSubTime(s2,s1,p) + unsigned(rand() % 50);
    st2->t = getSubTime(s3,s1,p) + unsigned(rand() % 50);
    st3->t = getSubTime(s4,s1,p) + unsigned(rand() % 50);

    st0->head = 0x23;
    st0->key = 0x48;
    st0->timeNum = timeNum;
    st0->group = groupNum;
    st0->tagNum = (groupNum<<16) + tagNum;
    st0->stNum = stn1;
    st0->state = 0x22;
    st0->th = 0;
    st0->heart = 0x58;
    st0->pow = 0x35;
    st0->end = 0x0d0a;

    st1->head = 0x23;
    st1->key = 0x48;
    st1->timeNum = timeNum;
    st1->group = groupNum;
    st1->tagNum = (groupNum<<16) + tagNum;
    st1->stNum = stn2;
    st1->state = 0x22;
    st1->th = 0;
    st1->heart = 0x58;
    st1->pow = 0x35;
    st1->end = 0x0d0a;

    st2->head = 0x23;
    st2->key = 0x48;
    st2->timeNum = timeNum;
    st2->group = groupNum;
    st2->tagNum = (groupNum<<16) + tagNum;
    st2->stNum = stn3;
    st2->state = 0x22;
    st2->th = 0;
    st2->heart = 0x58;
    st2->pow = 0x35;
    st2->end = 0x0d0a;

    st3->head = 0x23;
    st3->key = 0x48;
    st3->timeNum = timeNum;
    st3->group = groupNum;
    st3->tagNum = (groupNum<<16) + tagNum;
    st3->stNum = stn4;
    st3->state = 0x22;
    st3->th = 0;
    st3->heart = 0x58;
    st3->pow = 0x35;
    st3->end = 0x0d0a;

}

void Work::setData3(uint16_t groupNum, uint16_t tagNum, timestamp *st0, timestamp *st1, timestamp *st2, uint8_t timeNum, point p)
{
    st0->t = getMainTime(s1,p) + unsigned(rand() % 50);
    st1->t = getSubTime(s2,s1,p) + unsigned(rand() % 50);
    st2->t = getSubTime(s3,s1,p) + unsigned(rand() % 50);

    st0->head = 0x23;
    st0->key = 0x50;
    st0->timeNum = timeNum;
    st0->group = groupNum;
    st0->tagNum = (groupNum<<16) + tagNum;
    st0->stNum = stn1;
    st0->state = 0x22;
    st0->th = 0;
    st0->heart = 0x58;
    st0->pow = 0x35;
    st0->end = 0x0d0a;

    st1->head = 0x23;
    st1->key = 0x50;
    st1->timeNum = timeNum;
    st1->group = groupNum;
    st1->tagNum = (groupNum<<16) + tagNum;
    st1->stNum = stn2;
    st1->state = 0x22;
    st1->th = 0;
    st1->heart = 0x58;
    st1->pow = 0x35;
    st1->end = 0x0d0a;

    st2->head = 0x23;
    st2->key = 0x50;
    st2->timeNum = timeNum;
    st2->group = groupNum;
    st2->tagNum = (groupNum<<16) + tagNum;
    st2->stNum = stn3;
    st2->state = 0x22;
    st2->th = 0;
    st2->heart = 0x58;
    st2->pow = 0x35;
    st2->end = 0x0d0a;
}

void Work::setData2(uint16_t groupNum, uint16_t tagNum, timestamp *st0, timestamp *st1, uint8_t timeNum, point p)
{
    st0->t = getMainTime(s1,p) + unsigned(rand() % 50);
    st1->t = getSubTime(s2,s1,p) + unsigned(rand() % 50);

    st0->head = 0x23;
    st0->key = 0x50;
    st0->timeNum = timeNum;
    st0->group = groupNum;
    st0->tagNum = (groupNum<<16) + tagNum;
    st0->stNum = stn1;
    st0->state = 0x22;
    st0->th = 0;
    st0->heart = 0x58;
    st0->pow = 0x35;
    st0->end = 0x0d0a;

    st1->head = 0x23;
    st1->key = 0x50;
    st1->timeNum = timeNum;
    st1->group = groupNum;
    st1->tagNum = (groupNum<<16) + tagNum;
    st1->stNum = stn2;
    st1->state = 0x22;
    st1->th = 0;
    st1->heart = 0x58;
    st1->pow = 0x35;
    st1->end = 0x0d0a;

}
