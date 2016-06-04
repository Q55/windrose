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

    //initial Table list
    QStringList strings;
    strings << "calcforce" << "gpsfpd" << "gpsimu" << "inclinometer" << "statistics" << "warning" << "wgpacurrentspeed";
    strings << "wgpawave" << "windsensor";
    iniTableList(0, strings);

    strings.clear();

    //QStringList strings2;
    strings << "bar" << "enlight1" << "enlight2" << "enlight3" << "enlight4" << "enlight5" << "enlight6" << "enlight7";;
    strings << "enlight8" << "fbg" << "foxboro" << "gps" << "inclinometer1" << "inv12" << "inv4" << "spm" << "warnings";
    strings << "wgpacurrentspeed" << "wgpawave" << "windsensor";
    iniTableList(1, strings);

    strings.clear();

    strings << "calcforce" << "gpsfpd" << "gpsimu" << "heave" << "inclinometer" << "statistics" << "temperature" << "warning";
    strings << "waveradar" << "waveradarsp" << "windsensor";
    iniTableList(2, strings);

    ui->comboBox_database->setCurrentIndex(1);
    int database = ui->comboBox_database->currentIndex();
    setDataTable(database);

 //   connect(ui->comboBox_database, SIGNAL(currentIndexChanged(int)), this, SIGNAL(comboboxDatabase_changed(int) ) );
    connect(ui->comboBox_database, SIGNAL( currentIndexChanged(int) ), this, SLOT( setDataTable(int) ) );
}

void Dialog::iniTableList(int index, QStringList strings)
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
        qDebug() << "int the function setDataTable:" << endl;
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

Dialog::~Dialog()
{
    delete ui;
}
