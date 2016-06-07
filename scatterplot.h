#ifndef SCATTERPLOT_H
#define SCATTERPLOT_H
#include <qwt_plot.h>
#include <QMainWindow>

class Plot;

class ScatterPlot: public QMainWindow
{
    Q_OBJECT

public:
    ScatterPlot();

public:
    void setSamples( const QVector<double> &x, const QVector<double> &y );
    void setXAxisLabel(QString xlabel);
    void setYAxisLabel(QString ylabel);

private:
    Plot *scatter_plot;
};

#endif // SCATTERPLOT_H
