#include "dataprocess.h"

DataProcess::DataProcess()
{

}

void DataProcess::setQuery(QStringList lists)
{

}

QVector<double> DataProcess::getData(QString list)
{

}

QStringList DataProcess::selectedData(QStringList lists)
{

}

QStringList DataProcess::tableData(QString database, QString table)
{
    qDebug() << "the database is" << database << " ";
    qDebug() << "the table is " << table << endl;
    QStringList ret;
    ret << "hello" << "world" << "test";
    return ret;
}

void DataProcess::exportToFile(QString data)
{

}

QStringList importFromFile(QFile *fileName)
{

}
