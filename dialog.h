#ifndef PREPROCESSWIDGET_H
#define PREPROCESSWIDGET_H

#include "dataprocess.h"
#include "analyseparas.h"
#include <QDialog>
#include <QFileDialog>
#include <QSet>
#include <QListWidgetItem>
#include <QStringList>
#include <QString>

class QWidget;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    enum DataBase
    {
        FPSO111,
        FPSO112,
        FPSO118
    };
    enum CurveType
    {
        CURVE,
        SCATTER,
        HISTOGRAM,
        WINDROSE
    };

/*
signals:
    void comboboxDatabase_changed(int);
*/
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

    void initTableList(int index, QStringList strings);
    void setBackgroud();

public slots:
    void configDataBasePopDialog();
    void dealConfigDataBase(QString, QString, QString, QVector<QString>);

    /*****************************
     * pre-process: data select
     *****************************/
    void setDBTableList( int );
    void setTableColList( QString );
    void preAddSelectedColList();
    void preAddSelectedColList(QListWidgetItem*);
    void preDelSelectedColList();
    void updateSpinBoxSelCol();
    void updateSpinBoxSelCol(QListWidgetItem*);

    /****************************************
     * pre-process: analysis configuration
     ****************************************/
    void saveConfigToMap();
    void showItemCurConfigInfo(QListWidgetItem*);
    void startPreProcess();
    void exportDataToFile();
    void clearPreCache();
    void setProgressTips(int);
    void initProgress();

    //==========================================

    /*****************************************
     * post-process:
     *****************************************/
    void setPostProcessRawCol();
    void postAddSelectedColList();
    void postAddSelectedColList(QListWidgetItem*) { postAddSelectedColList(); }
    void postDelSelectedColList();
    void postPopExprDlg();
    void postPopRenameColDlg();
    void parsePostExpr(bool, QString, int, double, bool, QString, int, QString, QString);
    void addRightMenuToShowData(const QPoint &);
    void addRightMenuToRemoveCol(const QPoint &);
    void updateShowedDataDetails(int begin_row);
    void addSelColDataByRightMenu();
    //void refreshDataToDefault();
    void clearAllData();
    void dealRenameSelCol(QString orig_col_name, QString new_col_name);
    void removeColDataFromShowDataList();
    //void showSelColDataCount();
    //void showSelColDataByDoubleClicked();
    void showSelColDataFirst1000();
    void showSelColDataPre1000();
    void showSelColDataLast1000();
    void showSelColDataNext1000();
    void clearPostCache();

    // post data analysis
    void postStartDataAnalysis();
    void postPrepareDataForAnalysis(int);
    void postDataAnalysisRadioButtonDisableInput(bool);
    void postDataAnalysisRadioButtonEnableInput(bool);
    void post2DShangStatsInputEnable(int);

    // post draw graph
    void postAddXAxisData();
    void postDelXAxisData();
    void postAddYAxisData();
    void postDelYAxisData();
    void postStartDrawGraph();
    void drawRoseNote(int);


    // forecast
    void forecastStart();


private:
    Ui::Dialog *ui;

    QStringList table111;
    QStringList table112;
    QStringList table118;

    DataProcess dpclass;
    QMap<QString, AnalyseParas> map_col_list_analyse_paras;

    QMap<QString, int> pre_selcol_count_map;
    //QMap<QString, int> pre_sel_colrepeatlist_map;

    QMap<int, QString> dbIndexNameMap;


    /***********************************
     * interact with AnalyseParas class
     ***********************************/
    double check_type[2] = {1.0, 2.0};  //important FIXME, zyn comment.FIXME 06-07. to lsq.
    QMap<double, int> check_type_anti_map;
    double consist_check_type[3] = {1.0, 2.0, 0.5}; // important FIXME. zyn comment. FIXME 06-07. to lsq
    QMap<double, int> consist_check_anti_map;

//    QMap<QString, Pre_AnalyseType> analyse_type_map;
//    QMap<QString, Pre_FilterType> filter_type_map;
    void initComboboxMap();
    void initStartEndDateTime();

    bool clear_post_silentmode_;
    bool clear_pre_silentmode_;
    int last_ref_col_;
    QMap<QString, QVector<double> > showdata_col_list_;
    double kendall_val_;
    QVector<QVector<double> > stats_2D_output_;
};

#endif // PREPROCESSWIDGET_H
