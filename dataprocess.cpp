#include "dataprocess.h"
#include "queryDB.h"

DataProcess::DataProcess()
{
}


QStringList DataProcess::queryTableNameListbyDBName(QString db_name) {
    QueryDB qdb;
    QString sql = "show tables;";
    QSqlQuery query = qdb.queryDB(db_name, sql);
//    qDebug() << "DataBase: "<< db_name << " table count = " << query.size();
    QStringList qsl;
    while(query.next()) {
        qsl << query.value(0).toString();
//        qDebug()<< query.value(0).toString();
    }
    return qsl;
}

QStringList DataProcess::queryColumnNameListInTable(QString db_name, QString table_name) {
    QString sql = "show COLUMNS from " + table_name + "";
    QueryDB qdb;
    QSqlQuery query = qdb.queryDB(db_name, sql);
//    qDebug() << "DataBase: "<< db_name << " table " << table_name <<" colume count = " << query.size();
    QStringList qsl;
    while(query.next()) {
        qsl << query.value(0).toString();
//        qDebug()<< query.value(0).toString();
    }

//    QVector<double> result = {63.28465174,37.99977112,67.73463881,1000,7.027921752,79.17068791,44.60047712,10.03249046,
//                              89.21039851,15.84685586,65.87981232,96.16947997,50.62965453,80.57868233,99.54306176,
//                              70.26305706,54.08040631,99.69740406,90.91789511,96.07628517,80.21519287,72.28712213,
//                              53.08459423,67.56803368,14.84815871,75.00601463};
//    result = Utils::rangeCont(result, 28.1604, 0.1, "");
//    // test filter function
//    QFile file("/Users/lishiqiang/Documents/parttime/外协交流/mat_to_c/mat_to_c/filters/test_data.csv");
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        qDebug()<<"Open File ERROR!";
//    }
//    QTextStream stream(&file);
//    QStringList csvList;
//    while (!stream.atEnd()) {
//        csvList.push_back(stream.readLine());
//    }
//    file.close();
//    QVector<double> result;
//    qDebug()<<csvList.size();
//    for (int i = 0; i < csvList.size(); ++i)
//        result.push_back(csvList.at(i).toDouble());
//    QVector<double> l_data, w_data;
//    double m_data = Utils::qtFilters(result, 5, l_data, w_data);
//    qDebug()<<"m_data = "<<m_data<<" lsize = "<<l_data.size()<<" wSize = "<<w_data.size();
//    for (int i = 0; i < 10; ++i) {
//        qDebug()<<w_data.at(i);
//    }

    return qsl;
}

QVector<double> DataProcess::queryRawDataBySelTableColName(QString db_name, QString tb_name, QString col_name,
                                                                QDateTime start_time, QDateTime end_time) {

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

        QVector<double> col_raw_data =
                queryRawDataBySelTableColName(it.value().db_name, it.value().tb_name, it.value().col_name,
                                              it.value().start_time, it.value().end_time);
        QString str = it.key();
        raw_data_map[str] = col_raw_data;

        QVector<double> result;

        // range check
        result = col_raw_data;
        result = Utils::rangeCheck(result, it.value().max, it.value().min, it.value().process_type);

        // time cont

        // range cont
        result = Utils::rangeCont(result, 28, it.value().time_interval, it.value().process_type);

        // inter consis

        // max
        result = Utils::calcMax(result, it.value().frequency, it.value().time_interval);

        // min
        result = Utils::calcMin(result, it.value().frequency, it.value().time_interval);

        // average
        result = Utils::calcAvg(result, it.value().frequency, it.value().time_interval);

        // filter
        QVector<double> l_data, w_data;
        double m_data = Utils::qtFilters(result, it.value().frequency, l_data, w_data);

        after_process_data_map[str] = result;
        QString str1 = str + ".LData";
        after_process_data_map[str1] = l_data;
        str1 = str + ".WData";
        after_process_data_map[str1] = w_data;
        str1 = str + ".MData";
        QVector<double> v_mdata = {m_data};
        after_process_data_map[str1] = v_mdata;
    }
}


void DataProcess::exportToFile(QString data)
{

}


