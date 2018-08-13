#ifndef MAIN_H
#define MAIN_H
#include <QApplication>
#include <QWidget>
#include "speeddispaly.h"
#include "widget.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    Speeddispaly speeddispaly;
    Widget widget;
    MainWindow(QWidget *parent = 0):QWidget(parent)
    {
        QObject::connect(&widget,SIGNAL(data_change(QString)),&speeddispaly,SLOT(displayspeed(QString)));
        QObject::connect(&widget,SIGNAL(show_display()),&speeddispaly,SLOT(show_clicked()));
        QObject::connect(&speeddispaly,SIGNAL(data_change(QString)),&widget,SLOT(send_data(QString)));
    }
    ~MainWindow(){
    }

};

#endif // MAIN_H
