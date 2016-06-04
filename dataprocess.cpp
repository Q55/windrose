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

QVector<double> DataProcess::queryRawDataBySelTableColName(QString db_name, QString tb_name, QString col_name,
                                                                QDate start_time, QDate end_time) {

    QString sql = "select " + col_name + " from " + tb_name + " where DateTime > " + start_time.toString() +
                " and DateTime < " + end_time.toString() + ";";
    QueryDB qdb;
    QSqlQuery query = qdb.queryDB(db_name, sql);
    QVector<double> result;
    while(query.next()) {
        result.push_back(query.value(0).toDouble());
    }
    return result;
}

QVector<double> DataProcess::getFromRawDataMap(QString list)
{
    return raw_data_map[list];
}

QVector<double> DataProcess::getFromAfterProcessDataMap(QString list)
{
    return after_process_data_map[list];
}

void DataProcess::preProccess(QMap<QString, AnalyseParas> analyse_paras) {

    for (QMap<QString, AnalyseParas>::Iterator it = analyse_paras.begin(); it != analyse_paras.end(); it++) {

//        QVector<double> col_raw_data = queryRawDataBySelTableColName(it->db_name, it->tb_name, it->col_name,
//                                                                 it->start_time, it->end_time);
//        QString str = it->tb_name + "." + it->col_name;
//        raw_data_map[str] = col_raw_data;

//        QVector<double> result;

//        // range filter

//        // time cont

//        // data cont

//        // consist check

//        // process type

//        // max

//        // minimal

//        // average

//        after_process_data_map[str] = result;
    }

}


void DataProcess::exportToFile(QString data)
{

}


