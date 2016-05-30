#ifndef POSTPROCESSWIDGET_H
#define POSTPROCESSWIDGET_H

#include <QWidget>

namespace Ui {
class PostProcessWidget;
}

class PostProcessWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PostProcessWidget(QWidget *parent = 0);
    ~PostProcessWidget();

private:
    Ui::PostProcessWidget *ui;
};

#endif // POSTPROCESSWIDGET_H
