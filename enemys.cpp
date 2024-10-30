#include "enemys.h"
#include <QPainter>
Enemy::Enemy(QPoint place, int type, int waveNum, int blockWidth)
{
    this->place[0]=place.x()*20-10;
    this->place[1]=place.y()*20-10;
    this->place[2]=0;
    this->type=type;
    this->no=waveNum;
    switch (((type-1)%7)+1) {
        case 1://绿色史莱姆，普通的
        bload=100;
        spead=2;
        break;
        case 2://蓝色史莱姆，强壮的，速度慢的
        bload=400;
        spead=3;
        break;
        case 3://紫色史莱姆，生命值特别高，速度特别慢
        bload=800;
        spead=5;
        break;
        case 4://红色史莱姆，生命值下降到一半时，速度提升
        bload=200;
        spead=3;
        break;
        case 5://黄色史莱姆，生命值特别低，速度特别快
        bload=50;
        spead=1;
        break;
        case 6://灰色史莱姆，生命值中等，速度慢，免疫控制
        bload =200;
        spead=3;
        break;
        case 7://粉色史莱姆，缓慢恢复生命，速度慢
        bload =300;
        spead=3;
    }
    bload+=bload*(int)(waveNum/100)/10;//血量随波次增长
    if(type>7){
        bload*=500;
        spead*=2;
        if(waveNum/100==0){
            bload*=3;
            spead*=3;
        }
    }
    maxBload=bload;
}


void Enemy::run(Map map)
{
    if(bload<=0&&bload>-10000){
        diedTime=100;
        bload=-99999;
        stop=9999999;
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
