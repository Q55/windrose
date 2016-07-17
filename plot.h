#ifndef PLOT_H
#define PLOT_H
#include <qwt_plot.h>
#include <QVector>
#include <QString>
#include <qwt_plot_curve.h>
#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>

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

    void setBarChart(bool is_bar_chart) { is_bar_chart_ = is_bar_chart; }

//public Q_SLOTS:
//    void showContour ( bool on );
//    void showSpectrogram ( bool on );

public slots:
    void setMouseActionByType(int);

private:
    QwtPlotCurve *d_curve;
public:
    QwtPlotZoomer* zoomer;
    QwtPlotPanner *panner;
    bool is_bar_chart_;
};


//class QwtPlotCurve;
//class QwtPlotItem;
//class SAXYDataTracker: public QwtPlotPicker
//{
//public:
//    SAXYDataTracker(QWidget * canvas);

//protected:
//    virtual QwtText trackerTextF(const QPointF & pos) const;
//    virtual QRect trackerRect(const QFont & font) const;
//    virtual void drawRubberBand (QPainter *painter) const;
//    void calcClosestPoint(const QPoint& pos);
//private:
//    // 记录最近点的信息
//    class closePoint
//    {
//    public:
//        closePoint();
//        QwtPlotCurve * curve() const{return this->m_curve;}
//        void setCurve(QwtPlotCurve * cur);
//        bool isValid() const;
//        QPointF getClosePoint() const;
//        int index() const{return this->m_index;}
//        void setIndex(int i){this->m_index = i;}
//        double distace() const{return this->m_distace;}
//        void setDistace(double d){this->m_distace = d;}
//        void setInvalid();
//    private:
//        QwtPlotCurve *m_curve;
//        int m_index;
//        double m_distace;
//    };
//    closePoint m_closePoint;
//private slots:
//    //捕获鼠标移动的槽
//    void mouseMove(const QPoint &pos);
//public slots:
//    void itemAttached(QwtPlotItem* plotItem,bool on);
//};

#endif // PLOT_H
