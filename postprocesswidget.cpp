#include "postprocesswidget.h"
#include "ui_postprocesswidget.h"

PostProcessWidget::PostProcessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PostProcessWidget)
{
    ui->setupUi(this);
}

PostProcessWidget::~PostProcessWidget()
{
    delete ui;
}
