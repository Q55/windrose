#include "dataprocess.h"
#include "queryDB.h"

#include <QErrorMessage>

DataProcess::DataProcess(QObject *parent) :
    QObject(parent)
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
//    QVector<double> result = {1,5,6,10,11,12,13,18,19,20};
//    Utils::timeCont(result, 1000, 1, 1, 1);
//    QVector<double> result = {1, 2, 3, 4, 5,6,7,8,9,10};
//    Utils::interConsis(result, 1);

    return qsl;
}

QVector<double> DataProcess::queryRawDataBySelTableColName(QString db_name, QString tb_name, QString col_name,
                                                                QDateTime start_time, QDateTime end_time) {

    QString sql = "select " + col_name + " from " + tb_name + " where DateTime between '" + start_time.toString("yyyy-MM-dd HH:mm:ss") +
                "' and '" + end_time.toString("yyyy-MM-dd HH:mm:ss") + "';";
    qDebug()<<sql;
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

    if (analyse_paras.empty()) {
        QErrorMessage * errDialog = new QErrorMessage();
        errDialog->showMessage("No column data is selected.");
        return;
    }

    int i = 0;
    int ratio = 0;
    for (QMap<QString, AnalyseParas>::Iterator it = analyse_paras.begin(); it != analyse_paras.end(); it++) {

        QVector<double> col_raw_data =
                queryRawDataBySelTableColName(it.value().db_name, it.value().tb_name, it.value().col_name,
                                              it.value().start_time, it.value().end_time);
        QString str = it.key();
        raw_data_map[str] = col_raw_data;
        QVector<double> result = col_raw_data;
        // range check
        if (it.value().range_filter)
            //FIXME 06-07
//            result = Utils::rangeCheck(result, it.value().max, it.value().min, it.value().process_type);
        // time cont
        //if (it.value().time_cont)
        //    result = Utils::timeCont(result, it.value().frequency, 1, 1, it.value().process_type);
        // range cont
        if (it.value().data_cont)
            //FIXME 06-07
//            result = Utils::rangeCont(result, 28, 0.1, it.value().process_type);
        // inter consis
        if (it.value().consist_check)
            //FIXME 06-07
//            result = Utils::interConsis(result, it.value().process_type);
        // max
        if (it.value().analyse_type == it.value().MAXVALUE)
            result = Utils::calcMax(result, it.value().frequency, it.value().time_interval);
        // min
        if (it.value().analyse_type == it.value().MINVALUE)
            result = Utils::calcMin(result, it.value().frequency, it.value().time_interval);
        // average
        if (it.value().analyse_type == it.value().AVERAGEVALUE)
            result = Utils::calcAvg(result, it.value().frequency, it.value().time_interval);
        // filter
        if (it.value().filter_type == it.value().LOWERPASSFILTER) {
            QVector<double> l_data, w_data;
            Utils::qtFilters(result, it.value().frequency, l_data, w_data);
            result = l_data;
        }
        after_process_data_map[str] = result;

        i++;
        ratio = ((double)i / (double)analyse_paras.size()) * 100;
        qDebug()<<"ratio = "<<ratio;
        emit this->preProcessRate(ratio);
    }

    emit preProcessEnd();
}


void DataProcess::exportToFile()
{

}

QStringList DataProcess::getNamePostProcessData()
{
    QStringList view_post_col_name;
    for(auto it = after_process_data_map.begin(); it != after_process_data_map.end(); ++it)
    {
        view_post_col_name << it.key();
    }
    return view_post_col_name;
}


