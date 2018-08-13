#include "widget.h"
#include <QApplication>
#include <qscreen.h>
#include "QTextCodec"
#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
    MainWindow mainwindow;
    mainwindow.widget.show();
    return a.exec();
}
