#ifndef PREPROCESSWIDGET_H
#define PREPROCESSWIDGET_H

#include <QWidget>

namespace Ui {
class PreProcessWidget;
}

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
