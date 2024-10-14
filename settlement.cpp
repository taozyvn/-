#include "settlement.h"
#include "ui_settlement.h"

Settlement::Settlement(int blockWidth,int mode,bool stars[3],QString objective[3],QWidget *parent) :
    QDialog(parent),mode(mode),
    ui(new Ui::Settlement)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);//设置为无边框
    resize(blockWidth*5,blockWidth*5*1.25);
    QLabel * objectiveLable[4];//字
    if(mode==0){
        this->setStyleSheet("border-image: url(:/map/stars.png);");
    }else if(mode==2){
        this->setStyleSheet("border-image: url(:/map/win-"+QString::number(4-((int)stars[0]+(int)stars[1]+(int)stars[2]))+".png);");
    }else{
        this->setStyleSheet("border-image: url(:/map/died.png);");
    }
    for(int i=0;i<3;i++){
        objectiveLable[i]= new QLabel(this);
        objectiveLable[i]->setText(objective[i]);
        box[i]=new QWidget(this);
        if(stars[i]){
            box[i]->setStyleSheet("border-image: url(:/map/true.png);background-color:none");
            objectiveLable[i]->setStyleSheet("background-color:none;border-image:none;font: "+QString::number(blockWidth/7.5)+"pt \"华康少女文字W5(P)\";color: rgb(0, 255, 0);");
        }else{
            box[i]->setStyleSheet("border-image: url(:/map/false.png);background-color:none");
            objectiveLable[i]->setStyleSheet("background-color:none;border-image:none;font: "+QString::number(blockWidth/7.5)+"pt \"华康少女文字W5(P)\";color: rgb(200, 50, 50);");
        }
        if(mode==0){
            box[i]->hide();
            objectiveLable[i]->move(blockWidth*1.5,blockWidth*((i*0.4)+3.4));
            objectiveLable[i]->setStyleSheet("background-color:none;border-image:none;font: "+QString::number(blockWidth/6)+"pt \"华康少女文字W5(P)\";color: rgb(0, 0, 0);");
        }else{
            objectiveLable[i]->move(blockWidth*1.2,blockWidth*((i*0.4)+3.4));
        }
        box[i]->resize(blockWidth/4,blockWidth/4);
        box[i]->move(blockWidth*3.5,blockWidth*((i*0.4)+3.4));
    }
    if(mode==0){
        objectiveLable[3]=new QLabel(this);
        objectiveLable[3]->setText("关卡目标");
        objectiveLable[3]->move(blockWidth*1.8,blockWidth*(2.9));
        objectiveLable[3]->setStyleSheet("background-color:none;border-image:none;font: "+QString::number(blockWidth/4.5)+"pt \"华康少女文字W5(P)\";color: rgb(0, 0, 0);");
    }
    ui->pushButton->resize(blockWidth,blockWidth/1.9);
    ui->pushButton->move(blockWidth*2.05,blockWidth*4.75);
}

Settlement::~Settlement()
{
    delete ui;
}
