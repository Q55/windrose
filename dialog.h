#ifndef PREPROCESSWIDGET_H
#define PREPROCESSWIDGET_H

#include "dataprocess.h"
#include "analyseparas.h"
#include <QDialog>
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

/*
signals:
    void comboboxDatabase_changed(int);
*/
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

    void initTableList(int index, QStringList strings);

public slots:
    /*****************************
     * pre-process: data select
     *****************************/
    void setDataTable( int );
    void setDataList( QString );

    void addSelectedColList();
    void delSelectedColList();
    void addItemToSelListWidget(QListWidgetItem*);
    void updateSpinBoxSelCol();

    /****************************************
     * pre-process: analysis configuration
     ****************************************/
    void saveConfigtoMap();
    void showItemCurConfigInfo(QListWidgetItem*);

    void startPreProcess();

    void setProgressTips(int);
    void initProgress();

    //==========================================

    /*****************************************
     * post-process:
     *****************************************/
    void setPostProcessRaw();
    void inputFormulaDialog();

private:
    Ui::Dialog *ui;

    QStringList table111;
    QStringList table112;
    QStringList table118;

    DataProcess dpclass;
    QMap<QString, AnalyseParas> map_col_list_analyse_paras;

    QSet<QString> curSelectedListSet;

    QMap<int, QString> dbIndexNameMap;

//    QMap<QString, Pre_AnalyseType> analyse_type_map;
//    QMap<QString, Pre_FilterType> filter_type_map;
    void initComboboxMap();
};

#endif // PREPROCESSWIDGET_H
