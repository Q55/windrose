#ifndef QWTPOLARWINDROSEPLOT_H
#define QWTPOLARWINDROSEPLOT_H

#include <QMainWindow>
//#include <qwt_polar_plot.h>

class QwtPolarWindRosePlot : public QMainWindow
{
    Q_OBJECT
public:
    explicit QwtPolarWindRosePlot(QWidget *parent = 0);

    void plotForPolarRose(const QVector<double> &windspeed, const QVector<double> &winddir);

    void statsGraphSeries(const QVector<double> &windspeed, const QVector<double> &winddir);

    void setXAxisLabel(QString xlabel);
    void setYAxisLabel(QString ylabel);

signals:

public slots:

private:
//    QwtPolarPlot *polar_plot;
    QVector<QVector<double> > graph_serials;
};

#endif // QWTPOLARWINDROSEPLOT_H
