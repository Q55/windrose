#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>
#include <QErrorMessage>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
 //
    ui->setupUi(this);

    /***************************************
     * initial DataBase Index to Name Map
     ***************************************/
    dbIndexNameMap[0] = "111";
    dbIndexNameMap[1] = "112";
    dbIndexNameMap[2] = "118";

    curSelectedListSet.clear();


    /*********************************
     * initial Table list
     *********************************/
    QStringList strings;
    strings = dpclass.queryTableNameListbyDBName(dbIndexNameMap[0]);
    initTableList(0, strings);

    strings.clear();

    strings = dpclass.queryTableNameListbyDBName(dbIndexNameMap[1]);
    initTableList(1, strings);

    strings.clear();

    strings = dpclass.queryTableNameListbyDBName(dbIndexNameMap[2]);
    initTableList(2, strings);

    ui->comboBox_database->setCurrentIndex(1);
    int database = ui->comboBox_database->currentIndex();
    setDataTable(database);
    setDataList(ui->comboBox_dababaseT->currentText());

 //   connect(ui->comboBox_database, SIGNAL(currentIndexChanged(int)), this, SIGNAL(comboboxDatabase_changed(int) ) );
    connect(ui->comboBox_database, SIGNAL( currentIndexChanged(int) ), this, SLOT( setDataTable(int) ) );
    connect(ui->comboBox_dababaseT, SIGNAL( currentIndexChanged(QString) ), this, SLOT( setDataList(QString) ) );

    connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT( setSelectedDataList()));
    //connect(ui->)
}

void Dialog::initTableList(int index, QStringList strings)
{
    switch (index) {
    case 0:
        table111 = strings;
        break;
    case 1:
        table112 = strings;
        break;
    case 2:
        table118 = strings;
        break;
    default:
        break;
    }
}
/*
void Dialog::comboboxDatabase_changed(int)
{
    connect(ui->comboBox_database, currentIndexChanged, this, );
}
*/
void Dialog::setDataTable( int style )
{
    if ( style == FPSO111 )
    {
        ui->comboBox_dababaseT->clear();
        ui->comboBox_dababaseT->addItems(table111);
    } else if ( style == FPSO112 )
    {
        ui->comboBox_dababaseT->clear();
        ui->comboBox_dababaseT->addItems(table112);
    } else if ( style == FPSO118 )
    {
        ui->comboBox_dababaseT->clear();
        ui->comboBox_dababaseT->addItems(table118);
    } else {
        QErrorMessage *errDialog = new QErrorMessage(this);
        errDialog->showMessage("The database is not exist!");
        return;
    }
    ui->comboBox_dababaseT->setCurrentIndex(0);
    repaint();
}

void Dialog::setDataList(QString tablename)
{
    if (tablename == "")
        return;
    ui->dbTableList->clear();
    int dbIndex = ui->comboBox_database->currentIndex();
    QString dbName = dbIndexNameMap[dbIndex];
    QStringList dbListItems = dpclass.queryColumnNameListInTable(dbName, tablename);
    ui->dbTableList->addItems(dbListItems);
    repaint();
}

void Dialog::setSelectedDataList()
{
    qDebug() << "enter the function" << endl;
    QList<QListWidgetItem*> selItem = ui->dbTableList->selectedItems();
    QList<QListWidgetItem*>::iterator it;
    QStringList selDataList;

    for(it = selItem.begin(); it != selItem.end(); ++it)
    {
        if (curSelectedListSet.find(*it) == curSelectedListSet.end())
        {
            QString dbName = dbIndexNameMap[ui->comboBox_database->currentIndex()];
            QString tableName = ui->comboBox_dababaseT->currentText();
            QString selColName = dbName + "." + tableName + "." + (*it)->text();
            selDataList << selColName;
            //ui->selectedDataList->addItem(*it);
            curSelectedListSet.insert(*it);
        }
    }
    ui->selectedDataList->addItems(selDataList);
    repaint();
}

Dialog::~Dialog()
{
    delete ui;
}
