#ifndef SCATTERPLOT_H
#define SCATTERPLOT_H
#include <qwt_plot.h>
#include <QMainWindow>
#include <qwt_plot_spectrogram.h>

class Plot;
class PlotSpectrogram;

class QwtGraphPlotCustom: public QMainWindow {
    Q_OBJECT

public:
    QwtGraphPlotCustom();

    void plotForCorrelation(const QVector<double> &x, const QVector<double> &y);
    void plotForWeightedFit(const QVector<double> &x, const QVector<double> &y, double a, double b);
    void plotForSpectral(const QVector<double> &f, const QVector<double> &YY);
    void plotFor1DMaxEntropy(const QVector<double> &yy1, const QVector<double> &yy2);
    void plotForXYData(const QVector<double> &x, const QVector<double> &y);
    void plotFor2DMaxEntropyDensity(const QVector<QVector<double> > &array_2d);

    void plotForCurve(const QVector<double> &x, const QVector<QVector<double> > &yy, const QVector<QString> &yy_names);
    void plotForScatter(const QVector<double> &x, const QVector<QVector<double> > &yy, const QVector<QString> &yy_names);
    void plotForBarChart(const QVector<double> &x, const QVector<double> &y);
    //void plotForPolarRose(const QVector<double> &windspeed, const QVector<double> &winddir);

public:
    //void setSamples( const QVector<double> &x, const QVector<double> &y );
    void setXAxisLabel(QString xlabel);
    void setYAxisLabel(QString ylabel);

public:
    Plot *graph_plot;
    PlotSpectrogram *spectrogram_plot;

};

#endif // SCATTERPLOT_H
