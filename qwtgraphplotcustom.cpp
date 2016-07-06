#include "qwtgraphplotcustom.h"
#include "plot.h"

#include <qwt_interval_symbol.h>
#include <qwt_symbol.h>
#include <QDebug>
#include <qwt_plot_curve.h>
#include <qwt_plot_histogram.h>
#include <qwt_plot_barchart.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_legend.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>

//************for spectrogram***************
#include <QVector>
#include "plotspectrogram.h"
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qslider.h>
#include <qlabel.h>
#include <qcheckbox.h>


QwtGraphPlotCustom::QwtGraphPlotCustom() {

    graph_plot = new Plot(this);
    graph_plot->setTitle( "数据分析图" );
    setCentralWidget( graph_plot );
//    (void) new QwtPlotMagnifier(graph_plot->canvas()); //使用滚轮放大/缩小
//    (void) new QwtPlotPanner(graph_plot->canvas());//使用鼠标左键平移

    //graph_plot->setFixedSize(QSize(800, 600));
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

    graph_plot->setTitle( "谱分析曲线图" );
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

void QwtGraphPlotCustom::plotForXYData(const QVector<double> &x, const QVector<double> &y) {
    QPolygonF samples;
    for (int i = 0; i < x.size(); ++i)
        samples += QPointF(x[i], y[i]);

    graph_plot->setTitle( "X-Y曲线图" );
    QwtPlotCurve *curve = new QwtPlotCurve("X-Y曲线");
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

    graph_plot->setTitle( "一维最大熵曲线图" );
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

void QwtGraphPlotCustom::plotFor2DMaxEntropyDensity(const QVector<QVector<double> > &data) {
    spectrogram_plot = new PlotSpectrogram(data, this );

    setCentralWidget( spectrogram_plot );

    QToolBar *toolBar = new QToolBar( this );

    toolBar->addWidget( new QLabel("Color Map " ) );
    QComboBox *mapBox = new QComboBox( toolBar );
    mapBox->addItem( "RGB" );
    mapBox->addItem( "Indexed Colors" );
    mapBox->addItem( "Hue" );
    mapBox->addItem( "Alpha" );
    mapBox->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    toolBar->addWidget( mapBox );
    connect( mapBox, SIGNAL( currentIndexChanged( int ) ),
             spectrogram_plot, SLOT( setColorMap( int ) ) );

    toolBar->addWidget( new QLabel( " Opacity " ) );
    QSlider *slider = new QSlider( Qt::Horizontal );
    slider->setRange( 0, 255 );
    slider->setValue( 255 );
    connect( slider, SIGNAL( valueChanged( int ) ),
        spectrogram_plot, SLOT( setAlpha( int ) ) );

    toolBar->addWidget( slider );
    toolBar->addWidget( new QLabel("   " ) );

    QCheckBox *btnSpectrogram = new QCheckBox( "Spectrogram", toolBar );
    toolBar->addWidget( btnSpectrogram );
    connect( btnSpectrogram, SIGNAL( toggled( bool ) ),
        spectrogram_plot, SLOT( showSpectrogram( bool ) ) );

    QCheckBox *btnContour = new QCheckBox( "Contour", toolBar );
    toolBar->addWidget( btnContour );
    connect( btnContour, SIGNAL( toggled( bool ) ),
        spectrogram_plot, SLOT( showContour( bool ) ) );

    addToolBar( toolBar );

    btnSpectrogram->setChecked( true );
    btnContour->setChecked( false );
}

void QwtGraphPlotCustom::plotForCurve(const QVector<double> &x, const QVector<QVector<double> > &yy, const QVector<QString> &yy_names) {
    int i = 7;
    int j = 0;
    graph_plot->setTitle("曲线图");
    for (auto it = yy.begin(); it != yy.end(); ++it, ++i, ++j) {
        QPolygonF samples;
        for (int j = 0; j < it->size(); ++j) {
            if (x.size() == 0)
                samples += QPointF(j + 1, (*it)[j]);
            else
                samples += QPointF(x[j], (*it)[j]);
        }
        QwtPlotCurve *curve = new QwtPlotCurve(yy_names[j]);
        curve->setSamples(samples);
       // curve->setStyle(QwtPlotCurve::Lines);
        curve->setStyle(QwtPlotCurve::Dots);
        QwtSymbol *curve_symbols = new QwtSymbol( QwtSymbol::XCross);
        curve_symbols->setSize(3);
        curve_symbols->setPen((Qt::GlobalColor)i);
        curve->setSymbol(curve_symbols);
        curve->setPen((Qt::GlobalColor)i);
        curve->attach(graph_plot);
        graph_plot->insertLegend(new QwtLegend(), QwtPlot::RightLegend);
    }
}

void QwtGraphPlotCustom::plotForScatter(const QVector<double> &x, const QVector<double> &y) {
    QPolygonF samples;
    for (int i = 0; i < x.size(); ++i)
        samples += QPointF(x[i], y[i]);

    graph_plot->setTitle("散点图");
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

void QwtGraphPlotCustom::plotForBarChart(const QVector<double> &x, const QVector<double> &y) {
    QPolygonF samples;
    for (int j = 0; j < y.size(); ++j) {
        if (x.size() == 0)
            samples += QPointF(j + 1, y[j]);
        else
            samples += QPointF(x[j], y[j]);
    }

    graph_plot->setTitle("柱状图");
    QwtPlotBarChart *bar_chart = new QwtPlotBarChart("柱状图");
    bar_chart->setSamples(samples);
    bar_chart->attach(graph_plot);
}

void QwtGraphPlotCustom::setXAxisLabel(QString xlabel)
{
    graph_plot->setXAxisTitle(xlabel);
}

void QwtGraphPlotCustom::setYAxisLabel(QString ylabel)
{
    graph_plot->setYAxisTitle(ylabel);
}
