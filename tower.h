#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QVector>
#include <enemys.h>
class Tower
{
public:
    int type;//塔的种类
    int level;//塔的等级
    int angle=0;//炮口角度
    int fireSpeed;//攻击速度
    int damage;//攻击力
    int range;//攻击范围
    int startTime;//建造的时间
    int enemy[2]={0};//瞄准的敌人
    QPoint place;//塔的位置
    Tower * next=NULL;//链表的下一个节点
    Tower(){};//用于生成链表头
    Tower(int type,QPoint place,int startTiem);
    void Action(QVector<int> &enemyNum, QVector<QVector<Enemy *> > &enemy, int blockNum);
    void Action(int &mola);
    int getAngle(QPoint p1, double p3x, double p3y);
};

#endif // TOWER_H
