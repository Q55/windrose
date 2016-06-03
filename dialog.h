#ifndef PREPROCESSWIDGET_H
#define PREPROCESSWIDGET_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
public:
    explicit Dialog(QDialog *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // PREPROCESSWIDGET_H
