#include "widget.h"
#include "ui_widget.h"
#include "QMessageBox"

static const QString serviceUuid("00001101-0000-1000-8000-00805F9B34FB");

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    localDevice = new QBluetoothLocalDevice();
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    Receive=new QByteArray();
    connect(discoveryAgent,
            SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this,
            SLOT(addBlueToothDevicesToList(QBluetoothDeviceInfo))
            );
    connect(ui->list,
            SIGNAL(itemActivated(QListWidgetItem*)),
            this,
            SLOT(itemActivated(QListWidgetItem*))
            );
    connect(socket,
            SIGNAL(readyRead()),
            this,
            SLOT(readBluetoothDataEvent())
            );
    connect(socket,
            SIGNAL(connected()),
            this,
            SLOT(bluetoothConnectedEvent())
            );
    connect(socket,
            SIGNAL(disconnected()),
            this,
            SLOT(bluetoothDisconnectedEvent())
            );
    ui->pushButton_2->setEnabled(false);
    if( localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff ) {
        ui->pushButton_openBluetooth->setEnabled(true);
        ui->pushButton_closeDevice->setEnabled(false);
    }else {
        ui->pushButton_openBluetooth->setEnabled(false);
        ui->pushButton_closeDevice->setEnabled(true);
    }

    if( localDevice->hostMode() == QBluetoothLocalDevice::HostDiscoverable ) {
        ui->checkBox_discoverable->setChecked(true);
    }else {
        ui->checkBox_discoverable->setChecked(false);
    }
    QMessageBox::information(this,tr("Help"),tr("data 0~800 为坐标的 -400~400 \n"
                                                "x坐标 从零开始每次加10个像素点\n"
                                                "y坐标 由所发数据 data决定 "));
}

Widget::~Widget()
{
    delete discoveryAgent;
    delete localDevice;
    delete socket;
    delete Receive;
    delete ui;
}

void Widget::on_pushButton_scan_clicked()
{

    discoveryAgent->start();
    ui->pushButton_scan->setEnabled(false);

}

void Widget::addBlueToothDevicesToList( const QBluetoothDeviceInfo &info )
{
    QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());

    QList<QListWidgetItem *> items = ui->list->findItems(label, Qt::MatchExactly);

    if (items.empty()) {
        QListWidgetItem *item = new QListWidgetItem(label);
        QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(info.address());
        if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )
            item->setTextColor(QColor(Qt::green));
        else
            item->setTextColor(QColor(Qt::black));
        ui->list->addItem(item);
    }

}


void Widget::on_pushButton_openBluetooth_clicked()
{
    localDevice->powerOn();
    ui->pushButton_closeDevice->setEnabled(true);
    ui->pushButton_openBluetooth->setEnabled(false);
    ui->pushButton_scan->setEnabled(true);
}


void Widget::on_pushButton_closeDevice_clicked()
{
    localDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
    ui->pushButton_closeDevice->setEnabled(false);
    ui->pushButton_openBluetooth->setEnabled(true);
    ui->pushButton_scan->setEnabled(false);
}

void Widget::itemActivated(QListWidgetItem *item)
{
    QString text = item->text();

    int index = text.indexOf(' ');

    if (index == -1)
        return;

    QBluetoothAddress address(text.left(index));
    QString name(text.mid(index + 1));
    QMessageBox::information(this,tr("Info"),tr("The device is connecting..."));
    socket->connectToService(address, QBluetoothUuid(serviceUuid) ,QIODevice::ReadWrite);

}


void Widget::readBluetoothDataEvent()
{
    QByteArray line = socket->readAll();
    if(!line.isEmpty()){
        Receive->append(line);
        if(Receive->contains('#')){
         QString  strData=*Receive;
            Receive->clear();
            ui->textBrowser_info->append(strData);
            emit data_change(strData);
        }
    }
}
void Widget::bluetoothConnectedEvent()
{
    QMessageBox::information(this,tr("Info"),tr("successful connection!"));
    ui->pushButton_2->setEnabled(true);
    emit show_display();
}

void Widget::bluetoothDisconnectedEvent()
{
    QMessageBox::information(this,tr("Info"),tr("successful disconnection!"));
}

void Widget::on_pushButton_disconnect_clicked()
{
    socket->disconnectFromService();
}

void Widget::send_data(QString string)
{
    QByteArray arrayData;
    arrayData = string.toUtf8();
    socket->write(arrayData);
}

void Widget::on_horizontalSlider_sliderMoved(int position)
{
    socket->write(QString::number(position).toUtf8());
}

void Widget::on_pushButton_clicked()
{
    QMessageBox::information(this,tr("About"),tr("PortHelper 3.0\n"
                                                 "Author: Flame\n"
                                                 "Based on Qt 5.8.0,Built on Jun 6 2017\n"
                                                 "Copyright 2017 Flame All rights reserved\n"
                                                 "\n"
                                                 "Welcome to weibo.com/u/5128367627"));
}

void Widget::on_pushButton_2_clicked()
{
    emit show_display();
}
