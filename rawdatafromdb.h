#ifndef RAWDATAFROMDB_H
#define RAWDATAFROMDB_H

#include <QtSql>

/* In this class, we get raw data from database directly.
   It also provide APIs to access (part of) data
*/
class RawDataFromDB
{
public:
    RawDataFromDB();
    QSqlQueryModel *GetDataModel() { return sql_model; }

private:
    QSqlError dbConnect();
    QSqlError queryDataToModel();
    QSqlError dbClose();

private:
    QSqlDatabase db;
    QSqlQueryModel *sql_model; // a mode which contains all data query from db, use QSqlQueryModel to re-use its useful methods.
    //TODO: a model represents a table in database? need to be confirmed.
};

#endif // RAWDATAFROMDB_H
