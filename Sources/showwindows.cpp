#include "showwindows.h"
#include "ui_showwindows.h"
#include "showwindows.h"
ShowWindows::ShowWindows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowWindows)
{
    ui->setupUi(this);

    //显示当前日期时间
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&ShowWindows::time_upadate);//注意和qt4.0之前版本区分开
    timer->start(1000);
}

ShowWindows::~ShowWindows()
{
    delete ui;
}



void ShowWindows::time_upadate(){
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
    this->ui->bj_time->setText(str);
}

void ShowWindows::on_pushButton_clicked()
{
    emit turnToMainwindows();
}
