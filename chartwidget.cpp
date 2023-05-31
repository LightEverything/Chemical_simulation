#include "chartwidget.h"
#include "ui_chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent, QList<QPointF>* _data) :
    QWidget(parent),
    ui(new Ui::ChartWidget),
    data(_data),
    line(new QLineSeries()),
    chart(new QChart())
{
    ui->setupUi(this);
    setAttribute(Qt :: WA_DeleteOnClose, true);

    // 对数据进行排序
    std::sort(data->begin(), data->end(), cmp);
    line->append(*data);
    line->setVisible(true);
    line->setName("折线图n-气含率");

    chart->addSeries(line);
    chart->createDefaultAxes();
    chart->setTitle("在固定流量下转速对气含率的影响");
    chart->axes()[0]->setTitleText("转速");
    chart->axes()[1]->setTitleText("气含率");

    ui->chart_view->setChart(chart);
    ui->chart_view->setRenderHints(QPainter::Antialiasing);
}

ChartWidget::~ChartWidget()
{
    delete chart;
    delete ui;
}
