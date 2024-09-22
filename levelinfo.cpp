#include "levelinfo.h"

LevelInfo::LevelInfo(int level)
{
    switch (level) {
        case 1:
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
