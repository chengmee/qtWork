#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "argument.h"
#include "work.h"
#include <QString>
#include <QThreadPool>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void tx(uint16_t,int);

    void setData4(uint16_t,uint16_t,timestamp *,timestamp *,timestamp *,timestamp *,uint8_t,point);

    void setData2(uint16_t,uint16_t,timestamp *,timestamp *,uint8_t,point);

    void setData3(uint16_t,uint16_t,timestamp *,timestamp *,timestamp *,uint8_t,point);

    uint32_t getMainTime(point,point);

    uint32_t getSubTime(point,point,point);

    void ttime(int,uint8_t *);
private slots:
    void on_btn_begin_clicked();

    void on_btn_bound_clicked();

signals:

    void operate(uint32_t,uint32_t,uint32_t,uint32_t,point,point,point,point,int,int,int,QString,ushort,uint16_t);

private:
    Ui::MainWindow *ui;

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

    Work *worker[1000];
};


#endif // MAINWINDOW_H
