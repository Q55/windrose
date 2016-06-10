#ifndef FORMULADIALOG_H
#define FORMULADIALOG_H
#include <QDialog>
#include <QWidget>
#include <QMessageBox>

namespace Ui {
class PostExprDialog;
}

class PostExprDialog : public QDialog
{
    Q_OBJECT
public:
    PostExprDialog(QWidget *parent = 0);
    PostExprDialog(QStringList col_list, QWidget *parent = 0);
    ~PostExprDialog();

signals:
    void postExprParas(bool, QString, int, double, bool, QString, int, QString);

public slots:
    void accept();

private:
    Ui::PostExprDialog *ui;
};

#endif // FORMULADIALOG_H
