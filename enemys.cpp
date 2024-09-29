#include "enemys.h"

#include <QPainter>
Enemy::Enemy(QWidget *parents, QPoint place, int type, int waveNum, int blockWidth):QWidget(parents)
{
    this->place[0]=place.x()*20-10;
    this->place[1]=place.y()*20-10;
    this->place[2]=0;
    this->type=type;
    this->no=waveNum;
    switch (type) {
        case 1://绿色史莱姆，普通的
        bload=100;
        spead=2;
        break;
        case 2://蓝色史莱姆，强壮的，速度慢的
        bload=300;
        spead=3;
        break;
        case 3://紫色史莱姆，生命值特别高，速度特别慢
        bload=500;
        spead=5;
        break;
        case 4://红色史莱姆，缓慢恢复生命，速度慢
        bload=200;
        spead=3;
        break;
        case 5://黄色史莱姆，生命值特别低，速度特别快
        bload=50;
        spead=1;
        break;
    }
    if(type<=7){
        this->resize(blockWidth/3,blockWidth/3);
    }
    maxBload=bload;
}

void Enemy::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(diedTime==0){
        painter.drawPixmap(QRect(0,0,this->width(),this->height()),QPixmap(":/enemy/slime-1-"+QString::number(type)+".png"));
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::darkRed);
        painter.drawRect(QRect(0,0,this->width(),this->height()/5));
        //空血条
        painter.setBrush(Qt::black);
        painter.drawRect(QRect(this->width()*0.05,this->width()*0.05,this->width(),this->height()/7));
        //剩余血量
        painter.setBrush(Qt::red);
        painter.drawRect(QRect(this->width()*0.05,this->width()*0.05,this->width()*0.9*(double)bload/maxBload,this->height()/7));
    }else{
        diedTime-=3;
        painter.setOpacity((double)diedTime/100);//透明度为100%
        painter.drawPixmap(QRect(0,0,this->width(),this->height()),QPixmap(":/enemy/slime-1-"+QString::number(type)+".png"));
    }
}
void Enemy::run(Map map)
{
    if(bload<=0&&bload>-10000){
        diedTime=100;
        bload=-99999;
        stop=999999;
        emit died(type);
    }
    if(stop>0){
        stop--;
       return;
    }
    if(place[2]/20<map.road[mode].y()){
        place[2]++;
        switch(map.road[mode].x()){
            case 1:
            place[1]--;
            break;
            case 2:
            place[0]++;
            break;
            case 3:
            place[1]++;
            break;
            case 4:
            place[0]--;
            break;
        }
    }else{
        mode++;
        if(map.road[mode].x()==0){
            emit inHome(no);
            stop=999;
            bload=-10;
        }
        place[2]=0;
        run(map);
    }
}
