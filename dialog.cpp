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

    initComboboxMap();

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

    connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT( addSelectedColList() ) );
    connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT( updateSpinBoxSelCol() ) );

    connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT( delSelectedColList() ) );
    connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT( updateSpinBoxSelCol() ) );
    connect(ui->selectedDataList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT( showItemCurConfigInfo(QListWidgetItem*) ) );

    /**************************************************************
     * set analyse parameter corresponds to selected column data.
     **************************************************************/
    connect(ui->pushButton_saveConfig, SIGNAL(clicked()), this, SLOT( saveConfigtoMap() ) );
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

void Dialog::addSelectedColList()
{
    qDebug() << "enter the function" << endl;
    QList<QListWidgetItem*> addItems = ui->dbTableList->selectedItems();
    QList<QListWidgetItem*>::iterator it;
    QStringList selDataList;

    for(it = addItems.begin(); it != addItems.end(); ++it)
    {
        QString dbName = dbIndexNameMap[ui->comboBox_database->currentIndex()];
        QString tableName = ui->comboBox_dababaseT->currentText();
        QString selColName = dbName + "." + tableName + "." + (*it)->text();
        if (curSelectedListSet.find(selColName) == curSelectedListSet.end())
        {
            selDataList << selColName;
            //ui->selectedDataList->addItem(*it);
            curSelectedListSet.insert(selColName);
        }
    }
    ui->selectedDataList->addItems(selDataList);
    repaint();
}

void Dialog::delSelectedColList()
{
    QList<QListWidgetItem *> delItems = ui->selectedDataList->selectedItems();
    if(delItems.empty())
        return;
    QList<QListWidgetItem *>::iterator it;

    for (it = delItems.begin(); it != delItems.end(); ++it) {
        QString delColName = (*it)->text();
        curSelectedListSet.remove(delColName);

        //qDebug() << ui->selectedDataList->currentRow();
        ui->selectedDataList->takeItem(ui->selectedDataList->currentRow());
        //ui->selectedDataList->removeItemWidget(*it);
    }
    repaint();
}

void Dialog::updateSpinBoxSelCol()
{
    ui->spinBox_selCol->setValue(curSelectedListSet.size());
    //repaint();
}

void Dialog::saveConfigtoMap()
{
    AnalyseParas cur_analyse_paras;

    QListWidgetItem * cur_selected_col = ui->selectedDataList->currentItem();
    if (cur_selected_col == NULL)
        return;
    QString cur_selected_col_text = cur_selected_col->text();
    QString cur_db_name = cur_selected_col_text.section('.', 0, 0);
    QString cur_table_name = cur_selected_col_text.section('.', 1, 1);
    QString cur_col_name = cur_selected_col_text.section('.', 2, 2);

    int cur_frequency = ui->spinBox_frequency->value();
    int cur_time_interval = ui->spinBox_timeInterval->value();
    int cur_analyse_type = ui->comboBox_anaType->currentIndex();
    //QString cur_analyse_type = ui->comboBox_anaType->currentText();
    int cur_filter_type = ui->comboBox_filterType->currentIndex();
    //QString cur_filter_type = ui->comboBox_filterType->currentText();

    bool cur_range_filter = ui->groupBox_rangeFilter->isEnabled();
    double cur_max_filter_value = ui->doubleSpinBox_max->value();
    double cur_min_filter_value = ui->doubleSpinBox_min->value();

    bool cur_time_cont = ui->checkBox_timeCont->isChecked();
    bool cur_data_cont = ui->checkBox_dataCont->isChecked();
    bool cur_consist_check = ui->checkBox_consist->isChecked();
    int cur_process_type = ui->comboBox_processType->currentIndex();
    //QString cur_process_type = ui->comboBox_processType->currentText();
    QDateTime cur_start_time = ui->dateTimeEdit_startTime->dateTime();
    QDateTime cur_end_time = ui->dateTimeEdit_endTime->dateTime();

    map_col_list_analyse_paras[cur_selected_col_text].db_name = cur_db_name;
    map_col_list_analyse_paras[cur_selected_col_text].tb_name = cur_table_name;
    map_col_list_analyse_paras[cur_selected_col_text].col_name = cur_col_name;
    map_col_list_analyse_paras[cur_selected_col_text].frequency = cur_frequency;
    map_col_list_analyse_paras[cur_selected_col_text].time_interval = cur_time_interval;
    map_col_list_analyse_paras[cur_selected_col_text].analyse_type = cur_analyse_type;
    map_col_list_analyse_paras[cur_selected_col_text].filter_type = cur_filter_type;
    map_col_list_analyse_paras[cur_selected_col_text].range_filter = cur_range_filter;
    map_col_list_analyse_paras[cur_selected_col_text].max = cur_max_filter_value;
    map_col_list_analyse_paras[cur_selected_col_text].min = cur_min_filter_value;
    map_col_list_analyse_paras[cur_selected_col_text].time_cont = cur_time_cont;
    map_col_list_analyse_paras[cur_selected_col_text].data_cont = cur_data_cont;
    map_col_list_analyse_paras[cur_selected_col_text].consist_check = cur_consist_check;
    map_col_list_analyse_paras[cur_selected_col_text].process_type = cur_process_type;
    map_col_list_analyse_paras[cur_selected_col_text].start_time = cur_start_time;
    map_col_list_analyse_paras[cur_selected_col_text].end_time = cur_end_time;

    map_col_list_analyse_paras[cur_selected_col_text].printfConfigInfo();
    qDebug() << map_col_list_analyse_paras.size();
}

