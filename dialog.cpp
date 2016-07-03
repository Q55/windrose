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

#include <QFile>
#include <QTextStream>

void loadStyleSheet(const QString qssName)//加入下面函数
{

    QFile file(":/qss/"+qssName.toLower() + ".qss");

    QString styleSheet;

    if(file.open(QFile::ReadOnly))

    {
        styleSheet = QString::fromLatin1(file.readAll());
        //QTextStream styleIn(&data);

        //qssFile = styleIn.readAll();

        qApp->setStyleSheet(styleSheet);

        file.close();

    }
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    loadStyleSheet(QString("optStyle"));
    ui->setupUi(this);

    /////////////////////////////////////////////
    /// for cust lib test.
//    QVector<double> data1 = Utils::getQVectorFromFile("/Users/lishiqiang/Documents/parttime/外协交流/2Dmaximumentropy/test_data_stats_2d.csv",
//                                                     3, 1000000, 1);
//    QVector<double> data2 = Utils::getQVectorFromFile("/Users/lishiqiang/Documents/parttime/外协交流/2Dmaximumentropy/test_data_stats_2d.csv",
//                                                     3, 1000000, 2);
//    qDebug()<<data1.size();
//    qDebug()<<data2.size();
//    QVector<double> out1, out2;
//    QVector<QVector<double> > out;
//    Utils::qtStats2D(data1, data2, 0.12, 0.12, 0.1, 0.1, out);
//    qDebug()<<out.size();
//    for (int i = 0; i < out.size(); ++i) {
//        qDebug()<<i<<":"<<out.at(i).size()<<":"<<out.at(i);
//    }
//    QVector<double> data1 = Utils::getQVectorFromFile("/Users/lishiqiang/Documents/parttime/maxshang1.csv",
//                                                     3, 100000000, 15);
////    QVector<double> data2 = Utils::getQVectorFromFile("/Users/lishiqiang/Documents/parttime/spectral.csv",
////                                                     2, 100000000, 2);
////    qDebug()<<data1;
////    qDebug()<<data2;
//    QVector<double> out1, out2;
//    double a, b;
//    QVector<QVector<double> > out;
//    Utils::qt1DMaxEntropy(data1, 0.12, 0.001, 0.001, 20, 0.001, 0.1, 5, out1, out2);
////    qDebug()<<a<<","<<b;
//    qDebug()<<out1;
//    qDebug()<<out2;
//    for (int i = 0; i < out.size(); ++i) {
//        qDebug()<<i<<":"<<out.at(i).size()<<":"<<out.at(i);
//    }
//    QVector<double> data1 = Utils::getQVectorFromFile("/Users/lishiqiang/Documents/parttime/bar.tem.test.preprocdata.csv", 1, 100000000, 2);
//    double ret = Utils::qtCycleMax(data1, 0.1, 0.5, 100);
//    qDebug()<<ret;

//    QVector<QVector<double> > data;
//    data.resize(33);
//    for (int i = 0; i < 33; ++i)
//        data[i].resize(41);
//    for (int i = 0; i < 41; ++i) {
//        QVector<double> col = Utils::getQVectorFromFile("/Users/lishiqiang/Documents/parttime/外协交流/2Dmaximumentropy/test_data_distr_F2.pass.csv",
//                                                         1, 100000000, i + 1);
//        for (int j = 0; j < 33; ++j) {
//            data[j][i] = col.at(j);
//        }
//    }
//    qDebug()<<data;
//    QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // sticks + lines
//    graph->plotFor2DMaxEntropyDensity(data);
//    graph->show();
//    return;
//    QVector<double> in_data1, in_data2;
//    double a, b;
//    Utils::weightedFit(in_data1, in_data2, a, b);
//    qDebug()<<"a = "<<a<<", b = "<<b;
    ////////////////////////////////////////////

    initComboboxMap();
    pre_selcol_count_map.clear();
    kendall_val_ = 0.4954;
    stats_2D_output_.clear();
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
        emptyListErr->showMessage("请先选择列");
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
        errDialog->showMessage("请先执行'开始处理'");
        return;
    }

