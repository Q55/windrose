#include "configdatabase.h"
#include "ui_configdatabase.h"

ConfigDataBase::ConfigDataBase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDataBase)
{
    ui->setupUi(this);

    this->setWindowTitle("配置数据库");

}

ConfigDataBase::ConfigDataBase(QString db_address, QString db_username, QString db_password, QVector<QString> db_list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDataBase)
{
    ui->setupUi(this);
    this->setWindowTitle("配置数据库");

    ui->config_db_address->setText(db_address);
    ui->config_db_username->setText(db_username);
    ui->config_db_password->setText(db_password);

    for (int i = 0; i < db_list.size(); ++i) {
        ui->listWidget_db_name_list->addItem(db_list.value(i));
    }
}


void ConfigDataBase::accept() {

    QVector<QString> namelist;
    for (int i = 0; i < ui->listWidget_db_name_list->count(); ++i)
        namelist.push_back(ui->listWidget_db_name_list->item(i)->text());

    emit configDataBase(ui->config_db_address->text(),
                        ui->config_db_username->text(),
                        ui->config_db_password->text(),
                        namelist);

    QDialog::accept();
}


ConfigDataBase::~ConfigDataBase()
{
    delete ui;
}
