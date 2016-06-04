#ifndef PREPROCESSWIDGET_H
#define PREPROCESSWIDGET_H

#include <QDialog>
class QWidget;
class QStringList;

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


public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

    void iniTableList(int index, QStringList strings);

private:
    Ui::Dialog *ui;

    QStringList table111;
    QStringList table112;
    QStringList table118;

};

#endif // PREPROCESSWIDGET_H
