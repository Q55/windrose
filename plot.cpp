#include "plot.h"
#include <qwt_plot_magnifier.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
//#include <qwt_picker_machine.h>
#include <qwt_plot_curve.h>
#include <QBrush>
#include <qwt_symbol.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_grid.h>
//#include <qwt_painter.h>


//class DistancePicker: public QwtPlotPicker
//{
//public:
//    DistancePicker( QWidget *canvas ):
//        QwtPlotPicker( canvas )
//    {
//        setTrackerMode( QwtPicker::ActiveOnly );
//        setStateMachine( new QwtPickerDragLineMachine() );
//        setRubberBand( QwtPlotPicker::PolygonRubberBand );
//    }

//    virtual QwtText trackerTextF( const QPointF &pos ) const
//    {
//        QwtText text;

//        const QPolygon points = selection();
//        if ( !points.isEmpty() )
//        {
//            QString num;
//            num.setNum( QLineF( pos, invTransform( points[0] ) ).length() );

//            QColor bg( Qt::green );
//            bg.setAlpha( 200 );

//            text.setBackgroundBrush( QBrush( bg ) );
//            text.setText( num );
//        }
//        return text;
//    }
//};


class CustZoomer: public QwtPlotZoomer
{
public:
    CustZoomer( QWidget *canvas ):
        QwtPlotZoomer( canvas )
    {
        //setTrackerMode( AlwaysOn );

        //2016-07-19 TEST FOR DEBUG
        setMousePattern( QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier );
        setMousePattern( QwtEventPattern::MouseSelect3, Qt::RightButton );
        const QColor c( Qt::darkBlue );
        setRubberBandPen( c );
        setTrackerPen( c );
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

// 0--zoomber, 1--movable
void Plot::setMouseActionByType(int type) {

    if (type == 0) {
        panner->setEnabled(false);
        zoomer->setEnabled(true);

        zoomer->setMousePattern( QwtEventPattern::MouseSelect1, Qt::LeftButton );
        zoomer->setMousePattern( QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier );
        zoomer->setMousePattern( QwtEventPattern::MouseSelect3, Qt::RightButton );
//        const QColor c( Qt::darkBlue );
//        zoomer->setRubberBandPen( c );
//        zoomer->setTrackerPen( c );
    } else if (type == 1){
        zoomer->setEnabled(false);
        panner->setEnabled(true);

        QwtPlotPanner *panner = new QwtPlotPanner( canvas() );
        //panner->setAxisEnabled( QwtPlot::yRight, false );
        panner->setMouseButton( Qt::LeftButton );
        (void) new QwtPlotMagnifier( canvas() ); // 滚轮放大缩小
    }

    //replot();
}

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
    //is_bar_chart_ = false;
    plotLayout()->setAlignCanvasToScales( true );

    canvas()->resize(800, 600);

    //plotLayout->AlignScales();


//    // when using QwtPlotCurve::ImageBuffer simple dots can be
//    // rendered in parallel on multicore systems.
//    d_curve->setRenderThreadCount( 0 ); // 0: use QThread::idealThreadCount()

//    d_curve->setCurveAttribute(QwtPlotCurve::Fitted, true);

//    d_curve->attach( this );

    // LeftButton for the zooming
    // MidButton for the panning
    // RightButton: zoom out by 1
    // Ctrl+RighButton: zoom out to full size
    //DEBUG ZYN.
    zoomer = new QwtPlotZoomer(canvas()); //CustZoomer( canvas() );
    //if (is_bar_chart_) zoomer->setTrackerMode(QwtPicker::AlwaysOn);
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3, Qt::RightButton );
    const QColor c( Qt::darkBlue );
    const QColor qbackground( canvas()->palette().color(QPalette::Background) );
    zoomer->setRubberBandPen( c);
    zoomer->setTrackerPen( qbackground );

    // 平移
    panner = new QwtPlotPanner( canvas() );
    panner->setEnabled(false);
//    panner->setAxisEnabled( QwtPlot::yRight, false );
//    panner->setMouseButton( Qt::MidButton );

//    (void) new QwtPlotMagnifier( canvas() ); // 滚轮放大缩小

    // Avoid jumping when labels with more/less digits appear/disappear when scrolling vertically
//    const QFontMetrics fm( axisWidget( QwtPlot::yLeft )->font() );
//    QwtScaleDraw *sd = axisScaleDraw( QwtPlot::yLeft );
//    sd->setMinimumExtent( fm.width( "100.00" ) );

    // distanve measurement with the right mouse button
//    DistancePicker *picker = new DistancePicker( canvas() );
//    picker->setMousePattern( QwtPlotPicker::MouseSelect1, Qt::RightButton );
//    picker->setRubberBandPen( QPen( Qt::blue ) );
//    SAXYDataTracker *pick= new SAXYDataTracker(canvas());

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




