#include "dialog.h"
#include "ui_dialog.h"
#include "postexprdialog.h"
#include "qwtgraphplotcustom.h"
#include "qwtpolarwindroseplot.h"
#include "qchartwindroseplot.h"

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
    connect(ui->pushButton_first1000_records, SIGNAL(clicked()), this, SLOT(showSelColDataFirst1000()));
    connect(ui->pushButton_pre1000_records, SIGNAL(clicked()), this, SLOT(showSelColDataPre1000()));
    connect(ui->pushButton_last1000_records, SIGNAL(clicked()), this, SLOT(showSelColDataLast1000()));
    connect(ui->pushButton_post1000_records, SIGNAL(clicked()), this, SLOT(showSelColDataPost1000()));

    // post-processing: data analysis
    connect(ui->pushButton_post_start_analyse, SIGNAL(clicked()), this, SLOT(postStartDataAnalysis()));
    connect(ui->toolBox_analysis_data, SIGNAL(currentChanged(int)), this, SLOT(postPrepareDataForAnalysis(int)));
    connect(ui->pushButton_clear_post, SIGNAL(clicked()), this, SLOT(clearPostCache()));

    // post draw graph
    connect(ui->pushButton_add_xdata, SIGNAL(clicked()), this, SLOT(postAddXAxisData()));
    connect(ui->pushButton_del_xdata, SIGNAL(clicked()), this, SLOT(postDelXAxisData()));
    connect(ui->pushButton_add_ydata, SIGNAL(clicked()), this, SLOT(postAddYAxisData()));
    connect(ui->pushButton_del_ydata, SIGNAL(clicked()), this, SLOT(postDelYAxisData()));
    connect(ui->pushButton_start_drawgraph, SIGNAL(clicked()), this, SLOT(postStartDrawGraph()));
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
        dpclass.clearPostproc_data_map();

        //pre_sel_colrepeatlist_map.clear();
        pre_selcol_count_map.clear();
        map_col_list_analyse_paras.clear();

        ui->pre_selected_col_list->clear();
        ui->post_proc_raw_col_list->clear();
        ui->post_proc_after_col_list->clear();
        ui->tableWidget_col_data_details->clear();
        ui->xaxis_data_list->clear();
        ui->yaxis_data_list->clear();
        ui->label_selcol_totalcount->setText("0");
        ui->comboBox_correlation_x->setItemText(0, "0");
        ui->comboBox_correlation_x->setItemText(1, "1");
        ui->comboBox_correlation_y->setItemText(0, "0");
        ui->comboBox_correlation_y->setItemText(1, "1");
        ui->comboBox_weightfit_x->setItemText(0, "0");
        ui->comboBox_weightfit_x->setItemText(1, "1");
        ui->comboBox_weightfit_y->setItemText(0, "0");
        ui->comboBox_weightfit_y->setItemText(1, "1");
        show_data_details_col_name.clear();

        ui->spinBox_selCol->setValue(map_col_list_analyse_paras.size());

        QMessageBox msgBox;
        msgBox.setText("All Cached Data Cleared!");
        msgBox.exec();
    }
}

void Dialog::clearPostCache() {
    QMessageBox msgBox;
    msgBox.setText("Clear Post Cached Data in Memory?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Ok) {
        dpclass.clearPostproc_data_map();
        ui->post_proc_after_col_list->clear();
        ui->tableWidget_col_data_details->clear();
        ui->xaxis_data_list->clear();
        ui->yaxis_data_list->clear();
        ui->label_selcol_totalcount->setText("0");
        ui->comboBox_correlation_x->setItemText(0, "0");
        ui->comboBox_correlation_x->setItemText(1, "1");
        ui->comboBox_correlation_y->setItemText(0, "0");
        ui->comboBox_correlation_y->setItemText(1, "1");
        ui->comboBox_weightfit_x->setItemText(0, "0");
        ui->comboBox_weightfit_x->setItemText(1, "1");
        ui->comboBox_weightfit_y->setItemText(0, "0");
        ui->comboBox_weightfit_y->setItemText(1, "1");
        show_data_details_col_name.clear();

        QMessageBox msgBox;
        msgBox.setText("All Cached Data Cleared!");
        msgBox.exec();
    }
}

