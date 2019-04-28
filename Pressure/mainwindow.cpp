#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_begin_clicked()
{
    // 线程
    //int h = 700 / (groupNum+1);
    uint16_t ig = 0;
    for(int i = 1;i<=groupNum;i++)
    {
        QThread workerThread;

        //qDebug()<< "for 1!!!!"<<endl;
//        Work *worker = new Work;

        worker[i] = new Work();

        worker[i]->moveToThread(&workerThread);
        //信号发射后启动线程
        connect(this,SIGNAL(operate(uint32_t,uint32_t,uint32_t,uint32_t,point,point,point,point,int,int,int,QString,ushort,uint16_t)),worker[i],SLOT(doWork(uint32_t,uint32_t,uint32_t,uint32_t,point,point,point,point,int,int,int,QString,ushort,uint16_t)),Qt::UniqueConnection);
        //线程结束时销毁
        connect(&workerThread,&QThread::finished,worker[i],&QObject::deleteLater);

        workerThread.start();
        ig++;
        //qDebug()<< "for 2!!!!"<<endl;
        emit operate(stn1,stn2,stn3,stn4,s1,s2,s3,s4,stNum,groupNum,groupTagNum,ip,port,ig);

        workerThread.wait();
    }

}


void MainWindow::on_btn_bound_clicked()
{
    stNum = this->ui->comboBox->currentText().toInt();

    groupNum = this->ui->group_Num->text().toInt();
    groupTagNum = this->ui->group_Tag_Num->text().toInt();
    tagNum = groupNum * groupTagNum;

    ip = this->ui->lineEdit_ip->text();
    port = this->ui->lineEdit_port->text().toUShort();
    address.setAddress(ip);

    bool OK;
    stn1 = this->ui->stNum1->text().toUInt(&OK,16);
    stn2 = this->ui->stNum2->text().toUInt(&OK,16);

    s1.x = this->ui->s1_x->text().toDouble();
    s1.y = this->ui->s1_y->text().toDouble();
    s1.z = this->ui->s1_z->text().toDouble();

    s2.x = this->ui->s2_x->text().toDouble();
    s2.y = this->ui->s2_y->text().toDouble();
    s2.z = this->ui->s2_z->text().toDouble();


    if(stNum > 2)
    {
        stn3 = this->ui->stNum3->text().toUInt(&OK,16);

        s3.x = this->ui->s3_x->text().toDouble();
        s3.y = this->ui->s3_y->text().toDouble();
        s3.z = this->ui->s3_z->text().toDouble();
    }
    if(stNum > 3)
    {
        stn4 = this->ui->stNum4->text().toUInt(&OK,16);

        s4.x = this->ui->s4_x->text().toDouble();
        s4.y = this->ui->s4_y->text().toDouble();
        s4.z = this->ui->s4_z->text().toDouble();
    }
}

