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
#include <qwt_plot_item.h>
#include <qwt_picker_machine.h>
#include <qwt_painter.h>
//************for spectrogram***************
#include <QVector>
#include "plotspectrogram.h"
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qslider.h>
#include <qlabel.h>
#include <qcheckbox.h>

class SAXYDataTracker: public QwtPlotPicker
{
public:
    SAXYDataTracker(QWidget * canvas) : QwtPlotPicker( canvas ){
        //setTrackerMode( QwtPlotPicker::AlwaysOn );
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

class barChartPicker: public QwtPlotPicker
{
public:
    barChartPicker( QWidget *canvas ):QwtPlotPicker( canvas )
    {
        const QColor c( Qt::darkBlue );
        setRubberBandPen(c);
        setTrackerPen(c);
//        setTrackerMode( QwtPlotPicker::ActiveOnly );
//        setRubberBand( UserRubberBand  );
//        setStateMachine( new QwtPickerTrackerMachine() );
//        connect (this,&QwtPicker::moved,this,&barChartPicker::mouseMove);
//        if( plot () )
//            connect ( plot(),&QwtPlot::itemAttached,this,&barChartPicker::itemAttached );
    }
protected:
    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
        //QString text = QString::number(pos.x()) + QString( "%1" ).arg( pos.y(), 0, 'f', 1 );
        QString text = QString::number( pos.x() ) + "," + QString::number( pos.y() );
        QwtText qwttext( text );
        return qwttext;
    }
};

void QwtGraphPlotCustom::setMouseActionZoomer() {
    move_->setChecked(false);
    zoomer_->setChecked(true);

    graph_plot->setMouseActionByType(0);
}

void QwtGraphPlotCustom::setMouseActionMove() {
    move_->setChecked(true);
    zoomer_->setChecked(false);

    graph_plot->setMouseActionByType(1);
}

QwtGraphPlotCustom::QwtGraphPlotCustom() {

    graph_plot = new Plot(this);
    //graph_plot->setTitle( "数据分析图" );
    setCentralWidget( graph_plot );

    toolBar_ = new QToolBar(this);
    zoomer_ = new QToolButton(toolBar_);
    zoomer_->setText("缩放");
    zoomer_->setCheckable(true);
    toolBar_->addWidget(zoomer_);
    move_ = new QToolButton(toolBar_);
    move_->setText("平移");
    move_->setCheckable(true);
    toolBar_->addWidget(move_);

    addToolBar(toolBar_);
    //this->addToolBar(Qt::RightToolBarArea,toolBar);

    connect(zoomer_, SIGNAL(clicked()), this, SLOT(setMouseActionZoomer()));
    connect(move_, SIGNAL(clicked()), this, SLOT(setMouseActionMove()));

    //graph_plot->setFixedSize(QSize(800, 600));
    resize(900, 500);
}

void QwtGraphPlotCustom::plotForCorrelation(const QVector<double> &x, const QVector<double> &y) {

    QPolygonF samples;
    for (int i = 0; i < x.size(); ++i)
        samples += QPointF(x[i], y[i]);

    //graph_plot->setTitle("相关性分析结果示意图");
    QwtPlotCurve *curve1 = new QwtPlotCurve("curve1");
    curve1->setSamples(samples);
    curve1->setStyle(QwtPlotCurve::Sticks);
    curve1->attach(graph_plot);

    QwtPlotCurve *curve2 = new QwtPlotCurve("curve2");
    curve2->setSamples(samples);
    curve2->setStyle(QwtPlotCurve::Lines);
    curve2->attach(graph_plot);


    graph_plot->zoomer->setZoomBase();
    graph_plot->zoomer->setEnabled(false);
    SAXYDataTracker *pick= new SAXYDataTracker(graph_plot->canvas());
    //scatter_plot->resize(800, 600);

    //scatter_plot->replot();
}

void QwtGraphPlotCustom::plotForWeightedFit(const QVector<double> &x, const QVector<double> &y, double a, double b) {
    QPolygonF samples;
    for (int i = 0; i < x.size(); ++i)
        samples += QPointF(x[i], y[i]);

    //graph_plot->setTitle("曲线拟合结果示意图");
    QwtPlotCurve *curve1 = new QwtPlotCurve("原始数据");
    curve1->setSamples(samples);
    curve1->setStyle(QwtPlotCurve::Dots);

    QwtSymbol *curve1_symbols = new QwtSymbol( QwtSymbol::Ellipse);
    curve1_symbols->setSize(5);
    //curve1_symbols->setPen( Qt::red );
    curve1->setSymbol(curve1_symbols);
    curve1->attach(graph_plot);
    QwtLegend *legend_orig = new QwtLegend();
    QFont font;
    font.setPointSize(10);
    legend_orig->setFont(font);
    graph_plot->insertLegend(legend_orig, QwtPlot::RightLegend);

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
    QwtLegend *legend_weight = new QwtLegend();
    QFont font2;
    font2.setPointSize(10);
    legend_weight->setFont(font2);
    graph_plot->insertLegend(legend_weight, QwtPlot::RightLegend);

    graph_plot->zoomer->setZoomBase();
//    graph_plot->zoomer->setEnabled(false);
    SAXYDataTracker *pick= new SAXYDataTracker(graph_plot->canvas());
    //scatter_plot->resize(800, 600);
    //scatter_plot->replot();
}

void QwtGraphPlotCustom::plotForSpectral(const QVector<double> &f, const QVector<double> &YY) {
    QPolygonF samples;
    for (int i = 0; i < f.size(); ++i)
        samples += QPointF(f[i], YY[i]);

    //graph_plot->setTitle( "谱分析结果示意图" );
    QwtPlotCurve *curve = new QwtPlotCurve("谱分析曲线");
    curve->setSamples(samples);
    curve->setStyle(QwtPlotCurve::Lines);
    QwtSymbol *curve_symbols = new QwtSymbol( QwtSymbol::XCross);
    curve_symbols->setSize(1);
    curve_symbols->setPen( Qt::blue );
    curve->setSymbol(curve_symbols);
    curve->setPen(Qt::blue);
    curve->attach(graph_plot);
    SAXYDataTracker *pick= new SAXYDataTracker(graph_plot->canvas());
    graph_plot->zoomer->setEnabled(false);
    graph_plot->zoomer->setZoomBase();
}

void QwtGraphPlotCustom::plotForXYData(const QVector<double> &x, const QVector<double> &y) {
    QPolygonF samples;
    for (int i = 0; i < x.size(); ++i)
        samples += QPointF(x[i], y[i]);

    //graph_plot->setTitle( "X-Y曲线图" );
    QwtPlotCurve *curve = new QwtPlotCurve("X-Y曲线");
    curve->setSamples(samples);
    curve->setStyle(QwtPlotCurve::Lines);
    QwtSymbol *curve_symbols = new QwtSymbol( QwtSymbol::XCross);
    curve_symbols->setSize(1);
    curve_symbols->setPen( Qt::blue );
    curve->setSymbol(curve_symbols);
    curve->setPen(Qt::blue);
    curve->attach(graph_plot);
    SAXYDataTracker *pick= new SAXYDataTracker(graph_plot->canvas());
    graph_plot->zoomer->setEnabled(false);
    graph_plot->zoomer->setZoomBase();
}

void QwtGraphPlotCustom::plotFor1DMaxEntropy(const QVector<double> &yy1, const QVector<double> &yy2) {
    QPolygonF samples;
    for (int i = 0; i < yy1.size(); ++i)
        samples += QPointF(yy1[i], yy2[i]);

    //graph_plot->setTitle( "一维最大熵曲线图" );
    QwtPlotCurve *curve = new QwtPlotCurve("一维最大熵曲线");
    curve->setSamples(samples);
    curve->setStyle(QwtPlotCurve::Lines);
    QwtSymbol *curve_symbols = new QwtSymbol( QwtSymbol::XCross);
    curve_symbols->setSize(1);
    curve_symbols->setPen( Qt::blue );
    curve->setSymbol(curve_symbols);
    curve->setPen(Qt::blue);
    curve->attach(graph_plot);
    SAXYDataTracker *pick= new SAXYDataTracker(graph_plot->canvas());
    graph_plot->zoomer->setEnabled(false);
    graph_plot->zoomer->setZoomBase();
}

void QwtGraphPlotCustom::plotFor2DMaxEntropyDensity(const QVector<QVector<double> > &data) {
    spectrogram_plot = new PlotSpectrogram(data, this );
    //spectrogram_plot->setTitle("密度图");

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
        curve->setStyle(QwtPlotCurve::Lines);
        //curve->setStyle(QwtPlotCurve::Dots);
        QwtSymbol *curve_symbols = new QwtSymbol( QwtSymbol::XCross);
        curve_symbols->setSize(1);
        curve_symbols->setPen((Qt::GlobalColor)i);
        curve->setSymbol(curve_symbols);
        curve->setPen((Qt::GlobalColor)i);
        curve->attach(graph_plot);
        QwtLegend *legend = new QwtLegend();
        QFont font;
        font.setPointSize(10);
        legend->setFont(font);
        graph_plot->insertLegend(legend, QwtPlot::RightLegend);
    }
    SAXYDataTracker *pick= new SAXYDataTracker(graph_plot->canvas());
    graph_plot->zoomer->setZoomBase();
//    graph_plot->zoomer->setEnabled(true);
}

