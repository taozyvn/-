#include "widget.h"
#include "ui_widget.h"
#include <QClipboard>
#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QShortcut>
#include <QTimer>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    repaint();
    QTimer * timer= new QTimer(this);
    timer->start(3);//正常速度为33
    connect(timer,&QTimer::timeout,this,&Widget::timeOut);
    icons[0]=ui->pushButton_1;
    icons[1]=ui->pushButton_2;
    icons[2]=ui->pushButton_3;
    icons[3]=ui->pushButton_4;
    icons[4]=ui->pushButton_5;
    icons[5]=ui->pushButton_6;
    icons[6]=ui->pushButton_7;
    icons[7]=ui->pushButton_8;
    icons[8]=ui->pushButton_9;
    icons[9]=ui->pushButton_10;
    icons[10]=ui->pushButton_11;
    icons[11]=ui->pushButton_12;
    towerLevel=ui->label;
    ui->widget->hide();
    ui->label->hide();
    for(int i=0;i<12;i++){
        connect(icons[i],&QPushButton::clicked,this,&Widget::buttonClicked);
    }
    this->setWindowFlag(Qt::FramelessWindowHint);
    tower=new Tower();
}
Widget::~Widget()
{
    delete ui;
}
void Widget::checkButtonPlace(int x, int y)
{
    if(x==0){
        if(y==0){//[左上角
            initButton(x,y,1);
        }else if(y==8){//左下角
            initButton(x,y,5);
        }else{//左边
            initButton(x,y,3);
        }
    }else if(x==15){
        if(y==0){//右上角
            stop=true;
            Settlement Dialog(blockWidth,this);
            Dialog.exec();
            if(Dialog.choose==2){
                died();
            }else if(Dialog.choose==3){
                int levelNum=level.level;
                clearInfo();
                gameStart(levelNum);
            }
            stop=false;
            return;
        }else if(y==8){//右下角
            initButton(x,y,7);
        }else{//右边
            initButton(x,y,4);
        }
    }else{
        if(y==0){//上边
            initButton(x,y,2);
        }else if(y==8){//下边
            initButton(x,y,6);
        }else{//中间
            initButton(x,y,0);
        }
    }
}

