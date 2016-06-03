#include "preprocesswidget.h"
#include "ui_preprocesswidget.h"
#include "ui_dialog.h"

PreProcessWidget::PreProcessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreProcessWidget)
{
    ui->setupUi(this);
}

PreProcessWidget::~PreProcessWidget()
{
    delete ui;
}

Dialog::Dialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
