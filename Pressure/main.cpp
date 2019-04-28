#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<uint32_t>("uint32_t"); //注册该类型
    qRegisterMetaType<point>("point");
    qRegisterMetaType<uint16_t>("uint16_t");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