void Widget::initButton(int x, int y, int type)
{
    qDebug()<<"in initButton";
    ui->widget->hide();
    ui->label->hide();
    for(int i=0;i<12;i++)icons[i]->hide();
    clickedPlace=QPoint(x,y);//标记选择的点
    int deviationX=0;//偏移量
    int deviationY=0;
    switch (type) {//0为中间，1为左上，2为上，3为左，4为右，5为左下，6为下，7为右下
        case 1:
            deviationX=1;
            deviationY=1;
        break;
        case 2:
            deviationY=1;
        break;
        case 3:
            deviationX=1;
        break;
        case 4:
            deviationX=-1;
        break;
        case 5:
            deviationX=1;
            deviationY=-1;
        break;
        case 6:
            deviationY=-1;
        break;
        case 7:
            deviationX=-1;
            deviationY=-1;
        break;
    }
    switch (map.map[x][y]){
        case 0:
            icons[0]->move((x-0.75+deviationX*0.6+0.15)*blockWidth,(y-0.75+deviationY*0.6+0.15)*blockWidth);
            icons[1]->move((x+deviationX*0.6+0.15)*blockWidth,(y-0.75+deviationY*0.6+0.15)*blockWidth);
            icons[2]->move((x+0.75+deviationX*0.6+0.15)*blockWidth,(y-0.75+deviationY*0.6+0.15)*blockWidth);
            icons[3]->move((x-0.75+deviationX*0.6+0.15)*blockWidth,(y+deviationY*0.6+0.15)*blockWidth);
            icons[4]->move((x+0.75+deviationX*0.6+0.15)*blockWidth,(y+deviationY*0.6+0.15)*blockWidth);
            icons[5]->move((x-0.75+deviationX*0.6+0.15)*blockWidth,(y+0.75+deviationY*0.6+0.15)*blockWidth);
            icons[6]->move((x+0.75+deviationX*0.6+0.15)*blockWidth,(y+0.75+deviationY*0.6+0.15)*blockWidth);
            icons[7]->move((x+deviationX*0.6+0.15)*blockWidth,(y+0.75+deviationY*0.6+0.15)*blockWidth);
            if(type>0&&type<3){
                icons[type-1]->move((x+deviationX*0.6+0.15)*blockWidth,(y+deviationY*0.6+0.15)*blockWidth);
            }else if(type>=3&&type<=5){
                icons[type]->move((x+deviationX*0.6+0.15)*blockWidth,(y+deviationY*0.6+0.15)*blockWidth);
            }else if(type==6){
                icons[7]->move((x+deviationX*0.6+0.15)*blockWidth,(y+deviationY*0.6+0.15)*blockWidth);
            }else if(type==7){
                icons[6]->move((x+deviationX*0.6+0.15)*blockWidth,(y+deviationY*0.6+0.15)*blockWidth);
            }
            for(int i=0;i<7;i++){
                if(history.tower[i]>0){
                    icons[i]->show();
                    icons[i]->raise();
                }
            }
        break;
        case 1:
            switch (type) {
                case 1:case 5:case 7:
                icons[7]->move((x+0.75*deviationX+0.15)*blockWidth,(y+0.15)*blockWidth);
                icons[9]->move((x+0.15)*blockWidth,(y+0.75*deviationY+0.15)*blockWidth);
                break;
                case 2:case 6:
                icons[7]->move((x+0.75+0.15)*blockWidth,(y+0.15)*blockWidth);
                icons[9]->move((x-0.75+0.15)*blockWidth,(y+0.15)*blockWidth);
                break;
                case 3:case 4:case 0:
                icons[7]->move((x+0.15)*blockWidth,(y+0.75+0.15)*blockWidth);
                icons[9]->move((x+0.15)*blockWidth,(y-0.75+0.15)*blockWidth);
                break;
            }
            icons[9]->show();
            icons[9]->raise();
        break;
        case 2:
            switch (type) {
                case 1:case 5:case 7:
                icons[7]->move((x+0.75*deviationX+0.15)*blockWidth,(y+0.15)*blockWidth);
                icons[8]->move((x+0.15)*blockWidth,(y+0.75*deviationY+0.15)*blockWidth);
                break;
                case 2:case 6:
                icons[7]->move((x+0.75+0.15)*blockWidth,(y+0.15)*blockWidth);
                icons[8]->move((x-0.75+0.15)*blockWidth,(y+0.15)*blockWidth);
                break;
                case 3:case 4:case 0:
                icons[7]->move((x+0.15)*blockWidth,(y+0.75+0.15)*blockWidth);
                icons[8]->move((x+0.15)*blockWidth,(y-0.75+0.15)*blockWidth);
                break;
            }
            icons[8]->show();
            icons[8]->raise();
        break;
        case 7:
            ui->widget->show();
            ui->label->show();
            Tower *temp=tower->next;
            while((temp->place.x()!=x||temp->place.y()!=y)&&temp->next!=NULL){
                temp=temp->next;
            }
            ui->widget->resize(temp->range*2*blockWidth,temp->range*2*blockWidth);
            ui->label->setNum(temp->level);
            ui->widget->move((x-temp->range)*blockWidth+blockWidth/2,(y-temp->range)*blockWidth+blockWidth/2);
            ui->label->move(x*blockWidth+blockWidth/2-blockWidth/8,y*blockWidth+blockWidth/2-blockWidth/8);
            switch (type) {
                case 1:case 5:case 7:
                icons[11]->move((x+0.75*deviationX+0.15)*blockWidth,(y+0.15)*blockWidth);
                icons[10]->move((x+0.15)*blockWidth,(y+0.75*deviationY+0.15)*blockWidth);
                icons[7]->move((x+0.75*deviationX+0.15)*blockWidth,(y+0.75*deviationY+0.15)*blockWidth);
                break;
                case 2:case 6:
                icons[7]->move((x+0.15)*blockWidth,(y+0.75*deviationY+0.15)*blockWidth);
                icons[10]->move((x+0.75+0.15)*blockWidth,(y+0.15)*blockWidth);
                icons[11]->move((x-0.75+0.15)*blockWidth,(y+0.15)*blockWidth);
                break;
                case 3:case 4:
                icons[7]->move((x+0.75*deviationX+0.15)*blockWidth,(y+0.15)*blockWidth);
                icons[10]->move((x+0.15)*blockWidth,(y+0.75+0.15)*blockWidth);
                icons[11]->move((x+0.15)*blockWidth,(y-0.75+0.15)*blockWidth);
                break;
                case 0:
                icons[7]->move((x+0.15)*blockWidth,(y+0.75+0.15)*blockWidth);
                icons[10]->move((x+0.75+0.15)*blockWidth,(y+0.15)*blockWidth);
                icons[11]->move((x-0.75+0.15)*blockWidth,(y+0.15)*blockWidth);
                break;
            }
            icons[10]->setText("升级\n"+QString::number(temp->price*1.5));
            icons[11]->setText("出售\n"+QString::number(temp->price*0.6));
            icons[10]->show();
            icons[11]->show();
            icons[10]->raise();
            icons[11]->raise();
            break;
        return;
    }
    icons[7]->show();
    icons[7]->raise();
    qDebug()<<"out initButton";
}

