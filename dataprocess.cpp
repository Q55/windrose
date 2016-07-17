#include "dataprocess.h"
#include "queryDB.h"

#include <QErrorMessage>

DataProcess::DataProcess(QObject *parent) :
    QObject(parent)
{
    db_address_ = "127.0.0.1";
    db_username_ = "root";
    db_password_ = "123456";
    db_name_list_ = {"112", "118"};
}


QStringList DataProcess::queryTableNameListbyDBName(QString db_name) {
    QueryDB qdb;
    QString sql = "show tables;";
    QSqlQuery query = qdb.queryDB(db_name, db_address_, db_username_, db_password_, sql);
//    qDebug() << "DataBase: "<< db_name << " table count = " << query.size();
    QStringList qsl;
    while(query.next()) {
        qsl << query.value(0).toString();
    }
    return qsl;
}

QStringList DataProcess::queryColumnNameListInTable(QString db_name, QString table_name) {
    QString sql = "show COLUMNS from " + table_name + "";
    QueryDB qdb;
    QSqlQuery query = qdb.queryDB(db_name, db_address_, db_username_, db_password_, sql);
//    qDebug() << "DataBase: "<< db_name << " table " << table_name <<" colume count = " << query.size();
    QStringList qsl;
    while(query.next()) {
        qsl << query.value(0).toString();
//        qDebug()<< query.value(0).toString();
    }

    return qsl;
}

