#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QList>
#include <QPointF>
#include <QMessageBox>
#include "chartwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // 模式枚举变量
    enum
    {
        test,
        exam
    };

    const int maximum_frequency_ctrl = 250;
    const int minimum_frequency_ctrl = 0;

    const int maximum_pressure_upper = 1000;
    const int minimum_pressure_upper = 0;

    const int maximum_pressure_lower = 1000;
    const int minimum_pressure_lower = 0;

    const QString first_videos = ".\\videos\\0.2\\0.mp4";

    const double eps = 1E-6;

    const QSize pb_size = QSize(100, 100);

    // 按钮状况
    int  button_total_state = 0;
    int  button_mixer_state = 0;
    int  button_press_state = 0;

    // 压力轴情况
    int slider_press_begin = 370;
    int slider_press_end = 120;

    QMediaPlayer* video_play = nullptr;
    QIcon dail_press;

    // 图标
    QIcon button_red_closed;
    QIcon button_red_opened;

    QIcon button_green_closed;
    QIcon button_green_opened;

    QPixmap press_tube;

    // 数据保存
    QList<QPointF> data;


    // 设置videos
    void setPlayingVideo(double n);

    // 根据n获得视频
    QString getSpecialPath(double n);
    QString getNormalPath(double n);

    // 特殊n数量
    QString getValue0_2(double n);
    QString getValue0_4(double n);
    QString getValue0_6(double n);
    QString getValue0_8(double n);
    QString getValue1_0(double n);
    QString getValue1_2(double n);
    QString getValue1_4(double n);
    QString getValue1_6(double n);
    QString getValue1_8(double n);
    QString getValue2_0(double n);

    // 模式变量
    int mode = 0;
    // 分数
    int score = 100;
    int pre = 0;
    QString error = "";

    // 获取下一个值
    int getLowerValue(int c)
    {
        return int(double(c) / 20 + 1) * 20;
    }

    double getn0(double n)
    {
        return (0.1970448 + 2.2540743 * n) * 60;
    }

    double getn1(double n)
    {
        return (6.935153329 + 0.2642072132 * n) * 60;
    }
};
#endif // MAINWINDOW_H
