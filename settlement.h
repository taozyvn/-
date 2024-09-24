#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class Settlement;
}

class Settlement : public QDialog
{
    Q_OBJECT
public:
    int mode;//模式，0为关卡开始，1为游戏失败，2-5为3星到0星
    bool stars[3];//星星数
    QWidget * box[3];//框
public:
    explicit Settlement(int blockWidth, int mode, bool stars[3], QString objective[], QWidget *parent = nullptr);
    ~Settlement();

private:
    Ui::Settlement *ui;
};

#endif // SETTLEMENT_H
