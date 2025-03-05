#include "HistoryIfo.h"

History::History()
{
    for(int i=0;i<7;i++){
        tower[i]=2;
    }
    PrimoNum=4200;
    for(int i=0;i<7;i++){
        towerLevel[i][0]=0;
        towerLevel[i][1]=0;
        towerLevel[i][2]=0;
    }
//    for(int i=0;i<15;i++)stars[i]=3;
}