//==========================================================================
//post process
void Dialog::setPostProcessRawCol() {
    ui->post_proc_raw_col_list->clear();
    ui->post_proc_after_col_list->clear();
    dpclass.clearPostproc_data_map();
    ui->xaxis_data_list->clear();
    ui->yaxis_data_list->clear();
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
    ui->post_proc_after_col_list->repaint();
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
    ui->post_proc_after_col_list->repaint();
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
    show_data_details_col_name = ui->post_proc_after_col_list->currentItem()->text();;
    QVector<double> *col_data = NULL;
    auto post_data_map = dpclass.getPostProcDataMap();
    if (post_data_map.find(show_data_details_col_name) != post_data_map.end()) {
        col_data = &post_data_map[show_data_details_col_name];
    } else {
        col_data->clear();
    }

    for (int i = 1; i <= 1000 && i <= col_data->size(); ++i) {
        QTableWidgetItem * item1 = new QTableWidgetItem(QString::number(i));
        ui->tableWidget_col_data_details->setItem(i-1, 0, item1);

        QTableWidgetItem * item2 = new QTableWidgetItem(QString::number(col_data->at(i - 1)));
        ui->tableWidget_col_data_details->setItem(i-1, 1, item2);
    }
    ui->tableWidget_col_data_details->setColumnWidth(0, 50);
    ui->tableWidget_col_data_details->setColumnWidth(1, 50);
    //ui->tableWidget_col_data_details->resizeColumnsToContents();
    //ui->tableWidget_col_data_details->resizeRowsToContents();
    ui->tableWidget_col_data_details->repaint();
    ui->label_selcol_totalcount->setText(QString::number(col_data->size()));
    ui->label_selcol_totalcount->setStyleSheet("color: rgb(231,66,67);");
}

void Dialog::showSelColDataFirst1000() {
    if (show_data_details_col_name.isNull()) {
        qDebug()<<"Please select a col first.";
        return;
    }

    QVector<double> *col_data = NULL;
    auto post_data_map = dpclass.getPostProcDataMap();
    if (post_data_map.find(show_data_details_col_name) != post_data_map.end()) {
        col_data = &post_data_map[show_data_details_col_name];
    } else {
        col_data->clear();
    }

    for (int i = 1; i <= 1000 && i <= col_data->size(); ++i) {
        QTableWidgetItem * item1 = new QTableWidgetItem(QString::number(i));
        ui->tableWidget_col_data_details->setItem(i-1, 0, item1);

        QTableWidgetItem * item2 = new QTableWidgetItem(QString::number(col_data->at(i - 1)));
        ui->tableWidget_col_data_details->setItem(i-1, 1, item2);
    }
    ui->tableWidget_col_data_details->setColumnWidth(0, 50);
    ui->tableWidget_col_data_details->setColumnWidth(1, 50);
    //ui->tableWidget_col_data_details->resizeColumnsToContents();
    //ui->tableWidget_col_data_details->resizeRowsToContents();
    ui->tableWidget_col_data_details->repaint();
}

void Dialog::showSelColDataLast1000() {
    if (show_data_details_col_name.isNull()) {
        qDebug()<<"Please select a col first.";
        return;
    }

    QVector<double> *col_data = NULL;
    auto post_data_map = dpclass.getPostProcDataMap();
    if (post_data_map.find(show_data_details_col_name) != post_data_map.end()) {
        col_data = &post_data_map[show_data_details_col_name];
    } else {
        col_data->clear();
    }

    int base = 1;
    int size = col_data->size();
    if (size <= 1000) base = 1;
    else base = (size - 1000 + 1);
    if (base <= 0) base = 1;
    for (int i = base; (i - base + 1)  <= 1000 && i <= size; ++i) {
        QTableWidgetItem * item1 = new QTableWidgetItem(QString::number(i));
        ui->tableWidget_col_data_details->setItem(i-base, 0, item1);

        QTableWidgetItem * item2 = new QTableWidgetItem(QString::number(col_data->at(i - 1)));
        ui->tableWidget_col_data_details->setItem(i-base, 1, item2);
    }
    ui->tableWidget_col_data_details->setColumnWidth(0, 50);
    ui->tableWidget_col_data_details->setColumnWidth(1, 50);
    //ui->tableWidget_col_data_details->resizeColumnsToContents();
    //ui->tableWidget_col_data_details->resizeRowsToContents();
    ui->tableWidget_col_data_details->setCurrentCell(999, 0);
    ui->tableWidget_col_data_details->repaint();
}

