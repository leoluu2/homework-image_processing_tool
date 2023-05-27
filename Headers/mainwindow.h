#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "showwindows.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_show_img_button_clicked();

    void on_cvt_button_clicked();

    void on_ud_flip_button_clicked();

    void on_lr_flip_button_clicked();

    void on_show_init_button_pressed();

    void on_show_init_button_released();

    void on_rename_button_clicked();

    void on_check_button_clicked();

    void on_save_button_clicked();

private:
    Ui::MainWindow *ui;
    ShowWindows page_show;

    //tool bar
    QToolBar *m_toolBar;
    QAction *m_openAction, * m_saveAction;

    //图像
    QImage image_init,image;
};
#endif // MAINWINDOW_H
