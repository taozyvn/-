#ifndef MAP_H
#define MAP_H

#include <QPoint>

class Map
{ 
public:
    int map[16][9];//地图，0是空地,1是小障碍，2是大障碍，3是路，4是房子，5是路标，>5塔
    QPoint startBlock;//开始点
    QPoint road[20];
    Map();
    void getLevelMap(int level);
    void copy(int newArray[16][9]);
};

#endif // MAP_H
