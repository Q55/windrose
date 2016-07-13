#include "queryDB.h"

QSqlError QueryDB::connectDB(QString db_name, QString db_address, QString db_username, QString db_passwd) {
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db_ = QSqlDatabase::database("qt_sql_default_connection");
    else
      db_ = QSqlDatabase::addDatabase("QMYSQL");
//    db_.setHostName("127.0.0.1");
//    db_.setDatabaseName(db_name);
//    db_.setUserName("root");
//    db_.setPassword("123456");
    db_.setHostName(db_address);
    db_.setDatabaseName(db_name);
    db_.setUserName(db_username);
    db_.setPassword(db_passwd);
    if (!db_.open()){
        qDebug()<<"Open Database "<< db_name <<" Error!";
        qDebug()<<db_.lastError();
        return db_.lastError();
    }
    return QSqlError();
}

QSqlQuery QueryDB::queryDB(QString db_name, QString db_address, QString db_username, QString db_passwd, QString query_sql) {
    connectDB(db_name, db_address, db_username, db_passwd);
    QSqlQuery query(db_);
    query.exec(query_sql);
    closeDB();
    return query;
}

QSqlError QueryDB::closeDB() {
    db_.close();
    db_.removeDatabase("QMYSQL");
    return QSqlError();
}