void Widget::win()
{
    qDebug()<<"in win";
    if(level.level==2){
        Tower * temp=tower;
        int towerNum=0;
        while(true){
            if(temp->next==NULL){
                break;
            }else{
               towerNum++;
               temp=temp->next;
            }
        }
        stars[2]=towerNum>=6;
    }
    if(level.level==3)stars[1]=mola>=100;
    Settlement Dialog(blockWidth,2,stars,level.objective,this);
    Dialog.exec();
    if(history.level==level.level){
        history.level++;
    }
    mode=1;
    map.getLevelMap(-1);
    clearInfo();
    qDebug()<<"out win";
}

void Widget::died()
{
    qDebug()<<"in died";
    Settlement Dialog(blockWidth,1,stars,level.objective,this);
    Dialog.exec();
    mode=1;
    map.getLevelMap(-1);
    clearInfo();
    qDebug()<<"out died";
}

void Widget::clearInfo()
{
    qDebug()<<"in clearnInfo";
    if(tower->next!=NULL){
        Tower * temp=tower->next;
        Tower * temp2=temp->next;
        while(true){
            delete temp;
            temp=temp2;
            if(temp==NULL){
                break;
            }
            temp2=temp->next;
        }
    }
    for(int i=0;i<level.waveNum;i++){
        for(int j=0;j<enemyNum[i];j++){
            delete enemy[i][j];
        }
    }
    moreMola=0;
    waveNum=0;
    endTime=0;
    tower->next=NULL;
    stars[0]=false;
    stars[1]=false;
    stars[2]=false;
    heart=5;
    for(int i=0;i<12;i++){
        icons[i]->hide();
    }
    ui->widget->hide();
    ui->label->hide();
    qDebug()<<"out clearnInfo";
}

