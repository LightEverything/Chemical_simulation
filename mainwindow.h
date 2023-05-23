#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaMetaData>

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

    const int maximum_frequency_ctrl = 60;
    const int minimum_frequency_ctrl = 0;

    const int maximum_pressure_upper = 18;
    const int minimum_pressure_upper = 0;

    const int maximum_pressure_lower = 4;
    const int minimum_pressure_lower = 0;

    const QSize pb_size = QSize(100, 100);

    // 按钮状况
    int  button_total_state = 0;
    int  button_mixer_state = 0;
    int  button_press_state = 0;

    // 压力轴情况
    int slider_press_begin = 310;
    int slider_press_end = 110;
    int now_slider_press_lower = 110;
    int now_slider_press_upper = 110;

//    QVideoWidget* video_display = nullptr;
    QMediaPlayer* video_play = nullptr;
    QIcon dail_press;

    // 图标
    QIcon button_red_closed;
    QIcon button_red_opened;

    QIcon button_green_closed;
    QIcon button_green_opened;

    QPixmap press_tube;
};
#endif // MAINWINDOW_H
