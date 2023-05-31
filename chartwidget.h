#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QList>
#include <QPointF>
#include <QChart>
#include <QLineSeries>
#include <algorithm>

namespace Ui {
class ChartWidget;
}

class ChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = nullptr, QList<QPointF>* _data = nullptr);
    ~ChartWidget();

private:
    Ui::ChartWidget *ui;
    QList<QPointF>* data;
    QLineSeries* line;
    QChart* chart;

};

inline bool cmp(QPointF& a, QPointF& b) { return a.rx() < b.rx();}

#endif // CHARTWIDGET_H
