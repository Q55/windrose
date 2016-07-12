#include "plot.h"
#include <qwt_plot_magnifier.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_curve.h>
#include <QBrush>
#include <qwt_symbol.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_grid.h>
#include <qwt_painter.h>

class SAXYDataTracker: public QwtPlotPicker
{
public:
    SAXYDataTracker(QWidget * canvas) : QwtPlotPicker( canvas ){
        setTrackerMode( QwtPlotPicker::ActiveOnly );
        setRubberBand( UserRubberBand  );
        setStateMachine( new QwtPickerTrackerMachine() );
        connect (this,&QwtPicker::moved,this,&SAXYDataTracker::mouseMove);
        if(plot ())
            connect (plot(),&QwtPlot::itemAttached,this,&SAXYDataTracker::itemAttached );
    }

protected:
    virtual QwtText trackerTextF(const QPointF & pos) const {
        QwtText trackerText;
        if(!m_closePoint.isValid ())
            return trackerText;
        trackerText.setColor( Qt::black );
        QColor lineColor = m_closePoint.curve()->pen ().color ();
        QColor bkColor(lineColor);
        bkColor.setAlpha (30);
        trackerText.setBorderPen( m_closePoint.curve()->pen () );
        trackerText.setBackgroundBrush( bkColor );
        QPointF point = m_closePoint.getClosePoint ();
        QString info = QStringLiteral("<font color=\"%1\">y:%2</font><br>")
                       .arg(lineColor.name ()).arg(point.y ())
                       +
                       QStringLiteral("<font color=\"%1\">x:%2</font>")
                                          .arg(lineColor.name ()).arg(point.x ());
        trackerText.setText( info );
        trackerText.setBorderRadius (5);
        return trackerText;
    }
    virtual QRect trackerRect(const QFont & font) const {
        QRect r = QwtPlotPicker::trackerRect( font );
        r += QMargins(5,5,5,5);
        return r;
    }
    virtual void drawRubberBand (QPainter *painter) const {
        if ( !isActive() || rubberBand() == NoRubberBand ||
            rubberBandPen().style() == Qt::NoPen )
        {
            return;
        }
        if(!m_closePoint.isValid ())
            return;
        QPolygon pickedPoint = pickedPoints ();
        if(pickedPoint.count () < 1)
            return;
        //获取鼠标的客户坐标位置
        const QPoint pos = pickedPoint[0];
        const QPointF closePoint = m_closePoint.getClosePoint ();
        const QPoint cvp = transform (closePoint);
        QwtPainter::drawLine (painter,pos,cvp);
        QRect r(0,0,10,10);
        r.moveCenter (cvp);
        QwtPainter::drawRect (painter,r);
        //QwtPainter::drawEllipse (painter,r);
    }
    void calcClosestPoint(const QPoint& pos) {
        const QwtPlotItemList curveItems =
            plot()->itemList( QwtPlotItem::Rtti_PlotCurve );
        if(curveItems.size () <= 0)
            return;
        //把屏幕坐标转换为图形的数值坐标
        QPointF mousePoint = invTransform(pos);
        //记录最短的距离，默认初始化为double的最大值
        double distance = std::numeric_limits<double>::max ();
        //记录前一次最近点的曲线指针
        QwtPlotCurve * oldCur = m_closePoint.curve ();
        for ( int i = 0; i < curveItems.size(); ++i )
        {
            QwtPlotCurve * cur = static_cast<QwtPlotCurve *>( curveItems[i] );
            int index = cur->closestPoint (pos);
            if(-1 == index)
                continue;
            QPointF p = cur->sample (index);
            QLineF lp(p,mousePoint);
            double l = lp.length ();
            if(l < distance)
            {
                m_closePoint.setDistace(l);
                m_closePoint.setIndex(index);
                m_closePoint.setCurve(cur);
                distance = l;
            }
        }
        //说明最近点的曲线更换了，标记线的颜色换为当前曲线的颜色
        if(m_closePoint.isValid () && oldCur!=m_closePoint.curve ())
        {
            QPen p(m_closePoint.curve ()->pen ());
            p.setWidth (1);
            setRubberBandPen (p);
        }
    }
private:
    // 记录最近点的信息
    class closePoint
    {
    public:
        closePoint():m_curve(nullptr)
          ,m_index(-1)
          ,m_distace(std::numeric_limits<double>::max ()) {}
        QwtPlotCurve * curve() const{return this->m_curve;}
        void setCurve(QwtPlotCurve * cur) {this->m_curve = cur;}
        bool isValid() const {return ((this->curve() != nullptr) && (this->index() > 0));}
        QPointF getClosePoint() const {
            if(isValid ())
                return this->curve()->sample (this->index());
            return QPointF();
        }
        int index() const{return this->m_index;}
        void setIndex(int i){this->m_index = i;}
        double distace() const{return this->m_distace;}
        void setDistace(double d){this->m_distace = d;}
        void setInvalid() {
            setCurve (nullptr);
            setIndex (-1);
            setDistace (std::numeric_limits<double>::max ());
        }
    private:
        QwtPlotCurve *m_curve;
        int m_index;
        double m_distace;
    };
    closePoint m_closePoint;
private slots:
    //捕获鼠标移动的槽
    void mouseMove(const QPoint &pos) { calcClosestPoint(pos); }
public slots:
    void itemAttached(QwtPlotItem* plotItem,bool on) {
        if(!on)
        {
            if(QwtPlotItem::Rtti_PlotCurve == plotItem->rtti ())
            {
                QwtPlotCurve * cur = static_cast<QwtPlotCurve *>( plotItem);
                if(cur == m_closePoint.curve())
                    m_closePoint.setInvalid ();
            }
        }
    }
};

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
    //plotLayout->AlignScales();

    // attach curve
