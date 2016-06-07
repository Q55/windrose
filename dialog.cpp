#include "dialog.h"
#include "ui_dialog.h"
#include "formuladialog.h"

#include <QDebug>
#include <QErrorMessage>


void Dialog::initComboboxMap()
{
    /***************************************
     * initial DataBase Index to Name Map
     ***************************************/
    dbIndexNameMap[0] = "111";
    dbIndexNameMap[1] = "112";
    dbIndexNameMap[2] = "118";

    check_type_anti_map.insert(1.0, 0);
    check_type_anti_map.insert(2.0, 1);

    consist_check_anti_map.insert(1.0, 0);
    consist_check_anti_map.insert(2.0, 1);
    consist_check_anti_map.insert(0.5, 2);
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
 //
    ui->setupUi(this);

    initComboboxMap();

    curSelectedListMap.clear();

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
    connect(ui->dbTableList, SIGNAL( itemDoubleClicked(QListWidgetItem*) ), this, SLOT( addSelectedColList(QListWidgetItem*) ) );
    connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT( updateSpinBoxSelCol() ) );
    connect(ui->dbTableList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(updateSpinBoxSelCol(QListWidgetItem*)) );

    connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT( delSelectedColList() ) );
    connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT( updateSpinBoxSelCol() ) );
    connect(ui->selectedDataList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT( showItemCurConfigInfo(QListWidgetItem*) ) );

    //connect(ui->selectedDataList, SIGNAL(itemDoubleClicked(QListWidgetItem*))

    /**************************************************************
     * set analyse parameter corresponds to selected column data.
     **************************************************************/
    connect(ui->pushButton_saveConfig, SIGNAL(clicked()), this, SLOT( saveConfigtoMap() ) );

    connect(ui->pushButton_startDeal, SIGNAL(clicked()), this, SLOT( startPreProcess() ) );
//    connect(ui->pushButton_startDeal, SIGNAL(clicked()), this, SLOT( initProgress() ) );

    connect(&dpclass, SIGNAL( preProcessRate(int) ), ui->progressBar, SLOT( setValue(int) ) );
 //   connect(&dpclass, SIGNAL( preProcessRate(int) ), this, SLOT( setProgressBar(int) ) );
    connect(&dpclass, SIGNAL( preProcessRate(int) ), this, SLOT( setProgressTips(int) ) );

    //========================================================
    connect(&dpclass, SIGNAL( preProcessEnd() ), this, SLOT( setPostProcessRawCol() ) );
    connect(ui->pushButton_inputFormula, SIGNAL(clicked()), this, SLOT( inputFormulaDialog() ) );
}

void Dialog::setProgressTips(int i)
{
    QString progress_tips = QString::number(i, 10);
    progress_tips += " %";
    ui->lineEdit_tips->setText(progress_tips);

}

void Dialog::initProgress()
{
    ui->progressBar->setValue(0);
    setProgressTips(0);
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
    QList<QListWidgetItem*> addItems = ui->dbTableList->selectedItems();
    QList<QListWidgetItem*>::iterator it;
    QStringList selDataItems;

    for(it = addItems.begin(); it != addItems.end(); ++it)
    {
        QString dbName = dbIndexNameMap[ui->comboBox_database->currentIndex()];
        QString tableName = ui->comboBox_dababaseT->currentText();

        AnalyseParas cur_analyse_paras;
        cur_analyse_paras.db_name = dbName;
        cur_analyse_paras.tb_name = tableName;
        cur_analyse_paras.col_name = (*it)->text();

        QString selColName = dbName + "." + tableName + "." + (*it)->text();

        if (curSelectedListMap.find(selColName) == curSelectedListMap.end())
        {            
            //ui->selectedDataList->addItem(*it);
            curSelectedListMap.insert(selColName, 0);
        }
        else
        {
            curSelectedListMap[selColName]++;
            selColName += QString::number(curSelectedListMap[selColName]);
        }
        map_col_list_analyse_paras.insert(selColName, cur_analyse_paras);
        selDataItems << selColName;
    }
    ui->selectedDataList->addItems(selDataItems);
    QString selected_items_first = selDataItems.first();
    QList<QListWidgetItem *> set_item_selected = ui->selectedDataList->findItems(selected_items_first, Qt::MatchFixedString);
    ui->selectedDataList->setCurrentItem(set_item_selected.first());
    repaint();
}

void Dialog::addSelectedColList(QListWidgetItem *item)
{
    addSelectedColList();
}

void Dialog::delSelectedColList()
{
    QList<QListWidgetItem *> delItems = ui->selectedDataList->selectedItems();
    if(delItems.empty())
        return;
    QList<QListWidgetItem *>::iterator it;

    for (it = delItems.begin(); it != delItems.end(); ++it) {
        QString delColName = (*it)->text();

        int pre_row = ui->selectedDataList->currentRow();
        int cur_row = pre_row;
        if (pre_row == map_col_list_analyse_paras.size()-1) {
            cur_row = pre_row-1;
        }

        //curSelectedListMap.remove(delColName);
        if (curSelectedListMap[delColName] == 0)
        {
            curSelectedListMap.remove(delColName);
        }
        else
        {
            curSelectedListMap[delColName]--;
        }
        //qDebug() << ui->selectedDataList->currentRow();
        ui->selectedDataList->takeItem(pre_row);
        ui->selectedDataList->setCurrentRow(cur_row);

        map_col_list_analyse_paras.remove(delColName);
        //ui->selectedDataList->removeItemWidget(*it);
    }
    repaint();
}

