#ifndef LEVELINFO_H
#define LEVELINFO_H

#include <QVector>


class LevelInfo
{
public:
    QVector<int> enemy;//每波的敌人数量
    QVector<int> enemyType;//每波的敌人种类
    QVector<int> enemyTime;//每波的两次出怪间隔
    int waveTime;//两个波次间的间隔
    int waveNum;//波次数量
    int level;
    QString objective[3];
    LevelInfo(int level);
    void getLevelInfo(int level);
};

#endif // LEVELINFO_H
