#ifndef FORMULADIALOG_H
#define FORMULADIALOG_H
#include <QDialog>
#include <QWidget>

namespace Ui {
class FormulaDialog;
}

class FormulaDialog : public QDialog
{
    Q_OBJECT
public:
    FormulaDialog(QWidget *parent = 0);
    ~FormulaDialog();
private:
    Ui::FormulaDialog *ui;
};

#endif // FORMULADIALOG_H
