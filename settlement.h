#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <QDialog>

namespace Ui {
class Settlement;
}

class Settlement : public QDialog
{
    Q_OBJECT

public:
    explicit Settlement(QWidget *parent = nullptr);
    ~Settlement();

private:
    Ui::Settlement *ui;
};

#endif // SETTLEMENT_H
