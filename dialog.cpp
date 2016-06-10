#include "dialog.h"
#include "ui_dialog.h"
#include "postexprdialog.h"
#include "scatterplot.h"

#include <QDebug>
#include <QErrorMessage>
#include <QHBoxLayout>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    initComboboxMap();
    pre_selcol_count_map.clear();
    //pre_sel_colrepeatlist_map.clear();

    // pre-processing
    //initial Table list
    initTableList(0, dpclass.queryTableNameListbyDBName(dbIndexNameMap[0]));
    initTableList(1, dpclass.queryTableNameListbyDBName(dbIndexNameMap[1]));
    initTableList(2, dpclass.queryTableNameListbyDBName(dbIndexNameMap[2]));
    // default selected database, and default selected table.
    ui->comboBox_db_list->setCurrentIndex(1);
    setDBTableList(ui->comboBox_db_list->currentIndex());
    setTableColList(ui->comboBox_tb_list->currentText());
    // signals and slots for database, table, colume.
    connect(ui->comboBox_db_list, SIGNAL( currentIndexChanged(int) ), this, SLOT( setDBTableList(int) ) );
    connect(ui->comboBox_tb_list, SIGNAL( currentIndexChanged(QString) ), this, SLOT( setTableColList(QString) ) );
    // select col list:
    connect(ui->pushButton_pre_add_cols, SIGNAL(clicked()), this, SLOT( preAddSelectedColList() ) );
    connect(ui->pre_table_cols_list, SIGNAL( itemDoubleClicked(QListWidgetItem*) ), this, SLOT( preAddSelectedColList(QListWidgetItem*) ) );
    connect(ui->pushButton_pre_add_cols, SIGNAL(clicked()), this, SLOT( updateSpinBoxSelCol() ) );
    connect(ui->pre_table_cols_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(updateSpinBoxSelCol(QListWidgetItem*)) );

    connect(ui->pushButton_pre_del_cols, SIGNAL(clicked()), this, SLOT( preDelSelectedColList() ) );
    connect(ui->pushButton_pre_del_cols, SIGNAL(clicked()), this, SLOT( updateSpinBoxSelCol() ) );
    connect(ui->pre_selected_col_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT( showItemCurConfigInfo(QListWidgetItem*) ) );

    // set analyse parameter corresponds to selected column data.
    connect(ui->pushButton_saveConfig, SIGNAL(clicked()), this, SLOT( saveConfigToMap() ) );
    connect(ui->pushButton_clear_pre, SIGNAL(clicked()), this, SLOT(clearPreCache()));
    connect(ui->pushButton_startDeal, SIGNAL(clicked()), this, SLOT( startPreProcess() ) );
    connect(ui->pushButton_saveData, SIGNAL(clicked()), this, SLOT(exportDataToFile()) );

    connect(&dpclass, SIGNAL( preProcessRate(int) ), ui->progressBar, SLOT( setValue(int) ) );
    connect(&dpclass, SIGNAL( preProcessRate(int) ), this, SLOT( setProgressTips(int) ) );


    //========================================================
    // post-processing
    connect(&dpclass, SIGNAL( preProcessEnd() ), this, SLOT( setPostProcessRawCol() ) );
    connect(ui->pushButton_post_add_cols, SIGNAL(clicked()), this, SLOT(postAddSelectedColList()));
    connect(ui->post_proc_raw_col_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(postAddSelectedColList(QListWidgetItem*)));
    connect(ui->pushButton_post_del_cols, SIGNAL(clicked()), this, SLOT(postDelSelectedColList()));
    connect(ui->pushButton_post_input_expr, SIGNAL(clicked()), this, SLOT( postPopExprDlg() ) );
    connect(ui->post_proc_after_col_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(showSelColData())); // show 1000 data.

    //connect(ui->comboBox_curveType, SIGNAL(currentIndexChanged(int)), this, SLOT(setPlotMode(int)));
}

void Dialog::setProgressTips(int i) {

    if (i == 0) {
        initProgress();
    }
    QString progress_tips = QString::number(i, 10);
    qDebug()<<"progress_tips = "<<progress_tips;
    progress_tips += " %";
    ui->lineEdit_tips->setText(progress_tips);
    qDebug()<<"tips: "<<progress_tips;
    repaint();
}

