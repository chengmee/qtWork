#ifndef ARGUMENT_H
#define ARGUMENT_H
#include <QObject>
struct timestamp {
    uint8_t head;   //23
    uint8_t key;    //48
    uint8_t timeNum;//
    uint16_t group; //00 01
    uint32_t tagNum;//00 00 00 02
    uint32_t stNum; //ff ff ff ff
    uint8_t state;  //22
    uint8_t th;     //00
    uint32_t t;   //time
    uint8_t heart;  //58
    uint8_t pow;    //35
    uint16_t end; //0d 0a
};
struct point {
    double x;
    double y;
    double z;
};

#endif // ARGUMENT_H