void Dialog::updateSpinBoxSelCol()
{
    ui->spinBox_selCol->setValue(map_col_list_analyse_paras.size());
    //repaint();
}

void Dialog::updateSpinBoxSelCol(QListWidgetItem*) {
    updateSpinBoxSelCol();
}

void Dialog::saveConfigtoMap()
{
    QListWidgetItem * cur_selected_col = ui->selectedDataList->currentItem();
    if (cur_selected_col == NULL) {
        QErrorMessage *emptyListErr = new QErrorMessage(this);
        emptyListErr->showMessage("you must select a datalist or some datalists to configuration.");
        return;
    }

//    AnalyseParas cur_analyse_paras;
    QString cur_selected_col_text = cur_selected_col->text();
//    QString cur_db_name = cur_selected_col_text.section('.', 0, 0);
//    QString cur_table_name = cur_selected_col_text.section('.', 1, 1);
//    QString cur_col_name = cur_selected_col_text.section('.', 2, 2);

    int cur_frequency = ui->spinBox_frequency->value();
    int cur_time_interval = ui->spinBox_timeInterval->value();
    int cur_analyse_type = ui->comboBox_anaType->currentIndex();
    //QString cur_analyse_type = ui->comboBox_anaType->currentText();
    int cur_filter_type = ui->comboBox_filterType->currentIndex();
    //QString cur_filter_type = ui->comboBox_filterType->currentText();

    bool cur_range_filter = ui->groupBox_rangeFilter->isChecked();
    double cur_max_filter_value = ui->doubleSpinBox_max->value();
    double cur_min_filter_value = ui->doubleSpinBox_min->value();
    int cur_range_filter_check_type = ui->comboBox_rangeFilterCheckType->currentIndex();

    bool cur_time_cont = ui->groupBox_timeCont->isChecked();
    double cur_time_cont_time_step = ui->doubleSpinBox_timeContTimeStep->value();
    int cur_time_cont_check_type = ui->comboBox_timeContCheckType->currentIndex();

    bool cur_data_cont = ui->groupBox_rangeCont->isChecked();
    double cur_data_cont_gsd = ui->doubleSpinBox_rangeContGsd->value();
    double cur_data_cont_time_step = ui->doubleSpinBox_rangeContTimeStep->value();
    int cur_data_cont_check_type = ui->comboBox_rangeContCheckType->currentIndex();

    bool cur_consist_check = ui->groupBox_interConsis->isChecked();
    QString cur_expression = ui->lineEdit_preFormula->text();
    int cur_consist_check_type = ui->comboBox_interConsisCheckType->currentIndex();
    //int cur_process_type = ui->comboBox_processType->currentIndex();

    //QString cur_process_type = ui->comboBox_processType->currentText();
    QDateTime cur_start_time = ui->dateTimeEdit_startTime->dateTime();
    QDateTime cur_end_time = ui->dateTimeEdit_endTime->dateTime();

//    map_col_list_analyse_paras[cur_selected_col_text].db_name = cur_db_name;
//    map_col_list_analyse_paras[cur_selected_col_text].tb_name = cur_table_name;
//    map_col_list_analyse_paras[cur_selected_col_text].col_name = cur_col_name;
    map_col_list_analyse_paras[cur_selected_col_text].frequency = cur_frequency;
    map_col_list_analyse_paras[cur_selected_col_text].time_interval = cur_time_interval;
    map_col_list_analyse_paras[cur_selected_col_text].analyse_type = cur_analyse_type;
    map_col_list_analyse_paras[cur_selected_col_text].filter_type = cur_filter_type;

    map_col_list_analyse_paras[cur_selected_col_text].range_filter = cur_range_filter;
    map_col_list_analyse_paras[cur_selected_col_text].max = cur_max_filter_value;
    map_col_list_analyse_paras[cur_selected_col_text].min = cur_min_filter_value;
    double cur_range_filter_type_double = check_type[cur_range_filter_check_type];
    map_col_list_analyse_paras[cur_selected_col_text].filter_type = cur_range_filter_type_double;

    map_col_list_analyse_paras[cur_selected_col_text].time_cont = cur_time_cont;
    map_col_list_analyse_paras[cur_selected_col_text].time_cont_time_step = cur_time_cont_time_step;
    double cur_time_cont_check_type_double = check_type[cur_time_cont_check_type];
    map_col_list_analyse_paras[cur_selected_col_text].time_cont_check_type = cur_time_cont_check_type_double;

    map_col_list_analyse_paras[cur_selected_col_text].data_cont = cur_data_cont;
    map_col_list_analyse_paras[cur_selected_col_text].data_cont_gsd = cur_data_cont_gsd;
    map_col_list_analyse_paras[cur_selected_col_text].data_cont_time_step = cur_data_cont_time_step;
    double cur_data_cont_check_type_double = check_type[cur_data_cont_check_type];
    map_col_list_analyse_paras[cur_selected_col_text].data_cont_check_type = cur_data_cont_check_type_double;

    map_col_list_analyse_paras[cur_selected_col_text].consist_check = cur_consist_check;
    map_col_list_analyse_paras[cur_selected_col_text].expression = cur_expression;
    double cur_consist_check_type_double = consist_check_type[cur_consist_check_type];
    map_col_list_analyse_paras[cur_selected_col_text].consist_check_type = cur_consist_check_type_double;
    //map_col_list_analyse_paras[cur_selected_col_text].process_type = cur_process_type;
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
        qDebug() << "Development ERROR!";
        return;
//        AnalyseParas prime_analyse_paras;
//        map_col_list_analyse_paras.insert(curSelItem, prime_analyse_paras);
    }
    AnalyseParas * cur_analyse_paras = &map_col_list_analyse_paras[curSelItem];

    ui->comboBox_anaType->setCurrentIndex(cur_analyse_paras->analyse_type);
    ui->comboBox_filterType->setCurrentIndex(cur_analyse_paras->filter_type);
    //ui->comboBox_processType->setCurrentIndex(cur_analyse_paras->process_type);

    ui->spinBox_frequency->setValue(cur_analyse_paras->frequency);
    ui->spinBox_timeInterval->setValue(cur_analyse_paras->time_interval);

    if (cur_analyse_paras->range_filter) {
        ui->groupBox_rangeFilter->setChecked(true);
    } else {
        ui->groupBox_rangeFilter->setChecked(false);
    }

    ui->doubleSpinBox_max->setValue(cur_analyse_paras->max);
    ui->doubleSpinBox_min->setValue(cur_analyse_paras->min);

    if (cur_analyse_paras->time_cont)
    {
        ui->groupBox_timeCont->setChecked(true);
    } else {
        ui->groupBox_timeCont->setChecked(false);
    }
    ui->doubleSpinBox_timeContTimeStep->setValue(cur_analyse_paras->time_cont_time_step);
    int time_cont_check_type_index = check_type_anti_map[cur_analyse_paras->time_cont_check_type];
    ui->comboBox_timeContCheckType->setCurrentIndex(time_cont_check_type_index);

    if (cur_analyse_paras->data_cont)
    {
        ui->groupBox_rangeCont->setChecked(true);
    } else {
        ui->groupBox_rangeCont->setChecked(false);
    }
    ui->doubleSpinBox_rangeContGsd->setValue(cur_analyse_paras->data_cont_gsd);
    ui->doubleSpinBox_rangeContTimeStep->setValue(cur_analyse_paras->data_cont_time_step);
    int data_cont_check_type_index = check_type_anti_map[cur_analyse_paras->data_cont_check_type];
    ui->comboBox_rangeContCheckType->setCurrentIndex(data_cont_check_type_index);

    if (cur_analyse_paras->consist_check)
    {
        ui->groupBox_interConsis->setChecked(true);
    } else {
        ui->groupBox_interConsis->setChecked(false);
    }
    ui->lineEdit_preFormula->setText(cur_analyse_paras->expression);
    int inter_consis_check_type_index = consist_check_anti_map[cur_analyse_paras->consist_check_type];
    ui->comboBox_interConsisCheckType->setCurrentIndex(inter_consis_check_type_index);

    ui->dateTimeEdit_startTime->setDateTime(cur_analyse_paras->start_time);
    ui->dateTimeEdit_endTime->setDateTime(cur_analyse_paras->end_time);
}

