#include "qwtgraphplotcustom.h"
#include "plot.h"

#include <qwt_interval_symbol.h>
#include <qwt_symbol.h>
#include <QDebug>
#include <qwt_plot_curve.h>
#include <qwt_plot_histogram.h>

QwtGraphPlotCustom::QwtGraphPlotCustom() {

    graph_plot = new Plot(this);
    graph_plot->setTitle( "数据分析图" );
    setCentralWidget( graph_plot );

    graph_plot->setFixedSize(QSize(800, 600));
}

void QwtGraphPlotCustom::plotForCorrelation(const QVector<double> &x, const QVector<double> &y) {

    QPolygonF samples;
    for (int i = 0; i < x.size(); ++i)
        samples += QPointF(x[i], y[i]);

    QwtPlotCurve *curve1 = new QwtPlotCurve("curve1");
    curve1->setSamples(samples);
    curve1->setStyle(QwtPlotCurve::Sticks);
    curve1->attach(graph_plot);

    QwtPlotCurve *curve2 = new QwtPlotCurve("curve2");
    curve2->setSamples(samples);
    curve2->setStyle(QwtPlotCurve::Lines);
    curve2->attach(graph_plot);


    //scatter_plot->resize(800, 600);

    //scatter_plot->replot();
}

void QwtGraphPlotCustom::plotForWeightedFit(const QVector<double> &x, const QVector<double> &y, double a, double b) {
    QPolygonF samples;
    for (int i = 0; i < x.size(); ++i)
        samples += QPointF(x[i], y[i]);

    QwtPlotCurve *curve1 = new QwtPlotCurve("原始数据");
    curve1->setSamples(samples);
    curve1->setStyle(QwtPlotCurve::Dots);

    QwtSymbol *curve1_symbols = new QwtSymbol( QwtSymbol::Ellipse);
    curve1_symbols->setSize(5);
    curve1_symbols->setPen( Qt::red );
    curve1->setSymbol(curve1_symbols);
    curve1->attach(graph_plot);

    samples.clear();
    for (int i = 0; i < x.size(); ++i)
        samples += QPointF(x[i], b * x[i] + a);
    QwtPlotCurve *curve2 = new QwtPlotCurve("拟合曲线");
    curve2->setSamples(samples);
    curve2->setStyle(QwtPlotCurve::Lines);
    QwtSymbol *curve2_symbols = new QwtSymbol( QwtSymbol::XCross);
    curve2_symbols->setSize(3);
    curve2_symbols->setPen( Qt::blue );
    curve2->setSymbol(curve2_symbols);
    curve2->setPen(Qt::blue);
    curve2->attach(graph_plot);

    //scatter_plot->resize(800, 600);
    //scatter_plot->replot();
}

void QwtGraphPlotCustom::plotForSpectral(const QVector<double> &f, const QVector<double> &YY) {
    QPolygonF samples;
    for (int i = 0; i < f.size(); ++i)
        samples += QPointF(f[i], YY[i]);

    QwtPlotCurve *curve = new QwtPlotCurve("谱分析曲线");
    curve->setSamples(samples);
    curve->setStyle(QwtPlotCurve::Lines);
    QwtSymbol *curve_symbols = new QwtSymbol( QwtSymbol::XCross);
    curve_symbols->setSize(1);
    curve_symbols->setPen( Qt::blue );
    curve->setSymbol(curve_symbols);
    curve->setPen(Qt::blue);
    curve->attach(graph_plot);
}

void QwtGraphPlotCustom::plotFor1DMaxEntropy(const QVector<double> &yy1, const QVector<double> &yy2) {
    QPolygonF samples;
    for (int i = 0; i < yy1.size(); ++i)
        samples += QPointF(yy1[i], yy2[i]);

    QwtPlotCurve *curve = new QwtPlotCurve("一维最大熵曲线");
    curve->setSamples(samples);
    curve->setStyle(QwtPlotCurve::Lines);
    QwtSymbol *curve_symbols = new QwtSymbol( QwtSymbol::XCross);
    curve_symbols->setSize(1);
    curve_symbols->setPen( Qt::blue );
    curve->setSymbol(curve_symbols);
    curve->setPen(Qt::blue);
    curve->attach(graph_plot);
}

void QwtGraphPlotCustom::plotForCurve(const QVector<double> &x, const QVector<QVector<double> > &yy) {
    int i = 7;
    for (auto it = yy.begin(); it != yy.end(); ++it, ++i) {
        QPolygonF samples;
        for (int j = 0; j < it->size(); ++j) {
            if (x.size() == 0)
                samples += QPointF(j + 1, (*it)[j]);
            else
                samples += QPointF(x[j], (*it)[j]);
        }
        QwtPlotCurve *curve = new QwtPlotCurve("curve1");
        curve->setSamples(samples);
        curve->setStyle(QwtPlotCurve::Lines);
        QwtSymbol *curve_symbols = new QwtSymbol( QwtSymbol::XCross);
        curve_symbols->setSize(3);
        curve_symbols->setPen((Qt::GlobalColor)i);
        curve->setSymbol(curve_symbols);
        curve->setPen((Qt::GlobalColor)i);
        curve->attach(graph_plot);
    }
}

void QwtGraphPlotCustom::plotForScatter(const QVector<double> &x, const QVector<double> &y) {
    QPolygonF samples;
    for (int i = 0; i < x.size(); ++i)
        samples += QPointF(x[i], y[i]);

    qDebug()<<"test scatter.";
    QwtPlotCurve *curve = new QwtPlotCurve("散点图");
    curve->setSamples(samples);
    curve->setStyle(QwtPlotCurve::NoCurve);
    QwtSymbol *curve_symbols = new QwtSymbol( QwtSymbol::XCross);
    curve_symbols->setSize(3);
    curve_symbols->setPen( Qt::blue );
    curve->setSymbol(curve_symbols);
    curve->setPen(Qt::blue);
    curve->attach(graph_plot);
}

void QwtGraphPlotCustom::plotForBarChart(const QVector<double> &y) {
    //scatter_plot = new QwtP

}

void QwtGraphPlotCustom::plotForPolarRose(const QVector<double> &windspeed, const QVector<double> &winddir) {

    qDebug()<<"size speed = "<<windspeed.size()<<", size dir = "<<winddir.size();
}

//void ScatterPlot::setSamples(const QVector<double> &x, const QVector<double> &y) {
//    //qDebug() << "enter setSamples";
//    if (x.size() != y.size()) {
//        //qDebug() << "Input Data Size Error!";
//        return;
//    }
//    QPolygonF samples;
//    for (int i = 0; i < x.size(); ++i)
//        samples += QPointF(x[i], y[i]);
//    scatter_plot->setSamples( samples );
//    scatter_plot->replot();
//}

void QwtGraphPlotCustom::setXAxisLabel(QString xlabel)
{
    graph_plot->setXAxisTitle(xlabel);
}

void QwtGraphPlotCustom::setYAxisLabel(QString ylabel)
{
    graph_plot->setYAxisTitle(ylabel);
}
