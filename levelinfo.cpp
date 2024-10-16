#include "levelinfo.h"

LevelInfo::LevelInfo()
{

}

void LevelInfo::getLevelInfo(int level)
{
    this->level=level;
    objective[0]="不要损失生命值";
    switch (level) {
        //第一关的数据
        case 1:
        objective[1]="不砍伐任何树木";
        objective[2]="不使用岩元素塔";
        waveNum=5;
        startMola=30;
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
        enemy[4]-=5;
        break;
        //第二关的数据
        case 2:
        objective[1]="砍伐任意的树木";
        objective[2]="放置六座防御塔";
        waveNum=10;
        startMola=50;
        enemyType.resize(waveNum);
        enemyTime.resize(waveNum);
        enemy.resize(waveNum);
        for(int i=0;i<10;i++){
            enemy[i]=5+i*2;
            switch (i%3) {
                case 0:
                enemyType[i]=1;
                enemyTime[i]=15;
                break;
                case 1:
                enemyType[i]=2;
                enemyTime[i]=20;
                enemy[i]/=1.3;
                break;
                case 2:
                enemyType[i]=5;
                enemyTime[i]=10;
                enemy[i]*=2;
                break;
            }
        }
        enemyType[9]=2;
        enemyTime[9]=20;
        waveTime=25;
        break;
        //第三关的数据
        case 3:
        objective[1]="过关时有一百摩拉";
        objective[2]="拥有等级二的塔";
        waveNum=10;
        startMola=40;
        enemyType.resize(waveNum);
        enemyTime.resize(waveNum);
        enemy.resize(waveNum);
        for(int i=0;i<10;i++){
            enemy[i]=5+i*2;
            switch (i%3) {
                case 0:
                enemyType[i]=1;
                enemyTime[i]=14;
                break;
                case 1:
                enemyType[i]=5;
                enemyTime[i]=8;
                enemy[i]*=2;
                break;
                case 2:
                enemyType[i]=2;
                enemyTime[i]=15;
                enemy[i]/=1.5;
                break;
            }
        }
        enemyType[9]=2;
        enemyTime[9]=20;
        waveTime=20;
        break;
    }
}