void Dialog::initProgress()
{
    ui->progressBar->setValue(0);
    ui->progressBar->show();
    ui->lineEdit_tips->setText("0");
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

void Dialog::setDBTableList( int style ) {
    if ( style == FPSO111 ) {
        ui->comboBox_tb_list->clear();
        ui->comboBox_tb_list->addItems(table111);
    } else if ( style == FPSO112 ) {
        ui->comboBox_tb_list->clear();
        ui->comboBox_tb_list->addItems(table112);
    } else if ( style == FPSO118 ) {
        ui->comboBox_tb_list->clear();
        ui->comboBox_tb_list->addItems(table118);
    } else {
        QErrorMessage *errDialog = new QErrorMessage(this);
        errDialog->showMessage("The database is not exist!");
        return;
    }
    ui->comboBox_tb_list->setCurrentIndex(0);
    repaint();
}

void Dialog::setTableColList(QString tablename) {
    if (tablename == "")
        return;
    int dbIndex = ui->comboBox_db_list->currentIndex();
    QString dbName = dbIndexNameMap[dbIndex];
    QStringList dbListItems = dpclass.queryColumnNameListInTable(dbName, tablename);
    ui->pre_table_cols_list->clear();
    ui->pre_table_cols_list->addItems(dbListItems);
    ui->pre_table_cols_list->setCurrentItem(0);
    repaint();
}

void Dialog::preAddSelectedColList(QListWidgetItem *item) {
    preAddSelectedColList();
}

void Dialog::preAddSelectedColList() {
    QList<QListWidgetItem*> addItems = ui->pre_table_cols_list->selectedItems();
    if (addItems.size() == 0)
        return;
    QStringList selected_col_items;

    for(QList<QListWidgetItem*>::iterator it = addItems.begin(); it != addItems.end(); ++it) {
        QString dbName = dbIndexNameMap[ui->comboBox_db_list->currentIndex()];
        QString tableName = ui->comboBox_tb_list->currentText();

        AnalyseParas cur_analyse_paras;
        cur_analyse_paras.db_name = dbName;
        cur_analyse_paras.tb_name = tableName;
        cur_analyse_paras.col_name = (*it)->text();

        QString sel_col_name = dbName + "." + tableName + "." + (*it)->text();

        if (pre_selcol_count_map.find(sel_col_name) == pre_selcol_count_map.end()) {
            pre_selcol_count_map.insert(sel_col_name, 1);
        } else {
            pre_selcol_count_map[sel_col_name]++;
            sel_col_name += QString::number(pre_selcol_count_map[sel_col_name]);
        }
        map_col_list_analyse_paras.insert(sel_col_name, cur_analyse_paras);
        selected_col_items << sel_col_name;
    }
    ui->pre_selected_col_list->addItems(selected_col_items);
    QList<QListWidgetItem *> set_item_selected = ui->pre_selected_col_list->findItems(
                selected_col_items.first(), Qt::MatchFixedString);
    ui->pre_selected_col_list->setCurrentItem(set_item_selected.first());
    repaint();
}

void Dialog::preDelSelectedColList() {
    QList<QListWidgetItem *> delItems = ui->pre_selected_col_list->selectedItems();
    if(delItems.empty()) return;

    int cur_row = 0;
    for (QList<QListWidgetItem *>::iterator it = delItems.begin(); it != delItems.end(); ++it) {
        int pre_row = ui->pre_selected_col_list->row(*it);
        cur_row = pre_row;
        if (pre_row == map_col_list_analyse_paras.size()-1)
            cur_row = pre_row-1;

        map_col_list_analyse_paras.remove((*it)->text());
        delete ui->pre_selected_col_list->takeItem(pre_row);
    }
    ui->pre_selected_col_list->setCurrentRow(cur_row);
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

void Dialog::saveConfigToMap() {
    QList<QListWidgetItem*> selected_items = ui->pre_selected_col_list->selectedItems();
    if (selected_items.size() == 0) {
        QErrorMessage *emptyListErr = new QErrorMessage(this);
        emptyListErr->showMessage("Please Select Column(s) First!");
        return;
    }

    for (auto it = selected_items.begin(); it != selected_items.end(); ++it) {
        QString sel_col_name = (*it)->text();

        map_col_list_analyse_paras[sel_col_name].frequency = ui->spinBox_frequency->value();
        map_col_list_analyse_paras[sel_col_name].time_interval = ui->spinBox_timeInterval->value();
        map_col_list_analyse_paras[sel_col_name].analyse_type = ui->comboBox_anaType->currentIndex();
        map_col_list_analyse_paras[sel_col_name].filter_type = ui->comboBox_filterType->currentIndex();

        map_col_list_analyse_paras[sel_col_name].range_filter = ui->groupBox_rangeFilter->isChecked();
        map_col_list_analyse_paras[sel_col_name].max = ui->doubleSpinBox_max->value();
        map_col_list_analyse_paras[sel_col_name].min = ui->doubleSpinBox_min->value();
        map_col_list_analyse_paras[sel_col_name].range_filter_check_type = check_type[ui->comboBox_rangeFilterCheckType->currentIndex()];

        map_col_list_analyse_paras[sel_col_name].time_cont = ui->groupBox_timeCont->isChecked();
        map_col_list_analyse_paras[sel_col_name].time_cont_time_step = ui->doubleSpinBox_timeContTimeStep->value();
        map_col_list_analyse_paras[sel_col_name].time_cont_check_type = check_type[ui->comboBox_timeContCheckType->currentIndex()];

        map_col_list_analyse_paras[sel_col_name].data_cont = ui->groupBox_rangeCont->isChecked();
        map_col_list_analyse_paras[sel_col_name].data_cont_gsd = ui->doubleSpinBox_rangeContGsd->value();
        map_col_list_analyse_paras[sel_col_name].data_cont_time_step = ui->doubleSpinBox_rangeContTimeStep->value();
        map_col_list_analyse_paras[sel_col_name].data_cont_check_type = check_type[ui->comboBox_rangeContCheckType->currentIndex()];

        map_col_list_analyse_paras[sel_col_name].consist_check = ui->groupBox_interConsis->isChecked();
        map_col_list_analyse_paras[sel_col_name].var_name = ui->lineEdit_preVarName->text();
        map_col_list_analyse_paras[sel_col_name].expression = ui->lineEdit_preFormula->text();
        map_col_list_analyse_paras[sel_col_name].consist_check_type = consist_check_type[ui->comboBox_interConsisCheckType->currentIndex()];

        map_col_list_analyse_paras[sel_col_name].start_time = ui->dateTimeEdit_startTime->dateTime();
        map_col_list_analyse_paras[sel_col_name].end_time = ui->dateTimeEdit_endTime->dateTime();
        //map_col_list_analyse_paras[sel_col_name].printfConfigInfo();
    }
}

void Dialog::showItemCurConfigInfo(QListWidgetItem * item) {
    QString curSelItem = item->text();
    if (map_col_list_analyse_paras.find(curSelItem) == map_col_list_analyse_paras.end()) {
        qDebug() << "Development ERROR!";
        return;
//        AnalyseParas prime_analyse_paras;
//        map_col_list_analyse_paras.insert(curSelItem, prime_analyse_paras);
    }
    AnalyseParas &cur_analyse_paras = map_col_list_analyse_paras[curSelItem];
    ui->spinBox_frequency->setValue(cur_analyse_paras.frequency);
    ui->spinBox_timeInterval->setValue(cur_analyse_paras.time_interval);
    ui->comboBox_anaType->setCurrentIndex(cur_analyse_paras.analyse_type);
    ui->comboBox_filterType->setCurrentIndex(cur_analyse_paras.filter_type);

    ui->groupBox_rangeFilter->setChecked(cur_analyse_paras.range_filter);
    ui->doubleSpinBox_max->setValue(cur_analyse_paras.max);
    ui->doubleSpinBox_min->setValue(cur_analyse_paras.min);

    ui->groupBox_timeCont->setChecked(cur_analyse_paras.time_cont);
    ui->doubleSpinBox_timeContTimeStep->setValue(cur_analyse_paras.time_cont_time_step);
    ui->comboBox_timeContCheckType->setCurrentIndex(check_type_anti_map[cur_analyse_paras.time_cont_check_type]);

    ui->groupBox_rangeCont->setChecked(cur_analyse_paras.data_cont);
    ui->doubleSpinBox_rangeContGsd->setValue(cur_analyse_paras.data_cont_gsd);
    ui->doubleSpinBox_rangeContTimeStep->setValue(cur_analyse_paras.data_cont_time_step);
    ui->comboBox_rangeContCheckType->setCurrentIndex(check_type_anti_map[cur_analyse_paras.data_cont_check_type]);

    ui->groupBox_interConsis->setChecked(cur_analyse_paras.consist_check);
    ui->lineEdit_preVarName->setText(cur_analyse_paras.var_name);
    ui->lineEdit_preFormula->setText(cur_analyse_paras.expression);
    ui->comboBox_interConsisCheckType->setCurrentIndex(consist_check_anti_map[cur_analyse_paras.consist_check_type]);

    ui->dateTimeEdit_startTime->setDateTime(cur_analyse_paras.start_time);
    ui->dateTimeEdit_endTime->setDateTime(cur_analyse_paras.end_time);
}

void Dialog::exportDataToFile() {
    if (dpclass.getAfterDataMapSize() <= 0) {
        QErrorMessage * errDialog = new QErrorMessage();
        errDialog->showMessage("Please Press 'Start Process' First!");
        return;
    }

    QDir dir;
    QString cur_path = dir.currentPath();
    //QString dir_name = QFileDialog::getExistingDirectory(this, tr("Open Directory"), cur_path,
    //                                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString dir_name = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/Users/lishiqiang/Desktop",
                                                          QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    dpclass.exportDataToFiles(dir_name, true); // write raw_data
    dpclass.exportDataToFiles(dir_name, false);// write pre_processed_data
}

void Dialog::startPreProcess()
{
    int all_sel_col_row = ui->pre_selected_col_list->count();
    //qDebug() << all_sel_col_row;
    for (int cur_row = 0; cur_row < all_sel_col_row; ++cur_row)
    {
        QString sel_col_name = ui->pre_selected_col_list->item(cur_row)->text();
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
    dpclass.preProccess(map_col_list_analyse_paras);
}

void Dialog::clearPreCache(){
    QMessageBox msgBox;
    msgBox.setText("Clear All Cached Data in Memory?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Ok) {
        dpclass.clearRawDataMap();
        dpclass.clearAfterPreProcDataMap();
        dpclass.clearFreqList();

        //pre_sel_colrepeatlist_map.clear();
        pre_selcol_count_map.clear();
        map_col_list_analyse_paras.clear();

        ui->pre_selected_col_list->clear();
        ui->post_proc_raw_col_list->clear();
        ui->post_proc_after_col_list->clear();

        ui->spinBox_selCol->setValue(map_col_list_analyse_paras.size());

        QMessageBox msgBox;
        msgBox.setText("All Cached Data Cleared!");
        msgBox.exec();
    }
}

//==========================================================================
//post process
void Dialog::setPostProcessRawCol() {
    ui->post_proc_raw_col_list->addItems(dpclass.getNamePostProcessData());
    repaint();
}

void Dialog::postAddSelectedColList() {
    QList<QListWidgetItem*> add_items = ui->post_proc_raw_col_list->selectedItems();
    if (add_items.size() <= 0) {
        //qDebug()<<"Please selecte column(s).";
        return;
    }
    QStringList selected_col_items;
    auto exist_cols = dpclass.getPostProcDataMap();
    for (auto it = add_items.begin(); it != add_items.end(); ++it) {
        QString col_name = (*it)->text();
        if(exist_cols.find(col_name) == exist_cols.end()) // cannot add duplicate columns in post process.
            selected_col_items << col_name;
    }
    if (selected_col_items.size() <= 0 ) {
        //qDebug()<<"Please don't select duplicate column(s).";
        return;
    }
    dpclass.addColsToPostProcDataDirectly(selected_col_items);
    ui->post_proc_after_col_list->addItems(selected_col_items);
    QList<QListWidgetItem *> set_item_selected = ui->post_proc_after_col_list->findItems(
                selected_col_items.first(), Qt::MatchFixedString);
    ui->post_proc_after_col_list->setCurrentItem(set_item_selected.first());
    repaint();
}

void Dialog::postDelSelectedColList() {
    QList<QListWidgetItem *> del_items = ui->post_proc_after_col_list->selectedItems();
    if (del_items.size() <= 0) return;

    int cur_row = 0;
    QStringList del_col_list;
    for (auto it = del_items.begin(); it != del_items.end(); ++it) {
        int pre_row = ui->post_proc_after_col_list->row(*it);
        cur_row = pre_row;
        if (pre_row == ui->post_proc_after_col_list->count())
            cur_row = pre_row - 1;

        del_col_list << (*it)->text();
        delete ui->post_proc_after_col_list->takeItem(pre_row);
    }
    dpclass.delColsFromPostProcDataByName(del_col_list);
    ui->post_proc_after_col_list->setCurrentRow(cur_row);
    repaint();
}

void Dialog::postPopExprDlg() {
    QList<QListWidgetItem *> sel_col_items = ui->post_proc_raw_col_list->selectedItems();
    int size = sel_col_items.size();
    if (size <= 0 || size >= 3) {
        QMessageBox msgBox;
        msgBox.setText("Please Select 1 col or 2 cols data.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        //int ret = msgBox.exec();
        msgBox.exec();
        return;
    }

    QStringList selcols;
    for (auto it = sel_col_items.begin(); it != sel_col_items.end(); ++it) {
        selcols<<(*it)->text();
    }

    PostExprDialog *expr_dlg = new PostExprDialog(selcols);
    expr_dlg->show();

    connect(expr_dlg, SIGNAL(postExprParas(bool, QString, int, double, bool, QString, int, QString)), this,
            SLOT(parsePostExpr(bool, QString, int, double, bool, QString, int, QString)));
}

void Dialog::parsePostExpr(bool scalar_checked, QString scalar_data, int scalar_op, double scalar_val, bool vec_checked,
                           QString vec_data1, int vec_op, QString vec_data2) {
    QString new_col_name;
    if(scalar_checked) {
        new_col_name = dpclass.addColToPostProcDataByExpr(true, scalar_data, "", scalar_op, scalar_val);
    } else if (vec_checked) {
        new_col_name = dpclass.addColToPostProcDataByExpr(false, vec_data1, vec_data2, vec_op, 0.0);
    }
    if (new_col_name != "")
        ui->post_proc_after_col_list->addItem(new_col_name);
    repaint();
}

void Dialog::showSelColData() {
    QString sel_col = ui->post_proc_after_col_list->currentItem()->text();
    QVector<double> *col_data = NULL;
    auto post_data_map = dpclass.getPostProcDataMap();
    if (post_data_map.find(sel_col) != post_data_map.end()) {
        col_data = &post_data_map[sel_col];
    } else {
        col_data->clear();
    }

    for (int i = 1; i <= 1000 && i <= col_data->size(); ++i) {
        QTableWidgetItem * item1 = new QTableWidgetItem(QString::number(i));
        ui->tableWidget_2->setItem(i-1, 0, item1);

        QTableWidgetItem * item2 = new QTableWidgetItem(QString::number(col_data->at(i - 1)));
        ui->tableWidget_2->setItem(i-1, 1, item2);
    }
    ui->tableWidget_2->resizeColumnsToContents();
    ui->tableWidget_2->resizeRowsToContents();
    ui->tableWidget_2->repaint();
}

void Dialog::setPlotMode(int style)
{
    if (style == CURVE)
    {

    }
    else if (style == SCATTER)
    {
         ScatterPlot *scatter_graph = new ScatterPlot();
         QVector<double> x, y;
         for (int i = 0; i < 100; ++i) {
             x.append( i * 1.1 );
             y.append( i * 2.2 );
         }

         scatter_graph->setSamples(x, y);
         scatter_graph->setXAxisLabel("x轴");
         scatter_graph->setYAxisLabel("y轴");
         scatter_graph->resize(800, 600);
//         QHBoxLayout *layout = new QHBoxLayout(scatter_graph);
//         layout->setContentsMargins( 0, 0, 0, 0);
//         layout->addWidget( scatter_graph );
         scatter_graph->show();

         //scatter_graph->repaint();
    }
    repaint();
}

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

Dialog::~Dialog()
{
    delete ui;
}
