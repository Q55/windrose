#ifndef POSTCOLRENAMEDIALOG_H
#define POSTCOLRENAMEDIALOG_H

#include <QDialog>

namespace Ui {
class PostColRenameDialog;
}

class PostColRenameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PostColRenameDialog(QWidget *parent = 0);
    PostColRenameDialog(QString orig_col_name, QWidget *parent = 0);
    ~PostColRenameDialog();

signals:
    void postRenameNewColName(QString, QString);

public slots:
    void accept();

private:
    Ui::PostColRenameDialog *ui;
};

#endif // POSTCOLRENAMEDIALOG_H
