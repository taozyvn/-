#include "tower.h"
#include "cmath"

#include <QDebug>
Tower::Tower(int type, QPoint place,int startTime)
{
    this->startTime=startTime;
    this->type=type;
    this->place=place;
    switch(type){
        case 1:
            break;
        case 2:
            price=20;
            fireSpeed=10;
            damage=20;
            range=3;
            break;
        case 3:
            break;
        case 4:
            price=40;
            fireSpeed=50;
            damage=250;
            range=5;
            break;
        case 5:
            price=30;
            fireSpeed=1000;
            damage=0;
            range=0;
            break;
        case 6:
            break;
        case 7:
            break;
    }
}

void Tower::Action(QVector<int>& enemyNum,QVector<QVector<Enemy *>>& enemy)
{
    bool hasEnemy=false;
    switch(type){
        case 1:
 
        case 2:
            if(this->enemy[0]!=-1){
                enemy[this->enemy[0]][this->enemy[1]]->bload-=damage;
            }
            for(int i=0;i<enemyNum.length();i++){//遍历寻找符合攻击条件的敌人
                for(int j=0;j<enemyNum[i];j++){
                    if(enemy[i][j]->bload<=0)continue;
                    if((double)((enemy[i][j]->place[0]-place.x()*20-10)*
                            (enemy[i][j]->place[0]-place.x()*20-10)+
                            (enemy[i][j]->place[1]-place.y()*20-10)*
                            (enemy[i][j]->place[1]-place.y()*20-10))/400<=range*range){//根据勾股定理算出距离
                        hasEnemy=true;
                        if(this->enemy[0]==-1){
                            this->enemy[0]=i;
                            this->enemy[1]=j;
                        }else if(enemy[this->enemy[0]][this->enemy[1]]->bload<0){
                            this->enemy[0]=i;
                            this->enemy[1]=j;
                        }else if(enemy[this->enemy[0]][this->enemy[1]]->mode<enemy[i][j]->mode){
                            this->enemy[0]=i;
                            this->enemy[1]=j;
                        }else if(enemy[this->enemy[0]][this->enemy[1]]->mode==enemy[i][j]->mode&&enemy[this->enemy[0]][this->enemy[1]]->place[2]<enemy[i][j]->place[2]){
                            this->enemy[0]=i;
                            this->enemy[1]=j;
                        }
                    }
                }
                if(!hasEnemy)this->enemy[0]=-1;
                if(this->enemy[0]!=-1){
                    angle =getAngle(place,enemy[this->enemy[0]][this->enemy[1]]->place[0],enemy[this->enemy[0]][this->enemy[1]]->place[1]);
                }
            }
        case 3:
            break;
        case 4:
        if(this->enemy[0]!=-1){
            enemy[this->enemy[0]][this->enemy[1]]->bload-=damage;
        }
        for(int i=0;i<enemyNum.length();i++){//遍历寻找符合攻击条件的敌人
            for(int j=0;j<enemyNum[i];j++){
                if(enemy[i][j]->bload<=0)continue;
                if((double)((enemy[i][j]->place[0]-place.x()*20-10)*
                        (enemy[i][j]->place[0]-place.x()*20-10)+
                        (enemy[i][j]->place[1]-place.y()*20-10)*
                        (enemy[i][j]->place[1]-place.y()*20-10))/400<=range*range){//根据勾股定理算出距离
                    hasEnemy=true;
                    if(this->enemy[0]==-1){
                        this->enemy[0]=i;
                        this->enemy[1]=j;
                    }else if(enemy[this->enemy[0]][this->enemy[1]]->bload<0){
                        this->enemy[0]=i;
                        this->enemy[1]=j;
                    }else if(enemy[this->enemy[0]][this->enemy[1]]->mode<enemy[i][j]->mode&&enemy[this->enemy[0]][this->enemy[1]]->place[2]<enemy[i][j]->place[2]){
                        this->enemy[0]=i;
                        this->enemy[1]=j;
                    }
                }
            }
            if(!hasEnemy)this->enemy[0]=-1;
            if(this->enemy[0]!=-1){
                angle =getAngle(place,enemy[this->enemy[0]][this->enemy[1]]->place[0],enemy[this->enemy[0]][this->enemy[1]]->place[1]);
            }
        }
            break;
        case 6:
            break;
        case 7:
            break;
    }
}

int Tower::getAngle(QPoint p1,double p3x,double p3y) {
    // 线段的终点 p2 的计算
    QPoint p2 = QPoint(p1.x() * 2, p1.y());
    // 从 p1 到 p2 的方向向量
    double dx1 = p2.x() - p1.x();
    double dy1 = p2.y() - p1.y();
    // 从 p1 到 p3 的方向向量
    double dx2 = p3x/20- p1.x()-0.5;
    double dy2 = p3y/20- p1.y()-0.5;
    // 计算两个角度（以弧度为单位）
    double angle1 = atan2(dy1, dx1); // p1 到 p2 的角度
    double angle2 = atan2(dy2, dx2); // p1 到 p3 的角度
    // 计算角度差，并转换为度
    double angleDifference = angle2 - angle1;
    angleDifference = angleDifference * 180 / M_PI; // 从弧度转换为度
    // 确保角度在 0-360 度范围内
    angleDifference = fmod(angleDifference + 360, 360);
    return angleDifference;
}

void Tower::levelUp()
{
    level++;
    switch (type) {
        case 2:
            damage*=1.5;
            fireSpeed-=1;
            range+=0.5;
            price*=2.5;
            break;
        case 4:
            damage*=1.5;
            fireSpeed-=5;
            range+=0.5;
            price*=2.5;
    }
}