void Dialog::showSelColDataPre1000() {
    if (show_data_details_col_name.isNull()) {
        qDebug()<<"Please select a col first.";
        return;
    }

    QVector<double> *col_data = NULL;
    auto post_data_map = dpclass.getPostProcDataMap();
    if (post_data_map.find(show_data_details_col_name) != post_data_map.end()) {
        col_data = &post_data_map[show_data_details_col_name];
    } else {
        col_data->clear();
    }

    int current_index = ui->tableWidget_col_data_details->item(0, 0)->text().toInt();
    int base = 1;
    if (current_index <= 1000) base = 1;
    else base = (current_index - 1000);
    if (base <= 0) base = 1;
    for (int i = base; (i - base) < 1000 && i <= col_data->size(); ++i) {
        QTableWidgetItem * item1 = new QTableWidgetItem(QString::number(i));
        ui->tableWidget_col_data_details->setItem(i-base, 0, item1);

        QTableWidgetItem * item2 = new QTableWidgetItem(QString::number(col_data->at(i - 1)));
        ui->tableWidget_col_data_details->setItem(i-base, 1, item2);
    }
    ui->tableWidget_col_data_details->setColumnWidth(0, 50);
    ui->tableWidget_col_data_details->setColumnWidth(1, 50);
    //ui->tableWidget_col_data_details->resizeColumnsToContents();
    //ui->tableWidget_col_data_details->resizeRowsToContents();
    ui->tableWidget_col_data_details->repaint();
}

void Dialog::showSelColDataPost1000() {
    if (show_data_details_col_name.isNull()) {
        qDebug()<<"Please select a col first.";
        return;
    }

    QVector<double> *col_data = NULL;
    auto post_data_map = dpclass.getPostProcDataMap();
    if (post_data_map.find(show_data_details_col_name) != post_data_map.end()) {
        col_data = &post_data_map[show_data_details_col_name];
    } else {
        col_data->clear();
    }

    int current_index = ui->tableWidget_col_data_details->item(999, 0)->text().toInt();
    int base = 1;
    int size = col_data->size();
    if (current_index + 1000 < size) base = current_index + 1;
    else base = (size - 1000 + 1);
    if (base <=0) base = 1;
    for (int i = base; (i - base) < 1000 && i <= col_data->size(); ++i) {
        QTableWidgetItem * item1 = new QTableWidgetItem(QString::number(i));
        ui->tableWidget_col_data_details->setItem(i-base, 0, item1);

        QTableWidgetItem * item2 = new QTableWidgetItem(QString::number(col_data->at(i - 1)));
        ui->tableWidget_col_data_details->setItem(i-base, 1, item2);
    }
    ui->tableWidget_col_data_details->setColumnWidth(0, 50);
    ui->tableWidget_col_data_details->setColumnWidth(1, 50);
    //ui->tableWidget_col_data_details->resizeColumnsToContents();
    //ui->tableWidget_col_data_details->resizeRowsToContents();
    ui->tableWidget_col_data_details->repaint();
}

