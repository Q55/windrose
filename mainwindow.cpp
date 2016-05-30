#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "preprocesswidget.h"
#include "postprocesswidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->preProcess,SIGNAL(clicked(bool)), this, SLOT(preProcessConfig()));
    connect(ui->postProcess,SIGNAL(clicked(bool)), this, SLOT(postProcessConfig()));
}

void MainWindow::preProcessConfig() {
    PreProcessWidget *pre_process = new PreProcessWidget();
    pre_process->show();
}

void MainWindow::postProcessConfig() {
    PostProcessWidget *post_process = new PostProcessWidget();
    post_process->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
