#ifndef POSTPROCESSWIDGET_H
#define POSTPROCESSWIDGET_H

//#include <QWidget>
#include <QMainWindow>

namespace Ui {
class PostProcessWidget;
}

class PostProcessWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit PostProcessWidget(QMainWindow *parent = 0);
    ~PostProcessWidget();

private:
    Ui::PostProcessWidget *ui;
};

#endif // POSTPROCESSWIDGET_H
