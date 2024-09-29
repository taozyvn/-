#ifndef ENEMY_H
#define ENEMY_H

#include <QPoint>
#include <MapArray.h>
#include <QWidget>
class Enemy:public QWidget
{
    Q_OBJECT
public:
    int no;//编号
    int type;//种类
    int place[3];//位置
    int mode=0;//行走方向阶段
    int bload;//血量
    int maxBload;//满血血量，用于计算血条
    int spead=2;//速度
    int stop=0;//是否停止
    int diedTime=0;//死亡停滞时间
public:
    void run(Map map);//移动
    Enemy(QWidget* parents,QPoint place, int type, int no, int blockWidth);
private:
    void paintEvent(QPaintEvent *) override;
private: signals:
    void inHome(int no);//敌人到达信号
    void died(int type);
};

#endif // ENEMY_H
