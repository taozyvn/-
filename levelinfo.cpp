#include "levelinfo.h"

LevelInfo::LevelInfo(int level)
{
    this->level=level;
    getLevelInfo(level);
}

void LevelInfo::getLevelInfo(int level)
{
    objective[0]="不要损失生命值";
    switch (level) {
        case 1:
        objective[1]="不砍伐任何树木";
        objective[2]="不使用岩元素塔";
        waveNum=5;
        enemyType.resize(waveNum);
        enemyTime.resize(waveNum);
        enemy.resize(waveNum);
        for(int i=0;i<5;i++){
            enemy[i]=5+i*2;
            enemyType[i]=1;
            enemyTime[i]=15;
        }
        enemyType[4]=2;
        enemyTime[4]=20;
        waveTime=5;

        break;
        case 2:
        break;
    }
}