QVector<double> DataProcess::queryRawDataBySelTableColName(QString db_name, QString tb_name, QString col_name,
                                                                QDateTime start_time, QDateTime end_time) {

    QString sql = "select " + col_name + " from " + tb_name + " where DateTime between '" + start_time.toString("yyyy-MM-dd HH:mm:ss") +
                "' and '" + end_time.toString("yyyy-MM-dd HH:mm:ss") + "';";
    qDebug()<<sql;
    QueryDB qdb;
    QSqlQuery query = qdb.queryDB(db_name, db_address_, db_username_, db_password_, sql);
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

QVector<double> DataProcess::getFromAfterProcessDataMap(QString list){
    return after_preproc_data_map[list];
}

void DataProcess::preProccess(QMap<QString, AnalyseParas> analyse_paras) {

    if (analyse_paras.empty()) {
        QErrorMessage * errDialog = new QErrorMessage();
        errDialog->showMessage("没有选择任何数据列");
        return;
    }

    raw_data_map.clear();
    after_preproc_data_map.clear();
    freq_list.clear();
    int i = 0;
    int ratio = 0;
    emit this->preProcessRate(ratio);
    for (QMap<QString, AnalyseParas>::Iterator it = analyse_paras.begin(); it != analyse_paras.end(); it++) {

        QVector<double> col_raw_data =
                queryRawDataBySelTableColName(it.value().db_name, it.value().tb_name, it.value().col_name,
                                              it.value().start_time, it.value().end_time);
        QString str = it.key();
        raw_data_map[str] = col_raw_data;
        QVector<double> result = col_raw_data;
        freq_list.push_back(it.value().frequency);
        // range check
        if (it.value().range_filter)
            result = Utils::rangeCheck(result, it.value().max, it.value().min, it.value().range_filter_check_type);
        // time cont
        if (it.value().time_cont)
            result = Utils::timeCont(result, it.value().frequency, 1, it.value().time_cont_time_step, it.value().time_cont_check_type);
        // range cont
        if (it.value().data_cont)
            result = Utils::rangeCont(result, it.value().data_cont_gsd, it.value().data_cont_time_step, it.value().data_cont_check_type);
        // inter consis
        if (it.value().consist_check)
            result = Utils::interConsis(result, it.value().var_name, it.value().expression, it.value().consist_check_type);
        // max
        if (it.value().analyse_type == it.value().MAXVALUE)
            result = Utils::calcMax(result, it.value().frequency, it.value().time_interval);
        // min
        if (it.value().analyse_type == it.value().MINVALUE)
            result = Utils::calcMin(result, it.value().frequency, it.value().time_interval);
        // average
        if (it.value().analyse_type == it.value().AVERAGEVALUE) {
            if (str.contains("winddir", Qt::CaseInsensitive))
                result = Utils::calcDirAvg(result, it.value().frequency, it.value().time_interval);
            else
                result = Utils::calcAvg(result, it.value().frequency, it.value().time_interval);
        }
        // filter
        if (it.value().filter_type == it.value().LOWERPASSFILTER) {
            QVector<double> l_data, w_data;
            Utils::qtFilters(result, it.value().frequency, l_data, w_data);
            QString strtemp = str + ".LData";
            after_preproc_data_map[strtemp] = l_data;
            strtemp = str + ".WData";
            after_preproc_data_map[strtemp] = w_data;
        } else {
            after_preproc_data_map[str] = result;
        }

        i++;
        ratio = ((double)i / (double)analyse_paras.size()) * 100;
        qDebug()<<"ratio = "<<ratio;
        emit this->preProcessRate(ratio);
    }

    emit preProcessEnd();
}

void DataProcess::exportDataToFiles(QString path, bool is_rawdata)
{
    QString data_file_name;
    QMap<QString, QVector<double> > *write_data_map;
    if (is_rawdata) {
        data_file_name = path + ".rawdata.csv";
        write_data_map = &raw_data_map;
    } else {
        data_file_name = path + ".preprocdata.csv";
        write_data_map = &after_preproc_data_map;
    }
    QFile data_file(data_file_name);
    data_file.open(QFile::WriteOnly);
    QTextStream text(&data_file);
    // Write Header First
    for (QMap<QString, QVector<double> >::Iterator it = write_data_map->begin(); it != write_data_map->end(); ++it) {
        text<<"Time,"<<it.key()<<",";
    }
    text<<endl;

    // Write Data
    int line_count = 1;
    bool write_finished = false;
    while (!write_finished) {
        int col = 0;
        write_finished  = true;
        for (QMap<QString, QVector<double> >::Iterator it = write_data_map->begin(); it != write_data_map->end(); ++it, col++) {
            QVector<double> &data = it.value();
            if (line_count > data.size()) {
                text<<","<<",";
            } else {
                text<<(double)(1.0/(double)freq_list[col]*(double)line_count)<<","<<data[line_count-1]<<",";
                write_finished = false;
            }
        }
        text<<endl;
        line_count++;
    }
    data_file.close();
}

QStringList DataProcess::getNamePostProcessData() {
    QStringList view_post_col_name;
    for(auto it = after_preproc_data_map.begin(); it != after_preproc_data_map.end(); ++it) {
        view_post_col_name << it.key();
    }
    return view_post_col_name;
}

void DataProcess::addColsToPostProcDataDirectly(QStringList col_name_list) {
    if (col_name_list.size() <= 0) return;

    for (auto it = col_name_list.begin(); it != col_name_list.end(); ++it) {
        if (after_preproc_data_map.find(*it) != after_preproc_data_map.end()) {
            postproc_data_map.insert(*it, after_preproc_data_map[*it]);
        }
    }
    //qDebug()<<"Size of postproc_data_map after add is "<<postproc_data_map.size();
}

QString DataProcess::addColToPostProcDataByExpr(bool is_scalar, QString data1, QString data2, int op, double operand, QString new_col) {
    QString new_col_name = new_col;
    QVector<double> result;
    qDebug()<<operand;
    if (is_scalar) {
        if (after_preproc_data_map.find(data1) != after_preproc_data_map.end()) {
            QVector<double> &orig_data = after_preproc_data_map[data1];
            switch (op) {
            case 0:
                //new_col_name = data1 + "+" + QString::number(operand);
                for (auto it = orig_data.begin(); it != orig_data.end(); ++it)
                    result.push_back(*it + operand);
                break;
            case 1:
                //new_col_name = data1 + "-" + QString::number(operand);
                for (auto it = orig_data.begin(); it != orig_data.end(); ++it)
                    result.push_back(*it - operand);
                break;
            case 2:
                //new_col_name = data1 + "*" + QString::number(operand);
                for (auto it = orig_data.begin(); it != orig_data.end(); ++it)
                    result.push_back(*it * operand);
                break;
            case 3:
                //new_col_name = data1 + "/" + QString::number(operand);
                for (auto it = orig_data.begin(); it != orig_data.end(); ++it)
                    result.push_back(*it / operand);
                break;
            case 4:
                //new_col_name = data1 + "^2";
                for (auto it = orig_data.begin(); it != orig_data.end(); ++it)
                    result.push_back((*it) * (*it));
                break;
            case 5:
                //new_col_name = data1 + ".extract";
                for (auto it = orig_data.begin(); it != orig_data.end(); ++it)
                    result.push_back(sqrt(*it));
                break;
            case 6:
                //new_col_name = data1 + ".log";
                for (auto it = orig_data.begin(); it != orig_data.end(); ++it)
                    result.push_back(log(*it));
                break;
            }
        }
    } else {
        if (after_preproc_data_map.find(data1) != after_preproc_data_map.end() &&
                after_preproc_data_map.find(data2) != after_preproc_data_map.end()) {
            QVector<double> &orig_data1 = after_preproc_data_map[data1];
            QVector<double> &orig_data2 = after_preproc_data_map[data2];
            auto it1 = orig_data1.begin();
            auto it2 = orig_data2.begin();
            switch (op) {
            case 0:
                //new_col_name = data1 + "+" + data2;
                for (; it1 != orig_data1.end() && it2 != orig_data2.end(); ++it1, ++it2)
                    result.push_back(*it1 + *it2);
                break;
            case 1:
                //new_col_name = data1 + "-" + data2;
                for (; it1 != orig_data1.end() && it2 != orig_data2.end(); ++it1, ++it2)
                    result.push_back(*it1 - *it2);
                break;
            case 2:
                //new_col_name = data1 + "*" + data2;
                for (; it1 != orig_data1.end() && it2 != orig_data2.end(); ++it1, ++it2)
                    result.push_back(*it1 * *it2);
                break;
            case 3:
                //new_col_name = data1 + "/" + data2;
                for (; it1 != orig_data1.end() && it2 != orig_data2.end(); ++it1, ++it2) {
                    double val2 = *it2;
                    if (val2 == 0.0) val2 = 1;
                    result.push_back(*it1 / val2);
                }
                break;
            }
        }
    }

    int i = 1;
    QString temp_name = new_col_name;
    while (postproc_data_map.find(temp_name) != postproc_data_map.end()) {
        temp_name = new_col_name + QString::number(i++);
    }
    new_col_name = temp_name;

    if (new_col_name != "") {
        postproc_data_map.insert(new_col_name, result);
    }
    return new_col_name;
}

void DataProcess::delColsFromPostProcDataByName(QStringList col_name_list) {
    if (col_name_list.size() <= 0) return;

    for (auto it = col_name_list.begin(); it != col_name_list.end(); ++it) {
        if (postproc_data_map.find(*it) != postproc_data_map.end())
            postproc_data_map.remove(*it);
    }
    //qDebug()<<"Size of postproc_data_map after del is "<<postproc_data_map.size();
}
