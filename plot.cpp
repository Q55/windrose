#include "plot.h"
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_curve.h>
#include <QBrush>
#include <qwt_symbol.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_grid.h>
class DistancePicker: public QwtPlotPicker
{
public:
    DistancePicker( QWidget *canvas ):
        QwtPlotPicker( canvas )
    {
        setTrackerMode( QwtPicker::ActiveOnly );
        setStateMachine( new QwtPickerDragLineMachine() );
        setRubberBand( QwtPlotPicker::PolygonRubberBand );
    }

    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
        QwtText text;

        const QPolygon points = selection();
        if ( !points.isEmpty() )
        {
            QString num;
            num.setNum( QLineF( pos, invTransform( points[0] ) ).length() );

            QColor bg( Qt::green );
            bg.setAlpha( 200 );

            text.setBackgroundBrush( QBrush( bg ) );
            text.setText( num );
        }
        return text;
    }
};

Plot::Plot( QWidget *parent ):
    QwtPlot( parent ),
    d_curve( NULL )
{
//    canvas()->setStyleSheet(
//        "border: 2px solid Black;"
//        "border-radius: 15px;"
//        "( x1: 0, y1: 0, x2: 0, y2: 1,"
//            "stop: 0 LemonChiffon, stop: 1 PaleGoldenrod );"
//    );
//    QwtPlotCanvas *newcanvas=new QwtPlotCanvas();
//    newcanvas->setPalette(Qt::white);
//    newcanvas->setBorderRadius(10);
//    setCanvas( newcanvas );
    plotLayout()->setAlignCanvasToScales( true );

    canvas()->resize(800, 600);
    //plotLayout(AlignScales);

    // attach curve
    d_curve = new QwtPlotCurve();
    d_curve->setPen( QColor( "Black" ) );
    //d_curve->setCurveAttribute(fitten);

    // when using QwtPlotCurve::ImageBuffer simple dots can be
    // rendered in parallel on multicore systems.
    d_curve->setRenderThreadCount( 0 ); // 0: use QThread::idealThreadCount()

    d_curve->setCurveAttribute(QwtPlotCurve::Fitted, true);

    d_curve->attach( this );

    //QwtSymbol * symbol2 = new QwtSymbol( QwtSymbol::XCross, QBrush(Qt::white), QPen(Qt::red, 1), QSize(6,6));
    //QwtSymbol::Style  style = Cross;
    //setSymbol( symbol2 );
    //setSymbol(NULL);

    // panning with the left mouse button
    (void )new QwtPlotPanner( canvas() );

    // zoom in/out with the wheel
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier( canvas() );
    magnifier->setMouseButton( Qt::NoButton );

    // distanve measurement with the right mouse button
    DistancePicker *picker = new DistancePicker( canvas() );
    picker->setMousePattern( QwtPlotPicker::MouseSelect1, Qt::RightButton );
    picker->setRubberBandPen( QPen( Qt::blue ) );

    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableX( true );//设置网格线
    grid->enableY( true );
    grid->setMajorPen( Qt::black, 0, Qt::DotLine );
    grid->attach( this );

    //QSize sizeH = sizeHint();

}

void Plot::setSymbol( QwtSymbol *symbol )
{
    d_curve->setSymbol( symbol );

    if ( symbol == NULL )
    {
        d_curve->setStyle( QwtPlotCurve::Dots );
    }
}

void Plot::setSamples( const QVector<QPointF> &samples )
{
    d_curve->setPaintAttribute(
        QwtPlotCurve::ImageBuffer, samples.size() > 1000 );
    d_curve->setSamples( samples );
}

void Plot::setXAxisTitle(QString xlabel)
{
    setAxisTitle(QwtPlot::xBottom, xlabel);
}

void Plot::setYAxisTitle(QString ylabel)
{
    setAxisTitle(QwtPlot::yLeft, ylabel);
}

void Plot::appendCurve(QwtPlotCurve *append_curve)
{
    append_curve->attach(this);
}

void Plot::setCurveStyle(QwtPlotCurve::CurveStyle style)
{
    d_curve->setStyle(style);
}
