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

void DataProcess::preProcess(QStringList tb_col_name, QVector<AnalyseParas>, QVector<FilterCond>)
{

}

QVector<double> DataProcess::getFromRawDataMap(QString list)
{
    return raw_data_map[list];
}

QVector<double> DataProcess::getFromAfterProcessDataMap(QString list)
{
    return after_process_data_map[list];
}

void DataProcess::exportToFile(QString data)
{

}


