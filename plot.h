#ifndef PLOT_H
#define PLOT_H
#include <qwt_plot.h>
#include <QVector>
#include <QString>
#include <qwt_plot_curve.h>
#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>

class QwtSymbol;

class Plot : public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget *parent = NULL );

    void setSymbol( QwtSymbol * );
    void setSamples( const QVector<QPointF> &samples );
    void setXAxisTitle(QString xlabel);
    void setYAxisTitle(QString ylabel);
    void appendCurve(QwtPlotCurve *);
    void setCurveStyle(QwtPlotCurve::CurveStyle);

//public Q_SLOTS:
//    void showContour ( bool on );
//    void showSpectrogram ( bool on );

private:
    QwtPlotCurve *d_curve;
};

#endif // PLOT_H
