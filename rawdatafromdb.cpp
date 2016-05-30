#include "rawdatafromdb.h"

//TODO: May be need some parameters in this constructor.
RawDataFromDB::RawDataFromDB()
{
    this->dbConnect();
    this->queryDataToModel();
    this->dbClose();
}

QSqlError RawDataFromDB::dbConnect() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("testdb");
    db.setUserName("root");
    db.setPassword("123456");
    if (!db.open()){
        qDebug()<<"Open Database Error!";
        return db.lastError();
    }
    return QSqlError();
}

QSqlError RawDataFromDB::queryDataToModel() {
    sql_model = new QSqlQueryModel();
    sql_model->setQuery("select * from testtable");
    //sql_model->setTable("testtable");
    return QSqlError();
}

QSqlError RawDataFromDB::dbClose() {
    db.close();
    db.removeDatabase("QMYSQL");
    return QSqlError();
}