void Dialog::startPreProcess()
{
    int all_sel_col_row = ui->selectedDataList->count();
    //qDebug() << all_sel_col_row;
    for (int cur_row = 0; cur_row < all_sel_col_row; ++cur_row)
    {
        QString sel_col_name = ui->selectedDataList->item(cur_row)->text();
        if (map_col_list_analyse_paras.find(sel_col_name) == map_col_list_analyse_paras.end())
        {
            AnalyseParas init_analyse_paras;
            init_analyse_paras.db_name = sel_col_name.section('.', 0, 0);
            init_analyse_paras.tb_name = sel_col_name.section('.', 1, 1);
            init_analyse_paras.col_name = sel_col_name.section('.', 2, 2);
            map_col_list_analyse_paras.insert(sel_col_name, init_analyse_paras);
        }
    }
    //for test
//    qDebug() << map_col_list_analyse_paras.size();
//    for (auto it = map_col_list_analyse_paras.begin(); it != map_col_list_analyse_paras.end(); ++it)
//    {
//        it.value().printfConfigInfo();
//    }
    dpclass.preProccess(map_col_list_analyse_paras);
}
//==========================================================================
void Dialog::setPostProcessRawCol()
{
    ui->listWidget_postProcessRaw->addItems(dpclass.getNamePostProcessData());
    repaint();
}

void Dialog::inputFormulaDialog()
{
    FormulaDialog *formula_input_dialog = new FormulaDialog;
    formula_input_dialog->show();

}

Dialog::~Dialog()
{
    delete ui;
}
