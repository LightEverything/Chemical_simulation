#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , video_play(new QMediaPlayer(this))
    , press_tube(":\\image\\press.png")
{
    ui->setupUi(this);

    // 图片资源
    button_red_closed.addFile(".\\image\\red_button_closed.png", pb_size);
    button_red_opened.addFile(".\\image\\red_button_opened.png", pb_size);
    button_green_closed.addFile(".\\image\\green_button_closed.png", pb_size);
    button_green_opened.addFile(".\\image\\green_button_opened.png", pb_size);

    // 按钮
    ui->pb_total->setIconSize(pb_size);
    ui->pb_total->setIcon(button_red_closed);

    ui->pb_mixer->setIconSize(pb_size);
    ui->pb_mixer->setIcon(button_green_closed);

    ui->pb_press->setIconSize(pb_size);
    ui->pb_press->setIcon(button_green_closed);

    ui->wg_videos->setAutoFillBackground(true);
    ui->wg_videos->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);

    // 视频播放
    video_play->setVideoOutput(ui->wg_videos);
    video_play->setSource(QUrl::fromLocalFile(".\\videos\\123.mp4"));
    video_play->setLoops(-1);
    video_play->play();

    ui->stackedWidget->setCurrentWidget(ui->page_start);

    // 电机旋钮
    ui->dl_frequency_ctrl->setMinimum(minimum_frequency_ctrl);
    ui->dl_frequency_ctrl->setMaximum(maximum_frequency_ctrl);

    // 小压力阀
    ui->dl_pressure_lower->setMinimum(minimum_pressure_lower);
    ui->dl_pressure_lower->setMaximum(maximum_pressure_lower);
    ui->lb_press_lower->setScaledContents(true);
    ui->lb_move_slider_press_lower->setScaledContents(true);

    // 大压力阀
    ui->dl_pressure_upper->setMinimum(minimum_pressure_upper);
    ui->dl_pressure_upper->setMaximum(maximum_pressure_upper);
    ui->lb_press_upper->setScaledContents(true);

    // 链接
    connect(ui->dl_frequency_ctrl, &QAbstractSlider::valueChanged, this, [&](int val)
    {
        QString str = QString::fromStdString(std::to_string(val));
        QString str_speed = QString::fromStdString(std::to_string(int(double(val) * 2.15)));
//        ui->lb_frequency_show->setText(str);
//        ui->lb_speed_show->setText(str_speed);
    });

    connect(ui->dl_pressure_lower, &QAbstractSlider::valueChanged, this, [&](int val)
    {
//        ui->press_tube_lower->setValue(val);
        int now_pos_y = (double(val) / maximum_pressure_lower) * (slider_press_end - slider_press_begin) + slider_press_begin;
        qDebug() << now_pos_y;
        int now_pos_x =  ui->lb_move_slider_press_lower->x();
        int now_with =  ui->lb_move_slider_press_lower->width();
        int now_heigh = ui->lb_move_slider_press_lower->height();

        ui->lb_move_slider_press_lower->setGeometry(now_pos_x, now_pos_y, now_with, now_heigh);
    });

    connect(ui->dl_pressure_upper, &QAbstractSlider::valueChanged, this, [&](int val)
    {
//        ui->press_tube_upper->setValue(val);
    });

    connect(ui->pb_start_button, &QPushButton::clicked, this, [&]()
    {
        video_play->setSource(QUrl::fromLocalFile(".\\videos\\1234.mp4"));
        video_play->play();
    });

    connect(ui->wg_start_video, &StartVideoWidget::changeScense, this, [&](){
        ui->stackedWidget->setCurrentWidget(ui->page_achieve);
    });

    connect(ui->pb_total, &QPushButton::clicked, this, [&](){
        if (button_total_state)
            ui->pb_total->setIcon(button_red_closed);
        else
            ui->pb_total->setIcon(button_red_opened);

        button_total_state ^= 1;
    });

    connect(ui->pb_mixer, &QPushButton::clicked, this, [&](){
        if (button_mixer_state)
           ui->pb_mixer->setIcon(button_green_closed);
        else
            ui->pb_mixer->setIcon(button_green_opened);

        button_mixer_state ^= 1;
    });

    connect(ui->pb_press, &QPushButton::clicked, this, [&](){
        if (button_press_state)
           ui->pb_press->setIcon(button_green_closed);
        else
            ui->pb_press->setIcon(button_green_opened);

        button_press_state ^= 1;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
