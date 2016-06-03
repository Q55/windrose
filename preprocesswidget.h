#ifndef PREPROCESSWIDGET_H
#define PREPROCESSWIDGET_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class PreProcessWidget;
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

class PreProcessWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PreProcessWidget(QWidget *parent = 0);
    ~PreProcessWidget();

private:
    Ui::PreProcessWidget *ui;
};

#endif // PREPROCESSWIDGET_H
