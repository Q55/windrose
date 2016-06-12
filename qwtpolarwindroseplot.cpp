#include "qwtpolarwindroseplot.h"
#include "qwt_polar_grid.h"

QwtPolarWindRosePlot::QwtPolarWindRosePlot(QWidget *parent) : QMainWindow(parent) {
    polar_plot = new QwtPolarPlot();
    polar_plot->setTitle("风玫瑰图");
    //polar_plot->setPlotBackground (QBrush( Qt::red, Qt::SolidPattern ));

    setCentralWidget(polar_plot);
    polar_plot->setScale(QwtPolar::ScaleAzimuth, 0, 360, 20);
    polar_plot->setScale(QwtPolar::ScaleRadius, 0, 14, 2);

    QwtPolarGrid grid;
    grid.setFont (QFont("Times", 16, QFont::Bold));
    grid.setPen ( QPen(Qt::red, 2, Qt::DashLine) );
    grid.setAxisPen ( QwtPolar::AxisAzimuth, QPen(Qt::black, 1) );
    grid.setAxisPen ( QwtPolar::AxisLeft, QPen(Qt::black, 1) );

    grid.showGrid(QwtPolar::AxisAzimuth, true);
    grid.showGrid(QwtPolar::AxisLeft, true);
    grid.showGrid(QwtPolar::AxisRight, true);
    grid.showGrid(QwtPolar::AxisTop, true);
    grid.showGrid(QwtPolar::AxisBottom, true);
    grid.attach(polar_plot);

    polar_plot->setFixedSize(800, 600);
    //polar_plot->repaint();
}


void QwtPolarWindRosePlot::plotForPolarRose(const QVector<double> &windspeed, const QVector<double> &winddir) {

    qDebug()<<"size speed = "<<windspeed.size()<<", size dir = "<<winddir.size();
}


//void QwtPolarWindRosePlot::setXAxisLabel(QString xlabel)
//{
//    polar_plot->setsetXAxisTitle(xlabel);
//}

//void QwtPolarWindRosePlot::setYAxisLabel(QString ylabel)
//{
//    polar_plot->setYAxisTitle(ylabel);
//}
