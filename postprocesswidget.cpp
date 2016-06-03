#include "postprocesswidget.h"
#include "ui_postprocesswidget.h"

PostProcessWidget::PostProcessWidget(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::PostProcessWidget)
{
    ui->setupUi(this);
}

PostProcessWidget::~PostProcessWidget()
{
    delete ui;
}
