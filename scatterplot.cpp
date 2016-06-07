#include "scatterplot.h"
#include "plot.h"

#include <qwt_interval_symbol.h>
#include <qwt_symbol.h>
#include <QDebug>
#include <qwt_plot_curve.h>

ScatterPlot::ScatterPlot()
{
    scatter_plot = new Plot(this);
    scatter_plot->setTitle( "散点图" );
    setCentralWidget( scatter_plot );
    QwtSymbol *scatter_symbols = new QwtSymbol( QwtSymbol::Ellipse);
    scatter_symbols->setSize(3);
    scatter_symbols->setPen( Qt::blue );
    scatter_plot->setCurveStyle(QwtPlotCurve::Sticks);
    scatter_plot->setSymbol(scatter_symbols);
}

void ScatterPlot::setSamples(const QVector<double> &x, const QVector<double> &y)
{
    qDebug() << "enter setSamples";
    if (x.size() != y.size())
    {
        qDebug() << "Input Data Size Error!";
        return;
    }
    QPolygonF samples;
    for (int i = 0; i < x.size(); ++i)
    {
        samples += QPointF(x[i], y[i]);
    }
    scatter_plot->setSamples( samples );
    scatter_plot->replot();
}

void ScatterPlot::setXAxisLabel(QString xlabel)
{
    scatter_plot->setXAxisTitle(xlabel);
}

void ScatterPlot::setYAxisLabel(QString ylabel)
{
    scatter_plot->setYAxisTitle(ylabel);
}
