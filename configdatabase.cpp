#include "configdatabase.h"
#include "ui_configdatabase.h"
#include "dataprocess.h"
#include <QMessageBox>
#include <QMenu>

ConfigDataBase::ConfigDataBase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDataBase)
{
    ui->setupUi(this);

    this->setWindowTitle("配置数据库");
    this->setFixedSize(QSize(343, 243));
    connect(ui->config_add_dbname, SIGNAL(clicked()), this, SLOT(addDBName()));
    connect(ui->listWidget_db_name_list, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(addRightMenuToRemoveDBName(const QPoint &)));
}

ConfigDataBase::ConfigDataBase(QString db_address, QString db_username, QString db_password, QVector<QString> db_list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDataBase)
{
    ui->setupUi(this);
    this->setWindowTitle("配置数据库");
        this->setFixedSize(QSize(343, 243));

    ui->config_db_address->setText(db_address);
    ui->config_db_username->setText(db_username);
    ui->config_db_password->setText(db_password);

    for (int i = 0; i < db_list.size(); ++i) {
        ui->listWidget_db_name_list->addItem(db_list.value(i));
    }
    connect(ui->config_add_dbname, SIGNAL(clicked()), this, SLOT(addDBName()));
    connect(ui->listWidget_db_name_list, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(addRightMenuToRemoveDBName(const QPoint &)));
}

void ConfigDataBase::addRightMenuToRemoveDBName(const QPoint &) {
    QMenu *right_menu = new QMenu(ui->listWidget_db_name_list);
    QAction *del_dbname = new QAction(tr("删除数据库"), ui->listWidget_db_name_list);

    connect(del_dbname, SIGNAL(triggered(bool)), this, SLOT(removeSelDBName()));

    if (ui->listWidget_db_name_list->selectedItems().size() > 0) {
        right_menu->addAction(del_dbname);
    }

    right_menu->exec(QCursor::pos());

    delete right_menu;
    delete del_dbname;
}

void ConfigDataBase::removeSelDBName() {
    QList<QListWidgetItem *> delItems = ui->listWidget_db_name_list->selectedItems();
    if(delItems.empty()) return;

    for (QList<QListWidgetItem *>::iterator it = delItems.begin(); it != delItems.end(); ++it) {
        delete ui->listWidget_db_name_list->takeItem(ui->listWidget_db_name_list->row(*it));
    }
    repaint();
 }

void ConfigDataBase::addDBName() {
    QString new_db_name = ui->config_db_name->text();

    bool is_exist = true;

    // firstly, we check if dbname exist in database;
    DataProcess dp;
    dp.setDBAddress(ui->config_db_address->text());
    dp.setDBUsername(ui->config_db_username->text());
    dp.setDBPassword(ui->config_db_password->text());
    QStringList temp = dp.queryTableNameListbyDBName(new_db_name);
    if (temp.size() <= 0)
        is_exist = false;


    // secondly, we check if dbname exist in listwidget
    if(is_exist) { // if dbname exist in database.
        is_exist = false;
        for (int i = 0; i < ui->listWidget_db_name_list->count(); ++i) {
            if (ui->listWidget_db_name_list->item(i)->text() == new_db_name) {
                is_exist = true;
                break;
            }
        }
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("警告"));
        msgBox.setText("数据库查询失败或数据库为空，请检查用户名、密码和数据库名称是否正确！");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    if (!is_exist) {
        ui->listWidget_db_name_list->addItem(new_db_name);
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("警告"));
        msgBox.setText("数据库名已存在，无需重复添加");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
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