void Widget::gameStart(int levelNum)
{
    level.getLevelInfo(levelNum);
    Settlement Dialog(blockWidth,0,stars,level.objective,this);
    Dialog.exec();
    map.getLevelMap(levelNum);
    for(int i=0;i<3;i++)stars[i]=true;
    timeNum=0;
    enemy.clear();
    enemyNum.clear();
    enemy.resize(level.waveNum);//给波次分配空间
    enemyNum.resize(level.waveNum);//给敌人数量分配空间
    for(int i=0;i<level.waveNum;i++){
        enemy[i].resize(level.enemy[i]);//给敌人分配空间
        enemyNum[i]=0;//每波的当前敌人数都是0
    }
    mola=level.startMola;
}
void Widget::timeOut()
{
    if(stop)return;
    qDebug()<<"in timeOut";
    //关卡中的事件
    if(mode==3){
        qDebug()<<level.enemyTime[waveNum];
        if(timeNum%level.enemyTime[waveNum]==0){//出怪
            if(level.enemy[waveNum]>enemyNum[waveNum]){//怪物数量没有达标
                Enemy * newEnemy=new Enemy(map.startBlock,
                                           level.enemyType[waveNum],
                                           waveNum*100+enemyNum[waveNum]
                                           ,blockWidth);//创建新的敌人
                connect(newEnemy,&Enemy::inHome,[=](){
                    heart--;
                    stars[0]=false;
                    if(heart==0)died();
                });
                connect(newEnemy,&Enemy::died,[=](int type){
                    switch (type) {
                        case 1:mola+=(1.0+(timeNum/2)%2)*(1.0+(double)moreMola/2);break;
                        case 2:mola+=2.0*(1.0+(double)moreMola/2);break;
                        case 5:mola+=(1.0+(timeNum/2)%2)*(1.0+(double)moreMola/2);break;
                    }
                });
                enemy[waveNum][enemyNum[waveNum]]=newEnemy;
                enemyNum[waveNum]++;
            }else{
                if(endTime==0){//记录波次结束
                    endTime=timeNum;//记录波次结束时间，当间隔达到时出下一波怪
                }
            }
        }
        if(endTime!=0){//召唤下一波敌人
            if(timeNum-endTime==level.waveTime*33&&waveNum<level.waveNum-1){
                waveNum++;
                endTime=0;
            }else{
                bool isFinish=true;
                for(int i=0;i<enemyNum[waveNum];i++){
                    if(enemy[waveNum][i]->bload>0){
                        isFinish = false;
                        break;
                    }
                }
                if(isFinish){
                    if(waveNum<level.waveNum-1){
                        waveNum++;
                        endTime=0;
                    }else{
                        win();
                    }
                }
            }
        }
        for(int i=0;i<level.waveNum;i++){//敌人移动
            for(int j=0;j<enemyNum[i];j++){
                if(enemy[i][j]->diedTime>=0&&(timeNum+enemy[i][j]->no)%enemy[i][j]->spead==0){
                    enemy[i][j]->run(map);
                }
            }
        }
        Tower * temp = tower->next;//防御塔攻击
        while(temp!=NULL){
            if(temp->type!=5){
                if((timeNum-temp->startTime)%temp->fireSpeed==0){
                    temp->Action(enemyNum,enemy);
                }else{
                    if(temp->enemy[0]!=-1){
                        temp->angle =temp->getAngle(temp->place,enemy[temp->enemy[0]][temp->enemy[1]]->place[0],enemy[temp->enemy[0]][temp->enemy[1]]->place[1]);
                    }
                }
            }
            temp=temp->next;
        }
    }
    repaint();
    timeNum++;
    qDebug()<<"out timeout";

}

