#include "settlement.h"
#include "ui_settlement.h"

Settlement::Settlement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settlement)
{
    ui->setupUi(this);
}

Settlement::~Settlement()
{
    delete ui;
}
