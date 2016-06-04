#include "dataprocess.h"
#include "queryDB.h"

DataProcess::DataProcess()
{
}


QStringList DataProcess::queryTableNameListbyDBName(QString db_name) {
    QueryDB qdb;
    QString sql = "show tables;";
    QSqlQuery query = qdb.queryDB(db_name, sql);
    qDebug() << "DataBase: "<< db_name << " table count = " << query.size();
    QStringList qsl;
    while(query.next()) {
        qsl << query.value(0).toString();
        qDebug()<< query.value(0).toString();
    }
    return qsl;
}

QStringList DataProcess::queryColumnNameListInTable(QString db_name, QString table_name) {
    QString sql = "show COLUMNS from " + table_name + "";
    QueryDB qdb;
    QSqlQuery query = qdb.queryDB(db_name, sql);
    qDebug() << "DataBase: "<< db_name << " table " << table_name <<" colume count = " << query.size();
    QStringList qsl;
    while(query.next()) {
        qsl << query.value(0).toString();
        qDebug()<< query.value(0).toString();
    }
    return qsl;
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