void Widget::buttonClicked()
{
    qDebug()<<"in buttomClicked";
    if(sender()==icons[0]){
    }else if(sender()==icons[1]){
        mola-=20;
        if(mola<0){
            mola+=20;
            return;
        }else{
            Tower *temp=tower;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=new Tower(2,clickedPlace,timeNum);
            map.map[clickedPlace.x()][clickedPlace.y()]=7;
        }
    }else if(sender()==icons[2]){
    }else if(sender()==icons[3]){
    }else if(sender()==icons[4]){
        mola-=30;
        if(mola<0){
            mola+=30;
            return;
        }else{
            moreMola++;
            Tower *temp=tower;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=new Tower(5,clickedPlace,timeNum);
            map.map[clickedPlace.x()][clickedPlace.y()]=7;
            if(level.level==1)stars[2]=false;
        }
    }else if(sender()==icons[5]){
    }else if(sender()==icons[6]){
    }else if(sender()==icons[8]){
        mola-=60;
        if(mola<0){
            mola+=60;
            return;
        }else{
            map.map[clickedPlace.x()][clickedPlace.y()]=0;
            if(level.level==1)stars[1]=false;
            if(level.level==2)stars[1]=true;
        }
    }else if(sender()==icons[9]){
        mola-=30;
        if(mola<0){
            mola+=30;
            return;
        }else{
            map.map[clickedPlace.x()][clickedPlace.y()]=0;
            if(level.level==1)stars[1]=false;
            if(level.level==2)stars[1]=true;
        }
    }else if(sender()==icons[10]){
        Tower *temp=tower;
        while(true){
            if(temp->next->place==clickedPlace){
                temp=temp->next;
                break;
            }
            temp=temp->next;
        }
        mola-=temp->price*1.5;
        if(mola<0){
            mola+=temp->price*1.5;
            return;
        }else{
            temp->levelUp();
        }
    }else if(sender()==icons[11]){
        Tower *temp=tower;
        while(true){
            if(temp->next->place==clickedPlace){
                break;
            }
            temp=temp->next;
        }
        if(temp->next->next==NULL){
            delete temp->next;
            temp->next=NULL;
        }else{
            Tower * temp2=temp->next->next;
            delete temp->next;
            temp->next=temp2;
        }
        mola+=temp->price*0.6;
        map.map[clickedPlace.x()][clickedPlace.y()]=0;
    }
    for(int i=0;i<12;i++){
        icons[i]->hide();
    }
    ui->widget->hide();
    ui->label->hide();
    qDebug()<<"out buttonClicked";
}
void Widget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"in mousePressEvent";
    QPoint place = event->globalPos();//获得点击的位置
    place = this->mapFromGlobal(place);
    int x=place.x()/blockWidth,y=place.y()/blockWidth;//用坐标除以格子宽度，得到格子行列号
    if(isMaximized()){
        x=(place.x()+blockWidth/2)/blockWidth-1;
        y=place.y()/blockWidth;
    }
    switch (mode) {
    case 0://封面界面
        if(x>=6&&x<10&&y>=6&&y<8){//点击了开始游戏跳转关卡选择界面
            map.getLevelMap(-1);
            mode=1;
        }
        break;
    case 1://关卡选择界面
        if(x-2>=0&&x-2<11&&y-3>=0){
            if((x-2)%2==0&&(y-3)%2==0&&history.level>=(x-2)/2+1+((y-3)/2)*5){
                gameStart((x-2)/2+1+((y-3)/2)*5);
                mode=3;
            }
        }
        break;
    case 3:
        checkButtonPlace(x,y);
        break;
    }
    qDebug()<<"out mousePressEvent";
}
void Widget::paintEvent(QPaintEvent *)
{
    qDebug()<<"in paintEvent";
    QPainter painter(this);
    QPixmap * pixmap;
    QRect rect;
    Tower * temp;
    for(int i=0;i<16;i++){
        for(int j=0;j<9;j++){
            rect =QRect(i*blockWidth-1,j*blockWidth-1,blockWidth+2,blockWidth+2);//定义一个方格大小的正方形
            if(map.map[i][j]<3){
                pixmap=new QPixmap(":map/grassland-"+QString::number((i+j)%2+1)+
                                   "-"+QString::number(map.map[i][j])+".png");
            }else{
                pixmap=new QPixmap(":map/ground-"+QString::number((i+j)%2+1)+
                                   "-"+QString::number(map.map[i][j]-2)+".png");
            }
            painter.drawPixmap(rect,*pixmap);
        }
    }
    int angle=0;
    QFont font("隶书");
    switch (mode){
    case 0:
        //调整角度
        if(timeNum%20>=10){
            angle=12;
        }else{
            angle=348;
        }
        //移动坐标中心到即将打印图形的位置
        painter.save();//存储当前状态
        rect =QRect(-blockWidth/2,-blockWidth/2,blockWidth,blockWidth*0.85);//定义一个方格大小的正方形
        pixmap=new QPixmap(":enemy/slime-2-1.png");
        painter.translate(1.5*blockWidth,2.65*blockWidth);
        painter.rotate(angle);
        painter.drawPixmap(rect,*pixmap);
        painter.restore();//复位当前状态
        painter.save();
        rect =QRect(-blockWidth/2,-blockWidth/2,blockWidth,blockWidth*0.85);//定义一个方格大小的正方形
        pixmap=new QPixmap(":enemy/slime-2-3.png");
        painter.translate(1.5*blockWidth,4.65*blockWidth);
        painter.rotate(angle);
        painter.drawPixmap(rect,*pixmap);
        painter.restore();
        painter.save();
        rect =QRect(-blockWidth/2,-blockWidth/2,blockWidth,blockWidth*0.85);//定义一个方格大小的正方形
        pixmap=new QPixmap(":enemy/slime-2-5.png");
        painter.translate(13.5*blockWidth,3.65*blockWidth);
        painter.rotate(angle);
        painter.drawPixmap(rect,*pixmap);
        painter.restore();
        //更换角度
        if(timeNum%20>=10){
            angle=348;
        }else{
            angle=12;
        }
        painter.save();//存储当前状态
        rect =QRect(-blockWidth/2,-blockWidth/2,blockWidth,blockWidth*0.85);//定义一个方格大小的正方形
        pixmap=new QPixmap(":enemy/slime-2-2.png");
        painter.translate(2.5*blockWidth,3.65*blockWidth);
        painter.rotate(angle);
        painter.drawPixmap(rect,*pixmap);
        painter.restore();//复位当前状态
        painter.save();//存储当前状态
        rect =QRect(-blockWidth/2,-blockWidth/2,blockWidth,blockWidth*0.85);//定义一个方格大小的正方形
        pixmap=new QPixmap(":enemy/slime-2-4.png");
        painter.translate(14.5*blockWidth,2.65*blockWidth);
        painter.rotate(angle);
        painter.drawPixmap(rect,*pixmap);
        painter.restore();//复位当前状态
        painter.save();//存储当前状态
        rect =QRect(-blockWidth/2,-blockWidth/2,blockWidth,blockWidth*0.85);//定义一个方格大小的正方形
        pixmap=new QPixmap(":enemy/slime-2-6.png");
        painter.translate(14.5*blockWidth,4.65*blockWidth);
        painter.rotate(angle);
        painter.drawPixmap(rect,*pixmap);
        painter.restore();//复位当前状态
        painter.rotate(0);
        font.setPointSize(blockWidth/3*2);
        painter.setFont(font);
        painter.setPen(qRgb(0,0,160));
        rect =QRect(5.2*blockWidth,2.35*blockWidth,blockWidth*5.6,blockWidth);//定义一个方格大小的正方形
        painter.drawText(rect,"史莱姆塔防");
        painter.setPen(qRgb(0,96,225));
        rect =QRect(5.18*blockWidth,2.33*blockWidth,blockWidth*5.6,blockWidth);//定义一个方格大小的正方形
        painter.drawText(rect,"史莱姆塔防");
        painter.setPen(qRgb(225,0,40));
        font.setPointSize(blockWidth/5*3);
        painter.setFont(font);
        rect=QRect(6.15*blockWidth,6.5*blockWidth,blockWidth*4,blockWidth);
        painter.drawText(rect,"开始游戏");
        rect =QRect(6.13*blockWidth,6.48*blockWidth,blockWidth*4,blockWidth);//定义一个方格大小的正方形
        painter.setPen(qRgb(255,125,0));
        painter.drawText(rect,"开始游戏");
        break;
    case 1:
        for(int i=0;i<5;i++){
            for(int j=0;j<3;j++){
                rect =QRect((i*2+2)*blockWidth+blockWidth*0.1,
                            (j*2+3)*blockWidth+blockWidth*0.1,
                            blockWidth*0.8,
                            blockWidth*0.8);//定义一个方格大小的正方形
                if(history.level>=(j*5+(i+1))){
                    pixmap=new QPixmap(":level/level-1-"+QString::number((j*5+(i+1)))+".png");
                }else{
                    pixmap=new QPixmap(":level/level-2-"+QString::number((j*5+(i+1)))+".png");
                }
                painter.drawPixmap(rect,*pixmap);
            }
        }
        font.setPointSize(blockWidth/5*3-2);
        painter.setFont(font);
        rect=QRect(4.15*blockWidth,blockWidth,blockWidth*4,blockWidth);
        painter.setPen(qRgb(0,96,225));
        painter.drawText(rect,"关卡选择");
        rect =QRect(4.13*blockWidth,0.98*blockWidth,blockWidth*4,blockWidth);//定义一个方格大小的正方形
        painter.setPen(qRgb(0,0,160));
        painter.drawText(rect,"关卡选择");
        rect =QRect(13*blockWidth,2*blockWidth,blockWidth,blockWidth);
        pixmap=new QPixmap(":level/yvanShi.png");
        painter.drawPixmap(rect,*pixmap);
        rect =QRect(13*blockWidth,6*blockWidth,blockWidth,blockWidth);
        pixmap=new QPixmap(":level/yvanShi.png");
        painter.drawPixmap(rect,*pixmap);
        rect=QRect(13.05*blockWidth,blockWidth*2.87,blockWidth,blockWidth*3.2);
        painter.setPen(qRgb(255,128,0));
        painter.drawText(rect,"科技树");
        rect =QRect(13.03*blockWidth,2.85*blockWidth,blockWidth,blockWidth*3.2);//定义一个方格大小的正方形
        painter.setPen(qRgb(255,0,36));
        painter.drawText(rect,"科技树");
        break;
    case 3:
        //绘画右上方的信息框
        font.setFamily("Arial Black");
        font.setPointSize(blockWidth/10);
        painter.setFont(font);
        if(mola>999){
            rect = QRect(15.05*blockWidth,0.10*blockWidth,blockWidth,blockWidth/2);
        }else if(mola>99){
            rect = QRect(15.15*blockWidth,0.10*blockWidth,blockWidth,blockWidth/2);
        }else{
            rect = QRect(15.25*blockWidth,0.10*blockWidth,blockWidth,blockWidth/2);
        }
        painter.setPen(qRgb(255,128,10));
        painter.drawText(rect,QString::number((int)mola));
        if(heart>9){
            rect = QRect(15.2*blockWidth,0.35*blockWidth,blockWidth,blockWidth/2);
        }else{
            rect = QRect(15.3*blockWidth,0.38*blockWidth,blockWidth,blockWidth/2);
        }
        painter.setPen(qRgb(255,10,10));
        painter.drawText(rect,QString::number(heart));
        rect = QRect(15.2*blockWidth,0.66*blockWidth,blockWidth,blockWidth/2);
        painter.setPen(qRgb(0,255,0));
        painter.drawText(rect,QString::number(waveNum+1)+"/"+QString::number(level.waveNum));
        //绘画敌人
        for(int i=0;i<level.waveNum;i++){
            for(int j=0;j<enemyNum[i];j++){
                if(enemy[i][j]->type<=7){//判断是否是BOSS
                    if(enemy[i][j]->bload<0){//判断是否是以死亡单位
                        if(enemy[i][j]->diedTime>0){//判断是否还在死亡虚影期
                            enemy[i][j]->diedTime-=3;
                            rect=QRect(enemy[i][j]->place[0]*blockWidth/20-blockWidth/6,
                                    enemy[i][j]->place[1]*blockWidth/20-blockWidth/6,
                                    blockWidth/3,
                                    blockWidth/3);
                            pixmap= new QPixmap(":enemy/slime-1-"+QString::number(enemy[i][j]->type)+".png");
                            painter.setOpacity((double)enemy[i][j]->diedTime/100);//透明度为100%
                            painter.drawPixmap(rect,*pixmap);
                            painter.setOpacity(1);//透明度为100%
                        }
                        continue;
                    }
                    //敌人本体
                    rect=QRect(enemy[i][j]->place[0]*blockWidth/20-blockWidth/6,
                            enemy[i][j]->place[1]*blockWidth/20-blockWidth/6,
                            blockWidth/3,
                            blockWidth/3);
                    pixmap= new QPixmap(":enemy/slime-1-"+QString::number(enemy[i][j]->type)+".png");
                    painter.drawPixmap(rect,*pixmap);
                    //血条背景
                    rect=QRect(enemy[i][j]->place[0]*blockWidth/20-blockWidth/6,
                            enemy[i][j]->place[1]*blockWidth/20-blockWidth/6,
                            blockWidth/3+blockWidth/40,
                            blockWidth/15);
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(Qt::darkRed);
                    painter.drawRect(rect);
                    //空血条
                    rect=QRect(enemy[i][j]->place[0]*blockWidth/20-blockWidth/6+blockWidth/60,
                            enemy[i][j]->place[1]*blockWidth/20-blockWidth/6+blockWidth/75,
                            blockWidth/3,
                            blockWidth/20);
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(Qt::black);
                    painter.drawRect(rect);
                    //剩余血量
                    rect=QRect(enemy[i][j]->place[0]*blockWidth/20-blockWidth/6+blockWidth/60,
                            enemy[i][j]->place[1]*blockWidth/20-blockWidth/6+blockWidth/75,
                            blockWidth/3*((double)enemy[i][j]->bload/enemy[i][j]->maxBload),
                            blockWidth/20);
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(Qt::red);
                    painter.drawRect(rect);
                }else{

                }
            }
        }
        //绘画塔
        temp=tower->next;
        while(temp!=NULL){
            //绘画子弹
            switch (temp->type) {
                case 2:
                    if(temp->enemy[0]==-1){
                        break;
                    }
                    if(enemy[temp->enemy[0]][temp->enemy[1]]->bload<=0){
                        break;
                    }
                QPoint bulletPlace=getBullet(QPoint(temp->place.x()*20+10,temp->place.y()*20+10),
                                             QPoint(enemy[temp->enemy[0]][temp->enemy[1]]->place[0],
                                                    enemy[temp->enemy[0]][temp->enemy[1]]->place[1]),
                                             (double)((timeNum-temp->startTime)%temp->fireSpeed)/temp->fireSpeed);
                rect=QRect(bulletPlace.x()*blockWidth/20-blockWidth/20,
                        bulletPlace.y()*blockWidth/20-blockWidth/20,
                        blockWidth/10,
                        blockWidth/10);
                painter.setBrush(Qt::cyan);
                painter.drawEllipse(rect);
                break;
            }
            //塔身
            rect=QRect((temp->place.x()+0.1)*blockWidth,(temp->place.y()+0.1)*blockWidth,
                       blockWidth*0.8,blockWidth*0.8);
            pixmap= new QPixmap(":cannon/cannon-"+QString::number(temp->type)+"-1.png");
            painter.drawPixmap(rect,*pixmap);
            //炮管
            painter.save();//存储当前状态
            if(temp->type==1||temp->type==5||temp->type==6){
                rect=QRect((-0.3)*blockWidth,(-0.3)*blockWidth,
                           blockWidth*0.6,blockWidth*0.6);
            }else{
                rect=QRect((-0.3)*blockWidth,(-0.3)*blockWidth,
                           blockWidth*0.9,blockWidth*0.6);
            }
            pixmap= new QPixmap(":cannon/cannon-"+QString::number(temp->type)+"-2.png");
            painter.translate((temp->place.x()+0.5)*blockWidth,(temp->place.y()+0.5)*blockWidth);
            painter.rotate(temp->angle);
            painter.drawPixmap(rect,*pixmap);
            painter.restore();//复位当前状态
            temp=temp->next;
        }
        break;
    default:break;
    }
    qDebug()<<"out paintEvent";
}

QPoint Widget::getBullet(const QPoint &p1, const QPoint &p2, double percentage) {
    double dx = (double)p2.x() - p1.x();
    double dy = (double)p2.y() - p1.y();
    return QPoint(p1.x() + dx * percentage, p1.y() + dy * percentage);
}
