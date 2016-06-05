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

    enum Pre_AnalyseType
    {
        NONEANALYSE,
        MAXVALUE,
        MINVALUE,
        AVERAGEVALUE
    };

    enum Pre_FilterType
    {
        NONEFILTER,
        LOWERPASSFILTER
    };

/*
signals:
    void comboboxDatabase_changed(int);
*/
public slots:
    /*****************************
     * pre-process: data select
     *****************************/
    void setDataTable( int );
    void setDataList( QString );

    void addSelectedColList();
    void delSelectedColList();
    void updateSpinBoxSelCol();

    /****************************************
     * pre-process: analysis configuration
     ****************************************/
    void saveConfigtoMap();


    //==========================================

    /*****************************************
     * post-process:
     *****************************************/

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

    void initTableList(int index, QStringList strings);

private:
    Ui::Dialog *ui;

    QStringList table111;
    QStringList table112;
    QStringList table118;

    DataProcess dpclass;
    QMap<QString, AnalyseParas> map_col_list_analyse_paras;

    QSet<QString> curSelectedListSet;

    QMap<int, QString> dbIndexNameMap;
};

#endif // PREPROCESSWIDGET_H
