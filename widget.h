#ifndef WIDGET_H
#define WIDGET_H
#include "levelinfo.h"
#include <MapArray.h>
#include <QWidget>
#include <HistoryIfo.h>
#include <enemys.h>
#include <QPushButton>
#include <tower.h>
#include <settlement.h>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
public:
    int timeNum=0;//计时器的时间
    int endTime=0;//出怪结束的时间方便出下一波怪
    int blockWidth=64;//图块边长
    int mola=30;//金币数
    int heart=5;//剩余生命值
    int waveNum=0;//当前波次
    int mode=0;//模式，0为开始界面，1为关卡选择，2为科技树，3为正式关卡
    bool stars[3]={true,true,true};//星星数
    QPoint clickedPlace;//被点击的位置
    QPushButton * icons[12];//12种按钮
    History history;//历史记录类，保存关卡进度以及科技树进度；
    Map map;//地图类，里面存放了每一关的地图信息
    LevelInfo * level;//记录敌人信息的类
    QVector<int> enemyNum;//当前存在的敌人数
    QVector<QVector<Enemy*>> enemy;//指向每一个敌人的数组
    Tower * tower;//存放塔的链表
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void checkButtonPlace(int x,int y);
    void initButton(int x,int y,int type);//0为中间，1为左上，2为上，3为左，4为右，5为左下，6为下，7为右下
    void win();//游戏胜利
    void died();//游戏失败
    void clearInfo();//擦除关卡内信息
    QPoint getBullet(const QPoint &p1, const QPoint &p2, double percentage);
public slots:
    void timeOut();
    void buttonClicked();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