void Dialog::showItemCurConfigInfo(QListWidgetItem * item)
{
    QString curSelItem = item->text();
    qDebug() << curSelItem;
    if (map_col_list_analyse_paras.find(curSelItem) == map_col_list_analyse_paras.end()) {
        AnalyseParas prime_analyse_paras;
        map_col_list_analyse_paras.insert(curSelItem, prime_analyse_paras);
//        ui->comboBox_anaType->setCurrentIndex(0);
//        ui->comboBox_filterType->setCurrentIndex(0);
//        ui->comboBox_processType->setCurrentIndex(0);
//    } else
//    {
//        ui->comboBox_anaType->setCurrentText(map_col_list_analyse_paras[curSelItem].analyse_type);
//        ui->comboBox_filterType->setCurrentText(map_col_list_analyse_paras[curSelItem].filter_type);
//        ui->comboBox_processType->setCurrentText(map_col_list_analyse_paras[curSelItem].process_type);
    }
//    ui->comboBox_anaType->setCurrentText(map_col_list_analyse_paras[curSelItem].analyse_type);
//    ui->comboBox_filterType->setCurrentText(map_col_list_analyse_paras[curSelItem].filter_type);
//    ui->comboBox_processType->setCurrentText(map_col_list_analyse_paras[curSelItem].process_type);

    ui->comboBox_anaType->setCurrentIndex(map_col_list_analyse_paras[curSelItem].analyse_type);
    ui->comboBox_filterType->setCurrentIndex(map_col_list_analyse_paras[curSelItem].filter_type);
    ui->comboBox_processType->setCurrentIndex(map_col_list_analyse_paras[curSelItem].process_type);

    ui->spinBox_frequency->setValue(map_col_list_analyse_paras[curSelItem].frequency);
    ui->spinBox_timeInterval->setValue(map_col_list_analyse_paras[curSelItem].time_interval);

    if (map_col_list_analyse_paras[curSelItem].range_filter) {
        ui->groupBox_rangeFilter->setChecked(true);
    } else {
        ui->groupBox_rangeFilter->setChecked(false);
    }

    ui->doubleSpinBox_max->setValue(map_col_list_analyse_paras[curSelItem].max);
    ui->doubleSpinBox_min->setValue(map_col_list_analyse_paras[curSelItem].min);

    if (map_col_list_analyse_paras[curSelItem].time_cont)
    {
        ui->checkBox_timeCont->setCheckState(Qt::Checked);
    } else {
        ui->checkBox_timeCont->setCheckState(Qt::Unchecked);
    }

    if (map_col_list_analyse_paras[curSelItem].data_cont)
    {
        ui->checkBox_dataCont->setCheckState(Qt::Checked);
    } else {
        ui->checkBox_dataCont->setCheckState(Qt::Unchecked);
    }

    if (map_col_list_analyse_paras[curSelItem].consist_check)
    {
        ui->checkBox_consist->setCheckState(Qt::Checked);
    } else {
        ui->checkBox_consist->setCheckState(Qt::Unchecked);
    }

    ui->dateTimeEdit_startTime->setDateTime(map_col_list_analyse_paras[curSelItem].start_time);
    ui->dateTimeEdit_endTime->setDateTime(map_col_list_analyse_paras[curSelItem].end_time);
}

void Dialog::initComboboxMap()
{
    /***************************************
     * initial DataBase Index to Name Map
     ***************************************/
    dbIndexNameMap[0] = "111";
    dbIndexNameMap[1] = "112";
    dbIndexNameMap[2] = "118";

    /****************************************
     * initial ComboBox text to index Map
     ****************************************/
//    analyse_type_map.insert(ui->comboBox_anaType->itemText(0), NONEANALYSE);
//    analyse_type_map.insert(ui->comboBox_anaType->itemText(1), MAXVALUE);
//    analyse_type_map.insert(ui->comboBox_anaType->itemText(2), MINVALUE);
//    analyse_type_map.insert(ui->comboBox_anaType->itemText(3), AVERAGEVALUE);

//    filter_type_map.insert(ui->comboBox_filterType->itemText(0), NONEFILTER);
//    filter_type_map.insert(ui->comboBox_filterType->itemText(1), LOWERPASSFILTER);

}

Dialog::~Dialog()
{
    delete ui;
}