//    d_curve = new QwtPlotCurve();
//    d_curve->setPen( QColor( "Black" ) );
//    //d_curve->setCurveAttribute(fitten);

//    // when using QwtPlotCurve::ImageBuffer simple dots can be
//    // rendered in parallel on multicore systems.
//    d_curve->setRenderThreadCount( 0 ); // 0: use QThread::idealThreadCount()

//    d_curve->setCurveAttribute(QwtPlotCurve::Fitted, true);

//    d_curve->attach( this );

    // LeftButton for the zooming
    // MidButton for the panning
    // RightButton: zoom out by 1
    // Ctrl+RighButton: zoom out to full size
    zoomer = new CustZoomer( canvas() );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3, Qt::RightButton );
    const QColor c( Qt::darkBlue );
    zoomer->setRubberBandPen( c );
    zoomer->setTrackerPen( c );

    // 平移
    QwtPlotPanner *panner = new QwtPlotPanner( canvas() );
    panner->setAxisEnabled( QwtPlot::yRight, false );
    panner->setMouseButton( Qt::MidButton );

    (void) new QwtPlotMagnifier( canvas() ); // 滚轮放大缩小

    // Avoid jumping when labels with more/less digits appear/disappear when scrolling vertically
//    const QFontMetrics fm( axisWidget( QwtPlot::yLeft )->font() );
//    QwtScaleDraw *sd = axisScaleDraw( QwtPlot::yLeft );
//    sd->setMinimumExtent( fm.width( "100.00" ) );

    // distanve measurement with the right mouse button
//    DistancePicker *picker = new DistancePicker( canvas() );
//    picker->setMousePattern( QwtPlotPicker::MouseSelect1, Qt::RightButton );
//    picker->setRubberBandPen( QPen( Qt::blue ) );
    SAXYDataTracker *pick= new SAXYDataTracker(canvas());

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


//void Plot::showContour( bool on )
//{
//    d_spectrogram->setDisplayMode( QwtPlotSpectrogram::ContourMode, on );
//    replot();
//}


//for spectrogram
//void Plot::showSpectrogram( bool on )
//{
//    d_spectrogram->setDisplayMode( QwtPlotSpectrogram::ImageMode, on );
//    d_spectrogram->setDefaultContourPen(
//        on ? QPen( Qt::black, 0 ) : QPen( Qt::NoPen ) );

//    replot();
//}


