#ifndef PREPROCESSWIDGET_H
#define PREPROCESSWIDGET_H

#include "dataprocess.h"
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
public slots:
    void setDataTable( int );
    void setDataList( QString );
    void setSelectedDataList();

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

    QSet<QListWidgetItem *> curSelectedListSet;

    QMap<int, QString> dbIndexNameMap;
};

#endif // PREPROCESSWIDGET_H
