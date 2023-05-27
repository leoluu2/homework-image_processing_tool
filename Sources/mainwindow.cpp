
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QToolBar>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    page_show.show();

    auto f=[&](){
        this->show();
    };

    connect (&page_show,&ShowWindows::turnToMainwindows,this,f);

    //tool bar部分
    m_toolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea,m_toolBar);//创建工具栏
    m_openAction = ui->actionopen;
    m_toolBar->addAction(m_openAction);//open功能添加到toolBar
    m_saveAction = ui->actionsave;
    m_toolBar->addAction(m_saveAction);//save功能添加到toolBar

    //为什么connect槽函数会执行两次？？

    //connect(ui->show_img_button,&QPushButton::clicked,this,&MainWindow::on_show_img_button_clicked);
    //connect(ui->ud_flip_button,&QPushButton::clicked,this,&MainWindow::on_ud_flip_button_clicked);

    //显示原图,鼠标的左键
    //connect(ui->show_init_button,&QPushButton::pressed,this,&MainWindow::on_show_init_button_pressed);
    //connect(ui->show_init_button,&QPushButton::released,this,&MainWindow::on_show_init_button_released);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_show_img_button_clicked()
{
    //用文件夹打开
    QString filename=QFileDialog::getOpenFileName(this,
               tr("open img"),"",tr("Image Files (*.png *.jpg *.bmp)"));//""中间放的是指定的目录
    if(!filename.isEmpty()){
        image_init.load(filename);
        image.load(filename);//所有类型的图片都建议用Qimage打开,为了防止覆盖图片的时候重复创建image（这样容易内存泄漏），只创建一个，之后更改地址就好
        ui->show_img_label->setPixmap(QPixmap::fromImage(image));//Qlabel中提供了setPixmap,但没有setimage，所以需要转换

    }/*
    switch (image.format()) {
        case QImage::Format_Mono:
            qDebug("Image format: Mono");
            break;
        case QImage::Format_MonoLSB:
            qDebug("Image format: MonoLSB");
            break;
        case QImage::Format_Indexed8:
            qDebug("Image format: Indexed8");
            break;
        case QImage::Format_RGB32:
            qDebug("Image format: RGB32");
            break;
        case QImage::Format_ARGB32:
            qDebug("Image format: ARGB32");
            break;
        case QImage::Format_ARGB32_Premultiplied:
            qDebug("Image format: ARGB32_Premultiplied");
            break;
        case QImage::Format_RGB16:
            qDebug("Image format: RGB16");
            break;
        case QImage::Format_ARGB8565_Premultiplied:
            qDebug("Image format: ARGB8565_Premultiplied");
            break;
        case QImage::Format_RGB666:
            qDebug("Image format: RGB666");
            break;
        case QImage::Format_ARGB6666_Premultiplied:
            qDebug("Image format: ARGB6666_Premultiplied");
            break;
        case QImage::Format_RGB555:
            qDebug("Image format: RGB555");
            break;
        case QImage::Format_ARGB8555_Premultiplied:
            qDebug("Image format: ARGB8555_Premultiplied");
            break;
        case QImage::Format_RGB888:
            qDebug("Image format: RGB888");
            break;
        case QImage::Format_RGB444:
            qDebug("Image format: RGB444");
            break;
        case QImage::Format_ARGB4444_Premultiplied:
            qDebug("Image format: ARGB4444_Premultiplied");
            break;
        default:
            qDebug("Unknown image format");
            break;
        }*/

}

void MainWindow::on_cvt_button_clicked()
{
    image = image.convertToFormat(QImage::Format_Grayscale8);
    ui->show_img_label->setPixmap(QPixmap::fromImage(image));
    //因为要实现撤销等操作，所以应该还需要数据结构补充一下
}

void MainWindow::on_ud_flip_button_clicked()
{
    image = image.mirrored(false,true);
    ui->show_img_label->setPixmap(QPixmap::fromImage(image));
    //数据结构
}

void MainWindow::on_lr_flip_button_clicked()
{
    image = image.mirrored(true,false);
    ui->show_img_label->setPixmap(QPixmap::fromImage(image));
    //数据结构
}

void MainWindow::on_show_init_button_pressed()
{
    ui->show_img_label->setPixmap(QPixmap::fromImage(image_init));//长按展示原图
}

void MainWindow::on_show_init_button_released()
{
    ui->show_img_label->setPixmap(QPixmap::fromImage(image));//释放就展示之前的图片
}

void MainWindow::on_rename_button_clicked()
{

    QString newFileName = QInputDialog::getText(this, "图像重命名", "请输入新的图像名称:");
    if(newFileName.isEmpty()) return ;
    QString savePath = QFileDialog::getSaveFileName(this, "图片保存", newFileName, "Image Files (*.png *.jpg *.bmp)");
    if(savePath.isEmpty()) return ;
    image_init.save(savePath);
}

void MainWindow::on_check_button_clicked()
{

    //还不能很好的检查，要不就直接显示图片信息，分辨率，+rgb/argb

    if (image_init.format() == QImage::Format_RGBA8888) {
        QMessageBox::information(this, "Image format", "The image is in PNG format.");
    } else {
        QMessageBox::information(this, "Image format", "The image is not in PNG format.");
    }

}

void MainWindow::on_save_button_clicked()
{
    QString savePath = QFileDialog::getSaveFileName(this, "图片保存", "", "Image Files (*.png *.jpg *.bmp)");
    if(savePath.isEmpty()) return ;
    image.save(savePath);
}
