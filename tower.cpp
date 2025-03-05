#include "tower.h"
#include "cmath"

#include <QDebug>
Tower::Tower(int type, QPoint place, int startTime,int towerLevelNum)
{
    this->startTime=startTime;
    this->type=type;
    this->place=place;
    switch(type){
        case 1:
            break;
        case 2://风元素塔数值
            price=20;
            fireSpeed=15-int(towerLevelNum%100/10);
            damage=30+int(towerLevelNum%10);
            range=3+double(int(towerLevelNum/100))/2;
            break;
        case 3:
            break;
        case 4://雷元素塔数值
            price=40;
            fireSpeed=75-int(towerLevelNum%100/10);
            damage=300+int(towerLevelNum%10);
            range=5+double(int(towerLevelNum/100))/2;
            break;
        case 5://岩元素塔数值
            price=30;
            fireSpeed=100000;
            damage=0;
            range=0;
            break;
        case 6:
            break;
        case 7:
            break;
    }
}

//QString names[21]={
//    "火元素塔伤害提升","火元素塔攻速提升","火元素塔范围提升",
//    "风元素塔伤害提升","风元素塔攻速提升","风元素塔范围提升",
//    "冰元素塔伤害提升","冰元素塔攻速提升","冰元素塔范围提升",
//    "雷元素塔伤害提升","雷元素塔攻速提升","雷元素塔范围提升",
//    "岩元素塔价格降低","初始摩拉数增加10","获得的摩拉增加5%",
//    "水元素塔伤害提升","水元素塔减速提升","水元素塔范围提升",
//    "草元素塔伤害提升","草元素塔伤害提升","草元素塔伤害提升"};

void Tower::Action(QVector<int>& enemyNum,QVector<QVector<Enemy *>>& enemy)
{
    bool hasEnemy=false;
    switch(type){
        case 1:
 
        case 2:case 4://风元素塔和雷元素塔的攻击
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
        case 2://风元素塔升级
            damage*=1.75;
            fireSpeed-=1;
            range+=0.5;
            price*=2.5;
            break;
        case 4://雷元素塔升级
            damage*=1.75;
            fireSpeed-=5;
            range+=0.5;
            price*=2.5;
            break;
        case 5:
            price*=2.5;
    }
}
