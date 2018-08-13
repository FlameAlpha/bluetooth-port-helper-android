#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QtBluetooth/qbluetoothglobal.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothsocket.h>
#include <QGraphicsScene>
#include <QPointF>
#include <QPainterPath>

#define MAX_LENGTH 256

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_pushButton_scan_clicked();
    void addBlueToothDevicesToList(const QBluetoothDeviceInfo&);
    void on_pushButton_openBluetooth_clicked();
    void on_pushButton_closeDevice_clicked();
    void itemActivated(QListWidgetItem *item);
    void readBluetoothDataEvent();
    void bluetoothConnectedEvent();
    void bluetoothDisconnectedEvent();
    void on_pushButton_disconnect_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void send_data(QString string);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void data_change(QString strdata);
    void show_display();
private:
    Ui::Widget *ui;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;
    QBluetoothSocket *socket;
    QByteArray *Receive;
    unsigned char comBuffer[15];
    unsigned int  comCount;
    QString comStr;
};

#endif // WIDGET_H
