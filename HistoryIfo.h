#ifndef HISTORY_H
#define HISTORY_H


class History
{
public:
    int level=5;//解锁的关卡数
    int stars[15]={3};
    int tower[7];
    int PrimoNum;//原石数，上限为4200，一星通关给40，二星再给80，三星再给160
    int towerLevel[7][3];//升级价格为40,60,100；
public:
    History();
};

#endif // HISTORY_H
