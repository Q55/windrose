#include "qchartwindroseplot.h"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPolarChart>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#define radialCount 8

QChartWindRosePlot::QChartWindRosePlot(int angular_count, const QVector<double> &windspeed, const QVector<double> &winddir) {

    angular_count_ = angular_count;
    base_color_ = 7;
    legend_name_list_ = {"0 <= Ws < 2","2 <= Ws < 3","3 <= Ws < 4","4 <= Ws < 5","5 <= Ws < 6",
                        "6 <= Ws < 7","7 <= Ws < 8","Ws >= 8"};

    this->setWindowTitle("风玫瑰图");

    // create layout
    QVBoxLayout *legend_layout = new QVBoxLayout();
    for (int i = 0; i < radialCount; ++i) {
        QHBoxLayout *sublayout = new QHBoxLayout();
        QLabel *label = new QLabel("        ");
        label->setMaximumHeight(10);
        label->setAutoFillBackground(true);
        QPalette palette = label->palette();
        palette.setColor(label->backgroundRole(), (Qt::GlobalColor)(base_color_ + i));
        label->setPalette(palette);
        sublayout->addWidget(label);
        sublayout->addWidget(new QLabel(legend_name_list_[i]));
        sublayout->addStretch();

        legend_layout->addLayout(sublayout);
    }
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addLayout(legend_layout);

    radial_max_ = statsGraphSeries(windspeed, winddir);
    radial_max_ = radial_max_ * 1.02; // max 10% of original radial_max
    createPolarChartView();
    layout->addWidget(chart_view_);

    setLayout(layout);

    //show();

    //setCentralWidget(this);
}

void QChartWindRosePlot::createPolarChartView() {

    chart_ = new QPolarChart();
    //chart_->setTitle("Use arrow keys to scroll, +/- to zoom, and space to switch chart type.");
    chart_->setTitle("WindRose");

    chart_angular_axis_ = new QValueAxis();
    chart_angular_axis_->setTickCount(angular_count_ + 1); // First and last ticks are co-located on 0/360 angle.
    chart_angular_axis_->setLabelFormat("%d");
    chart_angular_axis_->setShadesVisible(false);
    chart_angular_axis_->setShadesBrush(QBrush(QColor(249, 249, 255)));
    chart_->addAxis(chart_angular_axis_, QPolarChart::PolarOrientationAngular);

    chart_radial_axis_ = new QValueAxis();
    chart_radial_axis_->setRange(0, radial_max_);
    chart_radial_axis_->setTickCount( (int)radialCount + 1 );
    chart_radial_axis_->setLabelsVisible(false);
    //radialAxis->setLabelFormat("%.1f");
    chart_->addAxis(chart_radial_axis_, QPolarChart::PolarOrientationRadial);

    drawRose();

    chart_angular_axis_->setRange(0, 360);
    chart_radial_axis_->setRange(0, radial_max_);

    chart_->legend()->setVisible(false);

    chart_view_ = new ChartView();
    chart_view_->setChart(chart_);
    chart_view_->setRenderHint(QPainter::Antialiasing);
}

void QChartWindRosePlot::drawRose() {

    double interval_angular = 360 / angular_count_;
    double left_a, right_a, bottom_r, up_r;
    for (int i = 0; i < chart_series_data_.size(); ++i) {
        //if (i == 2) return;
        left_a = i * interval_angular;
        right_a = (i + 1) * interval_angular;
        double accu_radial = 0.0;
        for (int j = 0; j < chart_series_data_[i].size(); ++j) {
            if (chart_series_data_[i][j] > 0) {
                bottom_r = accu_radial;
                up_r = chart_series_data_[i][j] + bottom_r;
                accu_radial += chart_series_data_[i][j];

                QLineSeries *lower;
                if (bottom_r == 0.0) {
                    lower = new QLineSeries();
                    lower->append(left_a, up_r);
                    lower->append(0, 0);
                    lower->append(right_a, up_r);
                } else if (bottom_r > 0.0) {
                    lower = new QSplineSeries();
                    for (double k = left_a; k <= right_a; k = k + 0.1)
                        lower->append(k, bottom_r);
                }
                lower->hide();
                lower->setPointLabelsVisible(false);

                QSplineSeries *up = new QSplineSeries();
                for (double k = left_a; k <= right_a; k = k + 0.1)
                    up->append(k, up_r);
                up->hide();
                up->setPointLabelsVisible(false);

                QAreaSeries *area = new QAreaSeries();
                area->setUpperSeries(up);
                area->setLowerSeries(lower);
                area->setOpacity(0.5);
                area->setColor((Qt::GlobalColor)(base_color_ + j));

                chart_->addSeries(up);
                chart_->addSeries(lower);
                chart_->addSeries(area);

                //lower->attachAxis(angularAxis);
                //lower->attachAxis(radialAxis);
                //up->attachAxis(angularAxis);
                //up->attachAxis(radialAxis);
                area->attachAxis(chart_angular_axis_);
                area->attachAxis(chart_radial_axis_);
            }
        }
    }
}

double QChartWindRosePlot::statsGraphSeries(const QVector<double> &windspeed, const QVector<double> &winddir) {
    chart_series_data_.resize(angular_count_);
    for (int i = 0; i < chart_series_data_.size(); ++i)
        chart_series_data_[i].resize(radialCount);

    for (int i = 0; i < chart_series_data_.size(); ++i)
        for (int j = 0; j < chart_series_data_[i].size(); ++j)
            chart_series_data_[i][j] = 0.0;

    double interval_angular = 360 / angular_count_;

    for (int i = 0; i < winddir.size() && i < windspeed.size(); ++i) {
        int row = winddir[i] / interval_angular;
        if (row == angular_count_) row = row - 1;

        double speed = windspeed[i];
        int col = 0;
        if (speed >=0 && speed < 2)
            col = 0;
        else if (speed >=2 && speed < 3)
            col = 1;
        else if (speed >= 3 && speed < 4)
            col = 2;
        else if (speed >= 4 && speed < 5)
            col = 3;
        else if (speed >= 5 && speed < 6)
            col = 4;
        else if (speed >= 6 && speed < 7)
            col = 5;
        else if (speed >=7 && speed < 8)
            col = 6;
        else if (speed >=8 )
            col = 7;

        chart_series_data_[row][col]++;
    }

    double max = 0.0;
    int total_count = windspeed.size();
    for (int i = 0; i < chart_series_data_.size(); ++i) {
        double temp_max = 0.0;
        for (int j = 0; j < chart_series_data_[i].size(); ++j) {
            chart_series_data_[i][j] = (double)(chart_series_data_[i][j] / (double)total_count * (double)100);
            temp_max += chart_series_data_[i][j];
        }
        if (max < temp_max) max = temp_max;
    }

    return max;
}
