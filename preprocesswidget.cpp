#include "preprocesswidget.h"
#include "ui_preprocesswidget.h"

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
