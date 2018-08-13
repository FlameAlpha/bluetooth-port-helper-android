#ifndef SPEEDDISPALY_H
#define SPEEDDISPALY_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPointF>
#include <QPainterPath>
#include "QMessageBox"
namespace Ui {
class Speeddispaly;
}

class Speeddispaly : public QWidget
{
    Q_OBJECT

public:
    explicit Speeddispaly(QWidget *parent = 0);
    ~Speeddispaly();

private slots:
    void displayspeed(QString strData);
    void on_Close_clicked();
    void show_clicked();
    void on_Clear_clicked();

    void on_spinBox_editingFinished();
    void on_spinBox_2_editingFinished();

    void on_pushButton_clicked();

signals:
    void data_change(QString string);
private:
    Ui::Speeddispaly *ui;
    QPainterPath *path;
    QPainterPath *path_other;
    QGraphicsScene *scene;
    QPointF *pointf;
    bool ON_OFF;
};

#endif // SPEEDDISPALY_H
