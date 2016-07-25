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
    void loadConfig();
    void saveConfig();

signals:
    void configDataBase(QString, QString, QString, QVector<QString>);

public slots:
    void addDBName();
    void accept();
    void addRightMenuToRemoveDBName(const QPoint &);
    void removeSelDBName();

private:
    Ui::ConfigDataBase *ui;
    QStringList user,table;
};

#endif // CONFIGDATABASE_H
