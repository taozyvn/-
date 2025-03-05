#include "widget.h"

#include <QApplication>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.showFullScreen();
    //改变窗口大小和改变按钮大小因为设及全屏后屏幕的大小所以在这里实现
    w.blockWidth=w.size().width()/16;
    for(int i=0;i<12;i++){
        w.icons[i]->resize(w.blockWidth*0.7,w.blockWidth*0.7);
        w.icons[i]->hide();
    }
    w.towerLevel->setStyleSheet("font: "+QString::number(w.blockWidth/4)+"pt \"Cascadia Code\";background-color:none;");
    w.boxText.setStyleSheet("font: "+QString::number(w.blockWidth/10)+"pt \"Cascadia Code\";background:none;color:#0faf0f;");
    w.boxText.resize(w.blockWidth*1.55,w.blockWidth*0.75);
    w.box.resize(w.blockWidth*1.55,w.blockWidth*0.75);
    w.towerLevel->resize(w.blockWidth/4,w.blockWidth/4);
    return a.exec();
}
