#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include <QtSql>
//FIXME: or
//#include "rawdatafromdb.cpp"
#include <QStringList>
#include <QVector>
#include <QList>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QMap>

//author: zyn
//time  : 2016-06-02
//class DataProcess:
//      process the data from mysql.
//      provide interface for graphic.

class DataProcess
{
public:
    DataProcess();
    void setQuery(QStringList lists);

    //function:
    //input : list name
    //output: list data
    QVector<double> getData(QString list);
    QStringList queryTableNameListbyDBName(QString db_name);
    QStringList queryColumnNameListInTable(QString db_name, QString table_name);

public slots:

    //FIXME: parameter not sure.
    QStringList selectedData(QStringList lists);
    QStringList tableData(QString index, QString table);

    //FIXME: input may be QStringList
    void exportToFile(QString data);
    QStringList importFromFile(QFile *fileName);

private :
    QSqlQuery query;

    //one-dimensinal map : key, attribute name. value, map<>
    //two-dimensinal map : key, data name. value, data attribute value.
    //FIXME: private or public?
    QMap<QString, QMap<QString, double> > attributeMap;

    //preResult is from file or from preprocess result.
    //FIXME: data type is int or double, fix me.
    QVector<QVector<double> > preResult;
    QList<QFile *> files;
};

#endif // DATAPROCESS_H
