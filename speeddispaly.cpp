#include "speeddispaly.h"
#include "ui_speeddispaly.h"

Speeddispaly::Speeddispaly(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Speeddispaly)
{
    ui->setupUi(this);
    ON_OFF=true;
    scene=new QGraphicsScene;
    pointf=new QPointF(0,0);
    path=new QPainterPath(QPointF(0,0));
    path_other=new QPainterPath(QPointF(0,0));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    scene->addLine(0,0,1900,0);
    scene->addLine(0,-400,0,400);
    ui->graphicsView->update();
}

Speeddispaly::~Speeddispaly()
{
    delete ui;
    delete scene;
    delete pointf;
    delete path;
    delete path_other;
}

void Speeddispaly::displayspeed(QString strData)
{
    static int Na[2]={400,400},Nb[2]={400,400};
    QString string1=strData.mid(0,strData.indexOf('L'));
    QString string2=strData.mid(strData.indexOf('L')+1,strData.indexOf('R')-strData.indexOf('L')-1);
    if(strData.contains('L')&&strData.contains('R'))
    {  
    if(((Na[0]-string1.toInt())>200||(string1.toInt()-Na[0])>200)&&((Na[1]-string1.toInt())>200||(string1.toInt()-Na[1])>200)){
    }
    else{
        Na[1]=Na[0];
        Na[0]=string1.toInt();
    }
    if(((Nb[0]-string2.toInt())>200||(string2.toInt()-Nb[0])>200)&&((Nb[1]-string2.toInt())>200||(string2.toInt()-Nb[1])>200)){
    }
    else{
        Nb[1]=Nb[0];
        Nb[0]=string2.toInt();
    }
    scene->addLine(pointf->x()+950,0,pointf->x()+960,0);
    pointf->setX(pointf->x()+10);
    pointf->setY(-(Na[0]-400));  // 若以中心为中点则，输入值应当加400
    QPen pen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    path->lineTo(*pointf);
    scene->addPath(*path,pen);

    QPen pen_other(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    pointf->setY(-(Nb[0]-400));  // 若以中心为中点则，输入值应当加400
    path_other->lineTo(*pointf);
    scene->addPath(*path_other,pen_other);


    ui->graphicsView->centerOn(QPointF(pointf->x()+10,400));
    ui->graphicsView->update();
    }
    else
    {
        //QMessageBox::information(this,tr("Error"),tr("Data error!"));
    }
}

void Speeddispaly::show_clicked()
{
    this->show();
}
void Speeddispaly::on_Close_clicked()
{
    this->close();
}

void Speeddispaly::on_Clear_clicked()
{
    delete scene;
    delete pointf;
    delete path;
    delete path_other;

    scene=new QGraphicsScene;
    pointf=new QPointF(0,0);
    path=new QPainterPath(QPointF(0,0));
    path_other=new QPainterPath(QPointF(0,0));
    ui->graphicsView->setScene(scene);
    scene->addLine(0,0,1900,0);
    scene->addLine(0,-400,0,400);
    ui->graphicsView->update();
}

void Speeddispaly::on_spinBox_editingFinished()
{
    QString string=ui->spinBox->text();
    string.append("L#");
    emit data_change(string);
}

void Speeddispaly::on_spinBox_2_editingFinished()
{
    QString string=ui->spinBox_2->text();
    string.append("R#");
    emit data_change(string);
}

void Speeddispaly::on_pushButton_clicked()
{
    QString string;
    ON_OFF=!ON_OFF;
    string=(QString::number(ON_OFF));
    string.append("A#");
    emit data_change(string);
}