//    QDir dir;
//    QString cur_path = dir.currentPath();
    //QString dir_name = QFileDialog::getExistingDirectory(this, tr("Open Directory"), cur_path,
    //                                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
//    QString dir_name = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/Users/lishiqiang/Desktop",
//                                                          QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("保存数据"),
                                                     "",
                                                     tr("保存文件(*)"));
    dpclass.exportDataToFiles(file_name, true); // write raw_data
    dpclass.exportDataToFiles(file_name, false);// write pre_processed_data
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
        msgBox.setText("请先选择1列或2列数据");
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

    connect(expr_dlg, SIGNAL(postExprParas(bool, QString, int, double, bool, QString, int, QString, QString)), this,
            SLOT(parsePostExpr(bool, QString, int, double, bool, QString, int, QString, QString)));
}

void Dialog::parsePostExpr(bool scalar_checked, QString scalar_data, int scalar_op, double scalar_val, bool vec_checked,
                           QString vec_data1, int vec_op, QString vec_data2, QString new_col_name) {
    if (new_col_name == "") {
        QMessageBox msgBox;
        msgBox.setText("请输入新列名");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    QString new_col;
    if(scalar_checked) {
        new_col = dpclass.addColToPostProcDataByExpr(true, scalar_data, "", scalar_op, scalar_val, new_col_name);
    } else if (vec_checked) {
        new_col = dpclass.addColToPostProcDataByExpr(false, vec_data1, vec_data2, vec_op, 0.0, new_col_name);
    }
    if (new_col != "")
        ui->post_proc_after_col_list->addItem(new_col);
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
        qDebug()<<"请先选择列";
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
        qDebug()<<"请先选择列";
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
        qDebug()<<"请先选择列";
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
        qDebug()<<"请先选择列";
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
    if (xaxis_col.size() != 1) {
        QErrorMessage *xOnlyOneColErr = new QErrorMessage(this);
        xOnlyOneColErr->showMessage("X轴仅能选择1列数据");
        return;
    }

    QSet<QString> exist_cols;
    for (int i = 0; i < ui->xaxis_data_list->count(); ++i) {
        exist_cols.insert(ui->xaxis_data_list->item(i)->text());
    }

    if (exist_cols.size() >= 1) {
        QErrorMessage *xOnlyOneColErr = new QErrorMessage(this);
        xOnlyOneColErr->showMessage("X轴已有数据列，请先删除后再添加");
        return;
    }

    QStringList selected_col_items;
    for (auto it = xaxis_col.begin(); it != xaxis_col.end(); ++it) {
        QString col_name = (*it)->text();
        if (exist_cols.find(col_name) == exist_cols.end())// cannot add duplicate columns in post process.
            selected_col_items << col_name;
    }
    if (selected_col_items.size() <= 0 ) {
        //qDebug()<<"请不要选择重复的列";
        return;
    }
    ui->xaxis_data_list->addItems(selected_col_items);
    ui->xaxis_data_list->repaint();
}

void Dialog::postDelXAxisData() {
//    QList<QListWidgetItem *> xaxis_col = ui->xaxis_data_list->selectedItems();
//    if (xaxis_col.size() <= 0) return;

//    for (auto it = xaxis_col.begin(); it != xaxis_col.end(); ++it) {
//        int pre_row = ui->xaxis_data_list->row(*it);
//        delete ui->xaxis_data_list->takeItem(pre_row);
//    }
    ui->xaxis_data_list->clear();
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

    if (index == 4) { // correlation
        if (sel_col_list.size() != 2) {
            ui->label_dataanalysis_note->setText("请为相关性分析/肯德尔系数选择2列数据");
            ui->label_dataanalysis_note->setStyleSheet("color: rgb(231,66,67);");
            return;
        }
        for (int i = 0; i < 2; ++i) {
            ui->comboBox_correlation_x->setItemText(i, sel_col_list[i]);
            ui->comboBox_correlation_y->setItemText(i, sel_col_list[i]);
        }
        ui->comboBox_correlation_x->setCurrentIndex(0);
        ui->comboBox_correlation_y->setCurrentIndex(1);
        ui->toolBoxPage_correlation->repaint();
    } else if (index == 1) { // weighted fit
        if (sel_col_list.size() != 2) {
            ui->label_dataanalysis_note->setText("请为曲线拟合选择2列数据");
            ui->label_dataanalysis_note->setStyleSheet("color: rgb(231,66,67);");
            return;
        }
        for (int i = 0; i < 2; ++i) {
            ui->comboBox_weightfit_x->setItemText(i, sel_col_list[i]);
            ui->comboBox_weightfit_y->setItemText(i, sel_col_list[i]);
        }
        ui->comboBox_weightfit_x->setCurrentIndex(0);
        ui->comboBox_weightfit_y->setCurrentIndex(1);
        ui->toolBoxPage_weightedfit->repaint();
    } else if (index == 6) { // stats
        if (sel_col_list.size() != 2) {
            ui->label_dataanalysis_note->setText("请为统计分析选择2列数据");
            ui->label_dataanalysis_note->setStyleSheet("color: rgb(231,66,67);");
            return;
        }
        for (int i = 0; i < 2; ++i) {
            ui->comboBox_stats_data1->setItemText(i, sel_col_list[i]);
            ui->comboBox_stats_data2->setItemText(i, sel_col_list[i]);
        }
        ui->comboBox_stats_data1->setCurrentIndex(0);
        ui->comboBox_stats_data2->setCurrentIndex(1);
        ui->toolBoxPage_2dshangstats->repaint();
    } else if (index == 7) { // 2d max entropy
        if (sel_col_list.size() != 4) {
            ui->label_dataanalysis_note->setText("请为二维最大熵分析选择4列数据");
            ui->label_dataanalysis_note->setStyleSheet("color: rgb(231,66,67);");
            return;
        }
        for (int i = 0; i < 4; ++i) {
            ui->comboBox_2dshang_ff1->setItemText(i, sel_col_list[i]);
            ui->comboBox_2dshang_ff2->setItemText(i, sel_col_list[i]);
            ui->comboBox_2dshang_FF1->setItemText(i, sel_col_list[i]);
            ui->comboBox_2dshang_FF2->setItemText(i, sel_col_list[i]);
        }
        ui->comboBox_2dshang_ff1->setCurrentIndex(0);
        ui->comboBox_2dshang_ff2->setCurrentIndex(1);
        ui->comboBox_2dshang_FF1->setCurrentIndex(2);
        ui->comboBox_2dshang_FF2->setCurrentIndex(3);
        ui->lineEdit_2dshang_R->setText(QString::number(kendall_val_));
        ui->toolBoxPage_maxshang2->repaint();
    }

    ui->label_dataanalysis_note->setText("Ok.");
    ui->label_dataanalysis_note->setStyleSheet("color: rgb(44,104,7);");
}

void Dialog::postStartDataAnalysis() {
//    if (ui->groupBox_data_analysis->isChecked()) {
        QList<QListWidgetItem *> sel_items = ui->post_proc_after_col_list->selectedItems();
        int analysis_type = ui->toolBox_analysis_data->currentIndex();
//        if (sel_items.size() <= 0 && analysis_type != 4) {
//            ui->label_dataanalysis_note->setText("Please Sel Correlation Columns.");
//            ui->label_dataanalysis_note->setStyleSheet("color: rgb(231,66,67);");
//            return;
//        }

        // prepare for data
        auto all_data_map = dpclass.getPostProcDataMap();
        QVector<double> in_data1, in_data2;
        QVector<double> out_data1, out_data2;
        double ret_val;
        QString msg = "Ok.";

        switch (analysis_type) {
        case 0: { // enpost
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
        case 1: { // weighted fit
            if (sel_items.size() != 2) {
                msg = "曲线拟合需要2列数据";
                break;
            }
            in_data1 = all_data_map[ui->comboBox_weightfit_x->currentText()]; // x
            in_data2 = all_data_map[ui->comboBox_weightfit_y->currentText()]; // y
            //in_data1 = {1,2,3,4,5,6,7,8,9,10,11,12,13};
            //in_data2 = {2.68009505, 4.440152786, 6.955791581,8.264737552, 10.32401073, 12.21620137, 14.56359881,
            //                            16.29702541, 18.01835966, 20.84322102, 22.86014104,24.31722384, 26.72096637};
            if (in_data1.size() != in_data2.size()) {
                msg = "输入数据X与Y尺寸不匹配";
                break;
            }
            double a, b;
            Utils::weightedFit(in_data1, in_data2, a, b);
            QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // sticks + lines
            graph->plotForWeightedFit(in_data1, in_data2, a, b);
            graph->show();
            break;
        }
        case 2: { // cyclemax
            if (sel_items.size() != 1) {
                msg = "回归分析需要1列数据";
                break;
            }
            in_data1 = all_data_map[ui->post_proc_after_col_list->currentItem()->text()];
            //qDebug()<<in_data1;
            double result = Utils::qtCycleMax(in_data1,
                                              ui->lineEdit_cyclemax_resol->text().toDouble(),
                                              ui->lineEdit_cyclemax_obstime->text().toDouble(),
                                              ui->lineEdit_cyclemax_regressioncycle->text().toDouble());
            ui->lineEdit_cyclemax_result->setText(QString::number(result));
            msg = QString::number(result);
            break;
        }
        case 3: { // spectral
            if (sel_items.size() != 1) {
                msg = "谱分析需要1列数据";
                break;
            }
            in_data1 = all_data_map[ui->post_proc_after_col_list->currentItem()->text()];
            Utils::qtSpectral(in_data1, ui->lineEdit_spectral_freq->text().toDouble(), out_data1, out_data2); // out1: f, out2: YY
            if (out_data1.size() != out_data2.size()) {
                msg = "谱分析计算错误:f/YY元素不等";
                break;
            }
            QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // lines
            graph->plotForSpectral(out_data1, out_data2);
            graph->show();
            break;
        }
        case 4: { // correlation & kendall
            if (sel_items.size() != 2) {
                msg = "相关性分析/肯德尔系数需要2列数据";
                break;
            }
            in_data1 = all_data_map[ui->comboBox_correlation_x->currentText()]; // x
            in_data2 = all_data_map[ui->comboBox_correlation_y->currentText()]; // y
//            in_data1 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
//            in_data2 = {0,2,4,6,8,10,12,14,16,18,20,22,24,26};
            if (in_data1.size() != in_data2.size()) {
                msg = "X列和Y列数据尺寸不匹配";
                break;
            }

            int type = 0;
            if (ui->radioButton_correlation->isChecked()) // correlation
                type = 1;
            else if (ui->radioButton_kendall->isChecked()) // kendall
                type = 2;

            if (type == 1) {
                ret_val = Utils::qtCorrelation(in_data1, in_data2, out_data1, out_data2); // a, b
                QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // sticks + lines
                graph->plotForCorrelation(out_data2, out_data1);
                //graph->plotForCorrelation(out_data1, out_data2);
                graph->show();
            } else if (type == 2) {
                ret_val = Utils::qtKendall(in_data1, in_data2, ui->lineEdit_kendall_limit_min1->text().toDouble(),
                                           ui->lineEdit_kendall_limit_min2->text().toDouble());
                kendall_val_ = ret_val;
                msg = QString::number(ret_val);
            } else {
                msg = "请选择分析类型:相关性分析 or 肯德尔系数";
            }
            break;
        }
        case 5: { // max shang 1
            if (sel_items.size() != 1) {
                msg = "1维最大熵需要1列数据";
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
        case 6: { // stats for max shang 2
            if (sel_items.size() != 2) {
                msg = "统计分析需要2列数据";
                break;
            }
            in_data1 = all_data_map[ui->comboBox_stats_data1->currentText()]; // data1
            in_data2 = all_data_map[ui->comboBox_stats_data2->currentText()]; // data2
            int type = ui->comboBox_stats_type->currentIndex();
            switch (type) {
            case 0: { // stats 1D
                Utils::qtStats1D(in_data1, ui->lineEdit_stats_step1->text().toDouble(), out_data1, out_data2);
                if (out_data1.size() != out_data2.size()) {
                    msg = "结果序列X和Y元素个数不匹配";
                    break;
                }
                QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // lines
                graph->plotForXYData(out_data1, out_data2);
                graph->show();
                break;
            }
            case 1: { // stats 2D
                stats_2D_output_.clear();
                Utils::qtStats2D(in_data1, in_data2, ui->lineEdit_stats_limit_min1->text().toDouble(),
                                 ui->lineEdit_stats_limit_min2->text().toDouble(),
                                 ui->lineEdit_stats_step1->text().toDouble(),
                                 ui->lineEdit_stats_step2->text().toDouble(), stats_2D_output_);
                if (stats_2D_output_.size() <= 0) {
                    msg = "输出结果为空";
                    break;
                }

                QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // sticks + lines
                graph->plotFor2DMaxEntropyDensity(stats_2D_output_);
                graph->show();

                break;
            }
            case 2: { // Distr F1
                Utils::qtDistrF1(in_data1, in_data2, out_data1, out_data2);
                if (out_data1.size() != out_data2.size()) {
                    msg = "结果序列X和Y元素个数不匹配";
                    break;
                }
                QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // lines
                graph->plotForXYData(out_data1, out_data2);
                graph->show();
                break;
            }
            case 3: { // Distr F2
                if (stats_2D_output_.size() == 0) {
                    QErrorMessage *stats2d_first_msg = new QErrorMessage(this);
                    stats2d_first_msg->showMessage("请先执行Stats2D以准备数据");
                    break;
                }
                QVector<QVector<double> > out;
                Utils::qtDistrF2(stats_2D_output_, out);

                if (out.size() <= 0) {
                    msg = "输出结果为空";
                    break;
                }

                QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // sticks + lines
                graph->plotFor2DMaxEntropyDensity(out);
                graph->show();

                break;
            }
            default: break;
            }

            break;
        }
        case 7: { // max shang 2
            if (sel_items.size() != 4) {
                msg = "二维最大熵分析需要4列数据";
                break;
            }
            QVector<double> ff1 = all_data_map[ui->comboBox_2dshang_ff1->currentText()]; // ff1
            QVector<double> ff2 = all_data_map[ui->comboBox_2dshang_ff2->currentText()]; // ff2
            QVector<double> FF1 = all_data_map[ui->comboBox_2dshang_FF1->currentText()]; // FF1
            QVector<double> FF2 = all_data_map[ui->comboBox_2dshang_FF2->currentText()]; // FF2
            int type = ui->comboBox_2dshang_type->currentIndex();
            QVector<QVector<double> > out; // should be replaced by a more global variable--lsq, 2016.06.26
            Utils::qt2DMaxEntropy(ff1, FF1, ff2, FF2, ui->lineEdit_2dshang_R->text().toDouble(), type, out);

            if (out.size() <= 0) {
                msg = "输出结果为空";
                break;
            }

            QwtGraphPlotCustom *graph = new QwtGraphPlotCustom(); // sticks + lines
            graph->plotFor2DMaxEntropyDensity(out);
            graph->show();

            break;
        }
        }
        ui->label_dataanalysis_note->setText(msg);
        if (msg != "Ok.")
            ui->label_dataanalysis_note->setStyleSheet("color: rgb(231,66,67);");
        else
            ui->label_dataanalysis_note->setStyleSheet("color: rgb(44,104,7);");
//    }
}

void Dialog::postStartDrawGraph() {
//    if (ui->groupBox_draw_graph->isChecked()) {
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
//        case 4: //spectrogram
//        {
//            QwtGraphPlotCustom *graph = new QwtGraphPlotCustom();
//            QVector<QVector<double> > test_data;
//            test_data.resize(1000);
//            for (int i = 0; i < 1000; ++i)
//            {
//                test_data[i].resize(1000);
//                for (int j = 0; j < 1000; ++j)
//                    test_data[i][j] = 1.11+i+j*1.2;
//            }
//            graph->plotFor2DMaxEntropyDensity(test_data);
//        }
        default:
            break;
        }
        ui->label_drawgraph_note->setText(msg);
        if (msg != "Ok.")
            ui->label_drawgraph_note->setStyleSheet("color: rgb(231,66,67);");
        else
            ui->label_drawgraph_note->setStyleSheet("color: rgb(44,104,7);");
//    }
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
