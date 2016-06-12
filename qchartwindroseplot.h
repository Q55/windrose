#ifndef QCHARTWINDROSEPLOT_H
#define QCHARTWINDROSEPLOT_H
#include <QtCharts/QPolarChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAreaSeries>
#include <QMainWindow>
#include <QVector>
#include "chartview.h"

QT_CHARTS_USE_NAMESPACE
class QChartWindRosePlot: public QWidget {
    Q_OBJECT

public:
    QChartWindRosePlot() {}
    QChartWindRosePlot(int angular_count, const QVector<double> &windspeed, const QVector<double> &winddir);
    void createPolarChartView();

private:
    double statsGraphSeries(const QVector<double> &windspeed, const QVector<double> &winddir); // return max count val
    void drawRose();

private:
    QPolarChart *chart_;
    QChartView *chart_view_;
    QValueAxis *chart_angular_axis_;
    int angular_count_;
    QValueAxis *chart_radial_axis_;
    QVector<QVector<double> > chart_series_data_;
    int base_color_;
    double radial_max_;
    QVector<QString> legend_name_list_;
};

#endif // QCHARTWINDROSEPLOT_H