void Dialog::postAddXAxisData() {
    QList<QListWidgetItem *> xaxis_col = ui->post_proc_after_col_list->selectedItems();
    if (xaxis_col.size() <= 0) return;

    QSet<QString> exist_cols;
    for (int i = 0; i < ui->xaxis_data_list->count(); ++i) {
        exist_cols.insert(ui->xaxis_data_list->item(i)->text());
    }

    QStringList selected_col_items;
    for (auto it = xaxis_col.begin(); it != xaxis_col.end(); ++it) {
        QString col_name = (*it)->text();
        if (exist_cols.find(col_name) == exist_cols.end())// cannot add duplicate columns in post process.
            selected_col_items << col_name;
    }
    if (selected_col_items.size() <= 0 ) {
        //qDebug()<<"Please don't select duplicate column(s).";
        return;
    }
    ui->xaxis_data_list->addItems(selected_col_items);
    ui->xaxis_data_list->repaint();
}

void Dialog::postDelXAxisData() {
    QList<QListWidgetItem *> xaxis_col = ui->xaxis_data_list->selectedItems();
    if (xaxis_col.size() <= 0) return;

    for (auto it = xaxis_col.begin(); it != xaxis_col.end(); ++it) {
        int pre_row = ui->xaxis_data_list->row(*it);
        delete ui->xaxis_data_list->takeItem(pre_row);
    }
    ui->xaxis_data_list->repaint();
}

void Dialog::postAddYAxisData() {
    QList<QListWidgetItem *> yaxis_col = ui->post_proc_after_col_list->selectedItems();
    if (yaxis_col.size() <= 0) return;

    QSet<QString> exist_cols;
    for (int i = 0; i < ui->yaxis_data_list->count(); ++i) {
        exist_cols.insert(ui->yaxis_data_list->item(i)->text());
    }

    QStringList selected_col_items;
    for (auto it = yaxis_col.begin(); it != yaxis_col.end(); ++it) {
        QString col_name = (*it)->text();
        if (exist_cols.find(col_name) == exist_cols.end())// cannot add duplicate columns in post process.
            selected_col_items << col_name;
    }
    if (selected_col_items.size() <= 0 ) {
        //qDebug()<<"Please don't select duplicate column(s).";
        return;
    }
    ui->yaxis_data_list->addItems(selected_col_items);
    ui->yaxis_data_list->repaint();
}

void Dialog::postDelYAxisData() {
    QList<QListWidgetItem *> yaxis_col = ui->yaxis_data_list->selectedItems();
    if (yaxis_col.size() <= 0) return;

    for (auto it = yaxis_col.begin(); it != yaxis_col.end(); ++it) {
        int pre_row = ui->yaxis_data_list->row(*it);
        delete ui->yaxis_data_list->takeItem(pre_row);
    }
    ui->yaxis_data_list->repaint();
}

void Dialog::postPrepareDataForAnalysis(int index) {
    QList<QListWidgetItem *> sel_items = ui->post_proc_after_col_list->selectedItems();
    QVector<QString> sel_col_list;
    for (auto it = sel_items.begin(); it != sel_items.end(); ++it)
        sel_col_list.push_back((*it)->text());

    if (index == 0) { // correlation
        if (sel_col_list.size() != 2) {
            ui->label_dataanalysis_note->setText("Please Sel 2 Columns for Correlation.");
            ui->label_dataanalysis_note->setStyleSheet("color: rgb(231,66,67);");
            return;
        }
        ui->comboBox_correlation_x->setItemText(0, sel_col_list[0]);
        ui->comboBox_correlation_x->setItemText(1, sel_col_list[1]);
        ui->comboBox_correlation_y->setItemText(0, sel_col_list[1]);
        ui->comboBox_correlation_y->setItemText(1, sel_col_list[0]);
        ui->toolBoxPage_correlation->repaint();
    } else if (index == 1) {
        if (sel_col_list.size() != 2) {
            ui->label_dataanalysis_note->setText("Please Sel 2 Columns for Weightfit.");
            ui->label_dataanalysis_note->setStyleSheet("color: rgb(231,66,67);");
            return;
        }
        ui->comboBox_weightfit_x->setItemText(0, sel_col_list[0]);
        ui->comboBox_weightfit_x->setItemText(1, sel_col_list[1]);
        ui->comboBox_weightfit_y->setItemText(0, sel_col_list[1]);
        ui->comboBox_weightfit_y->setItemText(1, sel_col_list[0]);
        ui->toolBoxPage_weightedfit->repaint();
    }

    ui->label_dataanalysis_note->setText("Ok.");
    ui->label_dataanalysis_note->setStyleSheet("color: rgb(44,104,7);");
}

