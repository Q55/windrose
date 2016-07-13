#ifndef QUERYDB_H
#define QUERYDB_H

#include <QtSql>

/* In this class, we get raw data from database directly.
   It also provide APIs to access (part of) data
*/
class QueryDB
{
public:
    QueryDB() {}
    ~QueryDB() {}

    QSqlQuery queryDB(QString db_name, QString db_address, QString db_username, QString db_passwd, QString query_sql);

public:
    QSqlError connectDB(QString db_name, QString db_address, QString db_username, QString db_passwd);
    QSqlError closeDB();

private:
    QSqlDatabase db_;
};

#endif // RAWDATAFROMDB_H