void QwtGraphPlotCustom::plotForScatter(const QVector<double> &x, const QVector<QVector<double> > &yy, const QVector<QString> &yy_names) {
    int i = 7;
    int j = 0;

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
        curve->setStyle(QwtPlotCurve::NoCurve);
        QwtSymbol *curve_symbols = new QwtSymbol( QwtSymbol::XCross);
        curve_symbols->setSize(3);
        curve_symbols->setPen( (Qt::GlobalColor)i );
        curve->setSymbol(curve_symbols);
        curve->setPen((Qt::GlobalColor)i);
        curve->attach(graph_plot);
        QwtLegend *legend = new QwtLegend();
        QFont font;
        font.setPointSize(10);
        legend->setFont(font);
        graph_plot->insertLegend(legend, QwtPlot::RightLegend);
    }
    SAXYDataTracker *pick= new SAXYDataTracker(graph_plot->canvas());

    graph_plot->zoomer->setZoomBase();
}

void QwtGraphPlotCustom::plotForBarChart(const QVector<double> &x, const QVector<double> &y) {
    QPolygonF samples;
    for (int j = 0; j < y.size(); ++j) {
        if (x.size() == 0)
            samples += QPointF(j + 1, y[j]);
        else
            samples += QPointF(x[j], y[j]);
    }

    QwtPlotBarChart *bar_chart = new QwtPlotBarChart("直方图");
    bar_chart->setSamples(samples);
    bar_chart->attach(graph_plot);
    graph_plot->setBarChart(true);

    const QColor c( Qt::darkBlue );
    graph_plot->zoomer->setRubberBandPen( c);
    graph_plot->zoomer->setTrackerPen( c );
    graph_plot->zoomer->setZoomBase();
//    barChartPicker *picker = new barChartPicker(graph_plot->canvas());
}

void QwtGraphPlotCustom::setXAxisLabel(QString xlabel)
{
    graph_plot->setXAxisTitle(xlabel);
}

void QwtGraphPlotCustom::setYAxisLabel(QString ylabel)
{
    graph_plot->setYAxisTitle(ylabel);
}