void Dialog::postStartDataAnalysis() {
    if (ui->groupBox_data_analysis->isChecked()) {

        QList<QListWidgetItem *> sel_items = ui->post_proc_after_col_list->selectedItems();
        int analysis_type = ui->toolBox_analysis_data->currentIndex();
        if (sel_items.size() <= 0 && analysis_type != 4) {
            ui->label_dataanalysis_note->setText("Please Sel Correlation Columns.");
            ui->label_dataanalysis_note->setStyleSheet("color: rgb(231,66,67);");
            return;
        }

        // prepare for data
        auto all_data_map = dpclass.getPostProcDataMap();
        QVector<double> in_data1, in_data2;
        QVector<double> out_data1, out_data2;
        double ret_val;
        QString msg = "Ok.";

        switch (analysis_type) {
        case 0: { // correlation
            if (sel_items.size() != 2) {
                msg = "Correlation Needs 2 Columns.";
                break;
            }
            in_data1 = all_data_map[ui->comboBox_correlation_x->currentText()]; // x
            in_data2 = all_data_map[ui->comboBox_correlation_y->currentText()]; // y
            //in_data1 = {1,2,3,4,5,6,7,8,10,11,12,13,14};
            //in_data2 = {0,2,4,6,8,10,12,14,16,18,20,22,24,26};
            if (in_data1.size() != in_data2.size()) {
                msg = "Size of Input Data X & Y Not Matched.";
                break;
            }
            ret_val = Utils::qtCorrelation(in_data1, in_data2, out_data1, out_data2); // a, b

            QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // sticks + lines
            graph->plotForCorrelation(in_data1, in_data2);
            graph->show();
            break;
        }
        case 1: { // weightedfit
            if (sel_items.size() != 2) {
                msg = "Weightedfit Needs 2 Columns.";
                break;
            }
            in_data1 = all_data_map[ui->comboBox_weightfit_x->currentText()]; // x
            in_data2 = all_data_map[ui->comboBox_weightfit_y->currentText()]; // y
            //in_data1 = {1,2,3,4,5,6,7,8,9,10,11,12,13};
            //in_data2 = {2.68009505, 4.440152786, 6.955791581,8.264737552, 10.32401073, 12.21620137, 14.56359881,
            //                            16.29702541, 18.01835966, 20.84322102, 22.86014104,24.31722384, 26.72096637};
            if (in_data1.size() != in_data2.size()) {
                msg = "Size of Input Data X & Y Not Matched.";
                break;
            }
            double a, b;
            Utils::weightedFit(in_data1, in_data2, a, b);
            QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // sticks + lines
            graph->plotForWeightedFit(in_data1, in_data2, a, b);
            graph->show();
            break;
        }
        case 2: { // spectral
            if (sel_items.size() != 1) {
                msg = "Spectral Needs 1 Column.";
                break;
            }
            in_data1 = all_data_map[ui->post_proc_after_col_list->currentItem()->text()];
            Utils::qtSpectral(in_data1, ui->lineEdit_spectral_freq->text().toDouble(), out_data1, out_data2); // out1: f, out2: YY
            if (out_data1.size() != out_data2.size()) {
                msg = "Size of Out Data f & YY Not Matched.";
                break;
            }
            QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // lines
            graph->plotForSpectral(out_data1, out_data2);
            graph->show();
            break;
        }
        case 3: { // cyclemax
            if (sel_items.size() != 1) {
                msg = "Cyclemax Needs 1 Column.";
                break;
            }
            in_data1 = all_data_map[ui->post_proc_after_col_list->currentItem()->text()];
            double result = Utils::qtCycleMax(in_data1, ui->lineEdit_cyclemax_estmax->text().toDouble(),
                                              ui->lineEdit_cyclemax_resol->text().toDouble(),
                                              ui->lineEdit_cyclemax_obstime->text().toDouble(),
                                              ui->lineEdit_cyclemax_regressioncycle->text().toDouble());
            ui->lineEdit_cyclemax_result->setText(QString::number(result));
            break;
        }
        case 4: { // enpost
            double spmx, spmy, spmz, aftx, afty, aftz;
            Utils::qtEnpost(ui->lineEdit_enpost_lat->text().toDouble(),
                            ui->lineEdit_enpost_lon->text().toDouble(),
                            ui->lineEdit_enpost_roll->text().toDouble(),
                            ui->lineEdit_enpost_pitch->text().toDouble(),
                            ui->lineEdit_enpost_heading->text().toDouble(),
                            ui->lineEdit_enpost_altitude->text().toDouble(),
                            spmx, spmy, spmz, aftx, afty, aftz);
            ui->lineEdit_enpost_spmx->setText(QString::number(spmx));
            ui->lineEdit_enpost_spmy->setText(QString::number(spmy));
            ui->lineEdit_enpost_spmz->setText(QString::number(spmz));
            ui->lineEdit_enpost_aftx->setText(QString::number(aftx));
            ui->lineEdit_enpost_afty->setText(QString::number(afty));
            ui->lineEdit_enpost_aftz->setText(QString::number(aftz));
            break;
        }
        case 5: { // max shang 1
            if (sel_items.size() != 1) {
                msg = "Max Shang1 Needs 1 Column.";
                break;
            }
            in_data1 = all_data_map[ui->post_proc_after_col_list->currentItem()->text()];
            Utils::qt1DMaxEntropy(in_data1, ui->lineEdit_maxshang1_limitmin->text().toDouble(),
                                  ui->lineEdit_maxshang1_a0resol->text().toDouble(),
                                  ui->lineEdit_maxshang1_estkesimin->text().toDouble(),
                                  ui->lineEdit_maxshang1_kesimax->text().toDouble(),
                                  ui->lineEdit_maxshang1_kesiresol->text().toDouble(),
                                  ui->lineEdit_maxshang1_whsample->text().toDouble(),
                                  ui->lineEdit_maxshang1_whmax->text().toDouble(),
                                  out_data1, out_data2); // output: yy1, yy2
            QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // lines
            graph->plotFor1DMaxEntropy(out_data1, out_data2);
            graph->show();
            break;
        }
        case 6: // max shang 2
            break;
        }
        ui->label_dataanalysis_note->setText(msg);
        if (msg != "Ok.")
            ui->label_dataanalysis_note->setStyleSheet("color: rgb(231,66,67);");
        else
            ui->label_dataanalysis_note->setStyleSheet("color: rgb(44,104,7);");
    }
}

