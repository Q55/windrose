#include "qwtgraphplotcustom.h"
#include "plot.h"

#include <qwt_interval_symbol.h>
#include <qwt_symbol.h>
#include <QDebug>
#include <qwt_plot_curve.h>
#include <qwt_plot_histogram.h>
#include <qwt_plot_barchart.h>
#include <qwt_plot_spectrogram.h>

//************for spectrogram***************
#include <qnumeric.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_color_map.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>

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


class MyZoomer: public QwtPlotZoomer
{
public:
    MyZoomer( QWidget *canvas ):
        QwtPlotZoomer( canvas )
    {
        setTrackerMode( AlwaysOn );
    }

    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
        QColor bg( Qt::white );
        bg.setAlpha( 200 );

        QwtText text = QwtPlotZoomer::trackerTextF( pos );
        text.setBackgroundBrush( QBrush( bg ) );
        return text;
    }
};

class SpectrogramData: public QwtRasterData
{
private:
    QMap<QPair<double, double>, double > rasterData;
    double xLength;
    double yLength;
    double minZValue;
    double maxZValue;
public:
    SpectrogramData()
    {

    }

    //返回值表示错误码
    int initSpectrogramData(const QVector<QVector<double> > &data)
    {
        if (data.empty())
            return -1;
        int matrixLength = data[0].size();
        int n = data.size();

        //rasterData.resize(data.size());
        xLength = (double)n;
        yLength = (double)matrixLength;
        minZValue = MAXFLOAT;
        maxZValue = 0.0;
        for (int i = 0; i < n; ++i) {
            if (matrixLength != data[i].size() )
            {
                qDebug() << "It is not a matrix";
                return -2;
            }
            //rasterData[i].resize(matrixLength);
            for (int j = 0; j < matrixLength; ++j) {
                rasterData.insert(qMakePair(double(i), double(j)), data[i][j]);
                if (minZValue > data[i][j])
                {
                    minZValue = data[i][j];
                }
                if (maxZValue < data[i][j])
                {
                    maxZValue = data[i][j];
                }
            }
        }
        return 0;
    }

    void setMyInterval()
    {
        setInterval( Qt::XAxis, QwtInterval( 0.0, xLength ) );
        setInterval( Qt::YAxis, QwtInterval( 0.0, yLength ) );
        setInterval( Qt::ZAxis, QwtInterval( minZValue, maxZValue ) );
    }

    virtual double value( double x, double y ) const
    {
        return rasterData.value(qMakePair(x, y));
    }
};

class LinearColorMapRGB: public QwtLinearColorMap
{
public:
    LinearColorMapRGB():
        QwtLinearColorMap( Qt::darkCyan, Qt::red, QwtColorMap::RGB )
    {
        addColorStop( 0.1, Qt::cyan );
        addColorStop( 0.6, Qt::green );
        addColorStop( 0.95, Qt::yellow );
    }
};

void QwtGraphPlotCustom::plotFor2DMaxEntropyDensity ( const QVector<QVector<double> > &data ) {

    QwtPlotSpectrogram* d_spectrogram = new QwtPlotSpectrogram("密度图");
    d_spectrogram->setRenderThreadCount( 0 ); // use system specific thread count
    d_spectrogram->setCachePolicy( QwtPlotRasterItem::PaintCache );

    SpectrogramData *spectrogram_data = new SpectrogramData();
    spectrogram_data->initSpectrogramData(data);
    spectrogram_data->setMyInterval();

    d_spectrogram->setData( spectrogram_data );
    d_spectrogram->attach( graph_plot );

    const QwtInterval zInterval = d_spectrogram->data()->interval( Qt::ZAxis );

    // A color bar on the right axis
    QwtScaleWidget *rightAxis = graph_plot->axisWidget( QwtPlot::yRight );
    rightAxis->setTitle( "Intensity" );
    rightAxis->setColorBarEnabled( true );

    graph_plot->setAxisScale( QwtPlot::yRight, zInterval.minValue(), zInterval.maxValue() );
    graph_plot->enableAxis( QwtPlot::yRight );

//    graph_plot->plotLayout()->setAlignCanvasToScales( true );

    d_spectrogram->setColorMap( new LinearColorMapRGB() );
    rightAxis->setColorMap( zInterval, new LinearColorMapRGB() );

    // LeftButton for the zooming
    // MidButton for the panning
    // RightButton: zoom out by 1
    // Ctrl+RighButton: zoom out to full size

    QwtPlotZoomer* zoomer = new MyZoomer( graph_plot->canvas() );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3,
        Qt::RightButton );

    QwtPlotPanner *panner = new QwtPlotPanner( graph_plot->canvas() );
    panner->setAxisEnabled( QwtPlot::yRight, false );
    panner->setMouseButton( Qt::MidButton );

    // Avoid jumping when labels with more/less digits
    // appear/disappear when scrolling vertically

    const QFontMetrics fm( graph_plot->axisWidget( QwtPlot::yLeft )->font() );
    QwtScaleDraw *sd = graph_plot->axisScaleDraw( QwtPlot::yLeft );
    sd->setMinimumExtent( fm.width( "100.00" ) );

    const QColor c( Qt::darkBlue );
    zoomer->setRubberBandPen( c );
    zoomer->setTrackerPen( c );

//    QToolBar *toolBar = new QToolBar( this );

//    QCheckBox *btnSpectrogram = new QCheckBox( "Spectrogram", toolBar );
//    toolBar->addWidget( btnSpectrogram );
//    connect( btnSpectrogram, SIGNAL( toggled( bool ) ),
//        d_plot, SLOT( showSpectrogram( bool ) ) );

//    QCheckBox *btnContour = new QCheckBox( "Contour", toolBar );
//    toolBar->addWidget( btnContour );
//    connect( btnContour, SIGNAL( toggled( bool ) ),
//        d_plot, SLOT( showContour( bool ) ) );

//    addToolBar( toolBar );
//    btnSpectrogram->setChecked( true );
//    btnContour->setChecked( false );
    d_spectrogram->setDisplayMode( QwtPlotSpectrogram::ImageMode, true );
    d_spectrogram->setDefaultContourPen( QPen( Qt::black, 0 ) );
    d_spectrogram->setDisplayMode( QwtPlotSpectrogram::ContourMode, true );
    graph_plot->replot();

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

    QwtPlotBarChart *bar_chart = new QwtPlotBarChart("柱状图");
    bar_chart->setSamples(samples);
    bar_chart->attach(graph_plot);
}

//void QwtGraphPlotCustom::plotForPolarRose(const QVector<double> &windspeed, const QVector<double> &winddir) {

//    qDebug()<<"size speed = "<<windspeed.size()<<", size dir = "<<winddir.size();
//}

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
