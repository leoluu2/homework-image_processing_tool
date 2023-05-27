#ifndef SHOWWINDOWS_H
#define SHOWWINDOWS_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class ShowWindows;
}

class ShowWindows : public QWidget
{
    Q_OBJECT

public:
    explicit ShowWindows(QWidget *parent = nullptr);
    ~ShowWindows();


public slots:
    void time_upadate();

signals:
    void turnToMainwindows();

private slots:


    void on_pushButton_clicked();

private:
    Ui::ShowWindows *ui;
};

#endif // SHOWWINDOWS_H