void Dialog::postStartDrawGraph() {
    if (ui->groupBox_draw_graph->isChecked()) {
        QString msg = "Ok.";
        auto all_data_map = dpclass.getPostProcDataMap();
        int graph_type = ui->comboBox_curveType->currentIndex();
        switch (graph_type) {
        case 0: { // curve chart
            if (ui->xaxis_data_list->count() > 1) {
                msg = "x data shoule be non or 1 col.";
                break;
            }
            QVector<double> x_col;
            for (int i = 0; i < ui->xaxis_data_list->count(); ++i)
                x_col = all_data_map[ui->xaxis_data_list->item(i)->text()];

            if (ui->yaxis_data_list->count() < 1 || ui->yaxis_data_list->count() > 5) {
                msg = "y data cols should between 1 ~ 5.";
                break;
            }
            QVector<QVector<double> > y_cols;
            for (int i = 0; i < ui->yaxis_data_list->count(); ++i)
                y_cols.push_back(all_data_map[ui->yaxis_data_list->item(i)->text()]);

            int records = x_col.size();
            if (records == 0) records = y_cols[0].size();
            bool matched = true;
            for (auto it = y_cols.begin(); it != y_cols.end(); ++it) {
                if (it->size() != records) {
                    msg = "records of x & y not matched.";
                    matched = false;
                    break;
                }
            }

            if (matched) {
                QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // lines
                graph->plotForCurve(x_col, y_cols);
                graph->setXAxisLabel(ui->lineEdit_xlabel->text());
                graph->setYAxisLabel(ui->lineEdit_ylabel->text());
                graph->show();
            }
            break;
        }
        case 1: { // scatter graph
            if (ui->xaxis_data_list->count() != 1) {
                msg = "x data shoule be 1 col.";
                break;
            }
            QVector<double> x_col = all_data_map[ui->xaxis_data_list->item(0)->text()];

            if (ui->yaxis_data_list->count() != 1) {
                msg = "y data should be 1 col.";
                break;
            }
            QVector<double> y_col = all_data_map[ui->yaxis_data_list->item(0)->text()];

            if (x_col.size() != y_col.size()) {
                msg = "records of x & y not matched.";
                break;
            }

            QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // lines
            graph->plotForScatter(x_col, y_col);
            graph->setXAxisLabel(ui->lineEdit_xlabel->text());
            graph->setYAxisLabel(ui->lineEdit_ylabel->text());
            graph->show();
            break;
        }
        case 2: { // rose plot
            if (ui->xaxis_data_list->count() != 1) {
                msg = "x data shoule be 1 col.";
                break;
            }
            if (!(ui->xaxis_data_list->item(0)->text().contains("windspeed", Qt::CaseInsensitive))) {
                msg = "The x col should be 'WindSpeed'";
                break;
            }
            QVector<double> x_col = all_data_map[ui->xaxis_data_list->item(0)->text()];

            if (ui->yaxis_data_list->count() != 1) {
                msg = "y data shoule be 1 col.";
                break;
            }
            if (!(ui->yaxis_data_list->item(0)->text().contains("winddir", Qt::CaseInsensitive))) {
                msg = "The y col should be 'WindDir'";
                break;
            }
            QVector<double> y_col = all_data_map[ui->yaxis_data_list->item(0)->text()];

            if (x_col.size() != y_col.size()) {
                msg = "records of x & y not matched.";
                break;
            }
//            QVector<double> x_col = {6,7.2,6.5,7.1,5.6,3.5,4.4,4.3,3.4,3.8,4.8,3.6,2.8,2.2,2.9,4.2,4.7,6,
//                                     6.2,4.1,3.4,2.3,3.2,3.9,3.5,3.7,2.5,2.9,2.9,3.5,4.6,4,4.4,4.9,5.6,5.4,5.1,5.2,5.6,6.3}; // speed
//            QVector<double> y_col = {57,44,56,57,57,81,59,56,66,9,56,62,41,65,11,44,65,64,46,46,24,73,105,
//                                     65,83,52,67,4,73,62,23,56,46,61,50,64,53,74,66,51}; // dir
            QChartWindRosePlot *windrose = new QChartWindRosePlot(18, x_col, y_col);
            windrose->show();
            break;
        }
        case 3: { // histgraph
            if (ui->xaxis_data_list->count() > 1) {
                msg = "x data shoule be non or 1 col.";
                break;
            }
            QVector<double> x_col;
            for (int i = 0; i < ui->xaxis_data_list->count(); ++i)
                x_col = all_data_map[ui->xaxis_data_list->item(i)->text()];

            if (ui->yaxis_data_list->count() != 1) {
                msg = "y data shoule be 1 col.";
                break;
            }
            QVector<double> y_col = all_data_map[ui->yaxis_data_list->item(0)->text()];

            if ((x_col.size() != 0) && (x_col.size() != y_col.size())) {
                msg = "records of x & y not matched.";
                break;
            }

            QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // lines
            graph->plotForBarChart(x_col, y_col);
            graph->setXAxisLabel(ui->lineEdit_xlabel->text());
            graph->setYAxisLabel(ui->lineEdit_ylabel->text());
            graph->show();
            break;
        }
        default:
            break;
        }
        ui->label_drawgraph_note->setText(msg);
        if (msg != "Ok.")
            ui->label_drawgraph_note->setStyleSheet("color: rgb(231,66,67);");
        else
            ui->label_drawgraph_note->setStyleSheet("color: rgb(44,104,7);");
    }
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
