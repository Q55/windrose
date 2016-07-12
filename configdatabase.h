#ifndef CONFIGDATABASE_H
#define CONFIGDATABASE_H

#include <QDialog>

namespace Ui {
class ConfigDataBase;
}

class ConfigDataBase : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDataBase(QWidget *parent = 0);
    ConfigDataBase(QString db_address, QString db_username, QString db_password, QVector<QString> db_list, QWidget *parent = 0);
    ~ConfigDataBase();

signals:
    void configDataBase(QString, QString, QString, QVector<QString>);

public slots:
    void accept();

private:
    Ui::ConfigDataBase *ui;
};

#endif // CONFIGDATABASE_H
