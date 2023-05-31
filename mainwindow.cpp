#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , video_play(new QMediaPlayer(this))
    , press_tube(":\\image\\press.png")
{
    ui->setupUi(this);
    setFixedSize(this->geometry().size());

    // 设置背景
    ui->page_start->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(".\\image\\start.jpg").scaled(    // 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio)));    // 使用平滑的缩放方式
    ui->page_start->setPalette(palette);


    ui->page_introduce_text->setAutoFillBackground(true);
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(".\\image\\background.jpg").scaled(    // 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio)));    // 使用平滑的缩放方式
    ui->page_introduce_text->setPalette(palette);

    ui->page_principle->setAutoFillBackground(true);
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(".\\image\\background.jpg").scaled(    // 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio)));    // 使用平滑的缩放方式
    ui->page_principle->setPalette(palette);

    ui->page_answer->setAutoFillBackground(true);
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(".\\image\\background.jpg").scaled(    // 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio)));    // 使用平滑的缩放方式
    ui->page_answer->setPalette(palette);

    ui->page_question->setAutoFillBackground(true);
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(".\\image\\background.jpg").scaled(    // 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio)));    // 使用平滑的缩放方式
    ui->page_question->setPalette(palette);

    ui->page_warning->setAutoFillBackground(true);
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(".\\image\\background.jpg").scaled(    // 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio)));    // 使用平滑的缩放方式
    ui->page_warning->setPalette(palette);

    ui->page_signup->setAutoFillBackground(true);
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(".\\image\\background.jpg").scaled(    // 缩放背景图.
                this->size(),
                Qt::IgnoreAspectRatio)));    // 使用平滑的缩放方式
    ui->page_signup->setPalette(palette);

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

    // 电机仪表盘

    // 视频播放
    video_play->setVideoOutput(ui->wg_videos);
    video_play->setSource(QUrl::fromLocalFile(first_videos));
    video_play->setLoops(-1);
    video_play->play();

    ui->stackedWidget->setCurrentWidget(ui->page_start);

    // 电机旋钮
    ui->dl_frequency_ctrl->setMinimum(minimum_frequency_ctrl);
    ui->dl_frequency_ctrl->setMaximum(maximum_frequency_ctrl);

    // 小压力阀
    ui->dl_pressure_lower->setMinimum(minimum_pressure_lower);
    ui->dl_pressure_lower->setMaximum(maximum_pressure_lower);

    // 大压力阀
    ui->dl_pressure_upper->setMinimum(minimum_pressure_upper);
    ui->dl_pressure_upper->setMaximum(maximum_pressure_upper);

    // 链接

    connect(ui->pb_start, &QPushButton::clicked, this, [&]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_signup);
    });

    connect(ui->pb_to_qusetion, &QPushButton::clicked, this, [&]()
    {
        if (button_total_state == 1 || button_mixer_state == 1 || button_press_state == 1)
        {
            score -= 5;
            error += "忘记关闭电源\n";
        }
        ui->stackedWidget->setCurrentWidget(ui->page_question);
    });

    connect(ui->pb_answer, &QPushButton::clicked, this, [&]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_answer);
        if (mode == exam && pre == 0)
        {
            pre = 1;
            ui->lb_show->setText("最终得分：");
            ui->lb_score->setText(QString::number(score));
            ui->lb_error->setText(error);
        }
    });

    connect(ui->pb_pre, &QPushButton::clicked, this, [&]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_question);
    });

    connect(ui->pb_quit, &QPushButton::clicked, this, [&]()
    {
        this->close();
    });

    connect(ui->pb_principle, &QPushButton::clicked, this, [&](){

        ui->stackedWidget->setCurrentWidget(ui->page_principle);
    });

    connect(ui->pb_view_videos, &QPushButton::clicked, this, [&](){

        ui->stackedWidget->setCurrentWidget(ui->page_introduce_videos);
    });

    connect(ui->pb_return, &QPushButton::clicked, this, [&](){
        ui->stackedWidget->setCurrentWidget(ui->page_introduce_text);
    });

    connect(ui->pb_warning, &QPushButton::clicked, this, [&](){
        ui->stackedWidget->setCurrentWidget(ui->page_warning);
    });

    connect(ui->pb_signup_test, &QPushButton::clicked, this, [&](){
        mode = test;
        ui->stackedWidget->setCurrentWidget(ui->page_introduce_text);
    });

    connect(ui->pb_signup_exam, &QPushButton::clicked, this, [&](){
        mode = exam;
        ui->stackedWidget->setCurrentWidget(ui->page_introduce_text);
    });

    connect(ui->pb_return_2, &QPushButton::clicked, this, [&](){
        ui->stackedWidget->setCurrentWidget(ui->page_introduce_text);
    });

    connect(ui->pb_start_test, &QPushButton::clicked, this, [&](){
        ui->stackedWidget->setCurrentWidget(ui->page_achieve);
    });

    connect(ui->dl_frequency_ctrl, &QAbstractSlider::valueChanged, this, [&](int val)
    {
        if (button_mixer_state == 0)
            return ;
        QString str_speed = QString::fromStdString(std::to_string(int(double(val) * 2.8)));
        ui->lcd_frequency->display(str_speed);
    });

    connect(ui->dl_pressure_lower, &QAbstractSlider::valueChanged, this, [&](int val)
    {
        if (button_press_state == 0)
        {
            return ;
        }
        int now_pos_y = (double(val) / maximum_pressure_lower) * (slider_press_end - slider_press_begin) + slider_press_begin;
        int now_pos_x =  ui->lb_move_slider_press_lower->x();
        int now_with =  ui->lb_move_slider_press_lower->width();
        int now_heigh = ui->lb_move_slider_press_lower->height();

        ui->lb_move_slider_press_lower->setGeometry(now_pos_x, now_pos_y, now_with, now_heigh);
        ui->lb_press_lower_show->setText(QString::number(double(val) / maximum_pressure_lower * 1.0, 'f', 1));
    });

    connect(ui->dl_pressure_upper, &QAbstractSlider::valueChanged, this, [&](int val)
    {
        if (button_press_state == 0)
        {
            return ;
        }
        int now_pos_y = (double(val) / maximum_pressure_upper) * (slider_press_end - slider_press_begin) + slider_press_begin;
        int now_pos_x =  ui->lb_move_slider_press_upper->x();
        int now_with =  ui->lb_move_slider_press_upper->width();
        int now_heigh = ui->lb_move_slider_press_upper->height();

        ui->lb_move_slider_press_upper->setGeometry(now_pos_x, now_pos_y, now_with, now_heigh);
        ui->lb_press_upper_show->setText(QString::number(double(val) / maximum_pressure_lower * 3.2, 'f', 1));
    });

    connect(ui->pb_start_button, &QPushButton::clicked, this, [&]()
    {
        double n = double(ui->dl_pressure_upper->value()) / maximum_pressure_upper * 3.2 + double(ui->dl_pressure_lower->value()) / maximum_pressure_lower * 1.0;
        int n0 = getn0(n) + 1;
        int n1 = getn1(n) + 1;

        QString strn0 = "n0:" + QString::number(n0);
        QString strn1 = "n':" + QString::number(n1);

        ui->lb_n0->setText(strn0);
        ui->lb_n1->setText(strn1);

        if (button_press_state == 0)
        {
            n = 0;
        }

        // 如果大于4.0报错
        if (n > 4.0)
        {
            error += "流量范围错误，扣五分\n";
            score -= 5;
            QMessageBox::warning(this, "范围错误", "流量设置错误， 请重新调整");
            return ;
        }

        ui->pb_start_button->setEnabled(false);
        ui->pb_record->setEnabled(true);
        ui->pb_stop->setEnabled(true);
        ui->pb_draw->setEnabled(false);
        ui->dl_pressure_lower->setEnabled(false);
        ui->dl_pressure_upper->setEnabled(false);
        ui->pb_getData->setEnabled(true);

        data.clear();

        // 设置视频
        int c = ui->lcd_frequency->value();
        if (c > 460)
        {
            error += "转速过快，容易导致容器破损，扣五分\n";
            score -= 5;
            QMessageBox::warning(this, "转速过快", "转速过快容易导致容器破损");
            return ;
        }

        setPlayingVideo(n);
    });

    connect(ui->wg_start_video, &StartVideoWidget::changeScense, this, [&](){
        ui->stackedWidget->setCurrentWidget(ui->page_introduce_text);
    });

    connect(ui->pb_total, &QPushButton::clicked, this, [&](){
        if (button_total_state)
        {
            ui->pb_total->setIcon(button_red_closed);
           ui->pb_mixer->setIcon(button_green_closed);
           ui->pb_press->setIcon(button_green_closed);

           if (button_mixer_state == 1 || button_press_state == 1)
           {
               score -= 5;
               error += "开关关闭顺序错误, 扣五分\n";
           }

            button_mixer_state = 0;
            button_press_state = 0;

            ui->lcd_frequency->display(0);
            int now_pos_x = ui->lb_move_slider_press_upper->x(), now_pos_y = slider_press_begin;
            int now_with =  ui->lb_move_slider_press_upper->width();
            int now_heigh = ui->lb_move_slider_press_upper->height();

            ui->lb_move_slider_press_upper->setGeometry(now_pos_x, now_pos_y, now_with, now_heigh);

            now_pos_x = ui->lb_move_slider_press_lower->x(), now_pos_y = slider_press_begin;
            now_with =  ui->lb_move_slider_press_lower->width();
            now_heigh = ui->lb_move_slider_press_lower->height();

            ui->lb_move_slider_press_lower->setGeometry(now_pos_x, now_pos_y, now_with, now_heigh);
        }
        else
        {
            ui->pb_total->setIcon(button_red_opened);
        }

        button_total_state ^= 1;
    });

    connect(ui->pb_mixer, &QPushButton::clicked, this, [&](){
        if (button_mixer_state)
        {
           ui->pb_mixer->setIcon(button_green_closed);
            button_mixer_state ^= 1;
        }
        else
        {
            if (button_total_state == 1)
            {
                ui->pb_mixer->setIcon(button_green_opened);
                button_mixer_state ^= 1;
            }
        }
    });

    connect(ui->pb_press, &QPushButton::clicked, this, [&](){
        if (button_press_state)
        {
           ui->pb_press->setIcon(button_green_closed);
           button_press_state ^= 1;
        }
        else
        {
            if (button_total_state == 1)
            {
                ui->pb_press->setIcon(button_green_opened);
                button_press_state ^= 1;
            }
        }

    });

    connect(ui->pb_stop, &QPushButton::clicked, this, [&](){
        ui->pb_start_button->setEnabled(true);
        ui->pb_stop->setEnabled(false);
        ui->pb_record->setEnabled(false);
        ui->pb_draw->setEnabled(true);
        ui->dl_pressure_lower->setEnabled(true);
        ui->dl_pressure_upper->setEnabled(true);
        ui->pb_getData->setEnabled(false);

        ui->lb_n0->setText("");
        ui->lb_n1->setText("");
    });

    connect(ui->pb_draw, &QPushButton::clicked, this, [&](){
        ChartWidget* cw = new ChartWidget(nullptr, &this->data);
        cw->show();
    });

    connect(ui->pb_record, &QPushButton::clicked, this, [&](){
        double c = ui->lcd_frequency->value();
        double hf = ui->le_hf->text().toDouble();
        ui->le_hf->clear();
        data.append({c, (hf - 25) / hf});
    });

    connect(ui->pb_getData, &QPushButton::clicked, this, [&](){
        double n = double(ui->dl_pressure_upper->value()) / maximum_pressure_upper * 3.2 + double(ui->dl_pressure_lower->value()) / maximum_pressure_lower * 1.0;
        int c = ui->lcd_frequency->value();
        if (c > 460)
        {
            error += "转速过快，容易导致容器破损，扣五分\n";
            score -= 5;
            QMessageBox::warning(this, "转速过快", "转速过快容易导致容器破损");
            return ;
        }

        setPlayingVideo(n);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPlayingVideo(double n)
{
    int tmp = n / 0.2;
    n = (tmp + 1) * 0.2;

    QString path = ".\\videos\\";

    if (n <= 2.0)
    {
        path += getSpecialPath(n);
    }
    else
    {
        path += getNormalPath(n);
    }

//    video_play->stop();
    video_play->setSource(QUrl::fromLocalFile(path));
    video_play->play();
}

QString MainWindow::getNormalPath(double n)
{
    int c = ui->lcd_frequency->value();
    QString str = QString::number(n, 'f', 1) + "\\";

    if (c < 100)
    {
        str += "0";
    }
    else
    {
        int tmp = getLowerValue(c);
        str += QString::number(tmp);
    }
    str += ".mp4";
    return str;
}

QString MainWindow::getSpecialPath(double n)
{
    if (n <= 0.2 + eps)
        return getValue0_2(n);
    else if (n <= 0.4 + eps)
        return getValue0_4(n);
    else if (n <= 0.6 + eps)
        return getValue0_6(n);
    else if (n <= 0.8 + eps)
        return getValue0_8(n);
    else if (n <= 1.0 + eps)
        return getValue1_0(n);
    else if (n <= 1.2 + eps)
        return getValue1_2(n);
    else if (n <= 1.4 + eps)
        return getValue1_4(n);
    else if (n <= 1.6 + eps)
        return getValue1_6(n);
    else if (n <= 1.8 + eps)
        return getValue1_8(n);
    else
        return getValue2_0(n);
}


QString MainWindow::getValue0_2(double n)
{
    int c = ui->lcd_frequency->value();
    QString path = QString::number(n, 'f', 1) + "\\";

    if (c < 100)
    {
        path += "0";
    }
    else if (c < 120)
    {
        path += "120";
    }
    else if (c < 150)
    {
        path += "150";
    }
    else if (c < 180)
    {
        path += "180";
    }
    else if (c < 210)
    {
        path += "210";
    }
    else if (c < 270)
    {
        for (int i = 230; i < 270; i += 20)
        {
            if (i <= c && i + 20 > c)
            {
                path += QString::number(i);
                break;
            }
        }
    }
    else if (c < 300)
    {
        path += "300";
    }
    else if (c < 330)
    {
        path += "330";
    }
    else if (c < 360)
    {
        path += "360";
    }
    else if (c < 400)
    {
        int tmp = getLowerValue(c);
        path += QString::number(tmp);
    }
    else if (430)
    {
        path += "430";
    }
    else
    {
        path += "460";
    }

    path += ".mp4";
    return path;
}

QString MainWindow::getValue0_4(double n)
{
    int c = ui->lcd_frequency->value();
    QString path = QString::number(n, 'f', 1) + "\\";

    if (c < 100)
    {
        path += "0";
    }
    else if (c < 130)
    {
        path += "130";
    }
    else if (c < 150)
    {
        path += "150";
    }
    else if (c < 170)
    {
        path += "170";
    }
    else if (c < 190)
    {
        path += "190";
    }
    else if (c < 210)
    {
        path += "210";
    }
    else if (c < 220)
    {

        path += "220";
    }
    else if (c < 300)
    {
        int tmp = getLowerValue(c);
        path += QString::number(tmp);
    }
    else if (c < 330)
    {
        path += "330";
    }
    else if (c < 350)
    {
        path += "350";
    }
    else if (c < 380)
    {
        path += "380";
    }
    else
    {
        int tmp = getLowerValue(c);
        path += QString::number(tmp);
    }
    path += ".mp4";
    return path;
}

QString MainWindow::getValue0_6(double n)
{

    int c = ui->lcd_frequency->value();
    QString path = QString::number(n, 'f', 1) + "\\";

    if (c < 100)
    {
        path += "0";
    }
    else if (c < 240)
    {
        int tmp = getLowerValue(c);
        path += QString::number(tmp);
    }
    else if (c < 270)
    {
        path += "270";
    }
    else if (c < 290)
    {
        path += "290";
    }
    else if (c < 310)
    {
        path += "310";
    }
    else if (c < 330)
    {
        path += "330";
    }
    else if (c < 350)
    {
        path += "350";
    }
    else if (c < 370)
    {
        path += "370";
    }
    else if (c < 390)
    {
        path += "390";
    }
    else if (c < 410)
    {
        path += "410";
    }
    else if (c < 430)
    {
        path += "430";
    }
    else
    {
        path += "460";
    }
    path += ".mp4";
    return path;
}

QString MainWindow::getValue0_8(double n)
{

    int c = ui->lcd_frequency->value();
    QString path = QString::number(n, 'f', 1) + "\\";

    if (c < 100)
    {
        path += "0";
    }
    else if (c < 320)
    {
        int tmp = getLowerValue(c);
        path += QString::number(tmp);

    }
    else if (c < 350)
    {
        path += "350";
    }
    else if (c < 370)
    {
        path += "370";
    }
    else if (c < 390)
    {
        path += "390";
    }
    else if (c < 410)
    {
        path += "410";
    }
    else if (c < 430)
    {
        path += "430";
    }
    else
    {
        path += "460";
    }
    path += ".mp4";
    return path;
}

QString MainWindow::getValue1_0(double n)
{

    int c = ui->lcd_frequency->value();
    QString path = QString::number(n, 'f', 1) + "\\";

    if (c < 100)
    {
        path += "0";
    }
    else if (c < 160)
    {
        int tmp = getLowerValue(c);
        path += QString::number(tmp);
    }
    else if (c < 430)
    {
        for (int i = 160; i < 430; i += 20)
        {
            if (i <= c && i + 20 > c)
            {
                path += QString::number(i);
                break;
            }
        }
    }
    else
    {
        path += "460";
    }
    path += ".mp4";
    return path;
}


QString MainWindow::getValue1_2(double n)
{

    int c = ui->lcd_frequency->value();
    QString path = QString::number(n, 'f', 1) + "\\";

    if (c < 100)
    {
        path += "0";
    }
    else if (c < 120)
    {
        path += "120";

    }
    else if (c < 150)
    {
        path += "150";
    }
    else if (c < 370)
    {
        for (int i = 150; i < 370; i += 20)
        {
            if (i <= c && i + 20 > c)
            {
                path += QString::number(i);
                break;
            }
        }
    }
    else if (c < 400)
    {
        path += "400";
    }
    else if (c < 420)
    {
        path += "420";
    }
    else
    {
        path += "460";
    }
    path += ".mp4";
    return path;
}

QString MainWindow::getValue1_4(double n)
{

    int c = ui->lcd_frequency->value();
    QString path = QString::number(n, 'f', 1) + "\\";

    if (c < 100)
    {
        path += "0";
    }
    else if (c < 160)
    {
        int tmp = getLowerValue(c);
        path += QString::number(tmp);
    }
    else if (c < 190)
    {
        path += "190";
    }
    else if (c < 310)
    {

        int tmp = getLowerValue(c);
        path += QString::number(tmp);
    }
    else if (c < 340)
    {
        path += "340";
    }
    else
    {
        int tmp = getLowerValue(c);
        path += QString::number(tmp);
    }
    path += ".mp4";
    return path;
}

QString MainWindow::getValue1_6(double n)
{
    int c = ui->lcd_frequency->value();
    QString path = QString::number(n, 'f', 1) + "\\";

    if (c < 100)
    {
        path += "0";
    }
    else if (c < 360)
    {
        int tmp = getLowerValue(c);
        path += QString::number(tmp);
    }
    else if (c < 390)
    {
        path += "390";
    }
    else
    {
        for (int i = 390; i < 451; i += 20)
        {
            if (i <= c && i + 20 > c)
            {
                path += QString::number(i);
                break;
            }
        }
    }
    path += ".mp4";
    return path;
}

QString MainWindow::getValue1_8(double n)
{
    int c = ui->lcd_frequency->value();
    QString path = QString::number(n, 'f', 1) + "\\";

    if (c < 100)
    {
        path += "0";
    }
    else if (c < 140)
    {
        int tmp = getLowerValue(c);
        path += QString::number(tmp);
    }
    else if (c < 170)
    {
        path += "170";
    }
    else if (c < 310)
    {
        for (int i = 170; i < 310; i += 20)
        {
            if (i <= c && i + 20 > c)
            {
                path += QString::number(i);
                break;
            }
        }
    }
    else if (c < 340)
    {
        path += "340";
    }
    else if (c < 360)
    {
        path += "360";
    }
    else if (c < 390)
    {
        path += "390";
    }
    else if (c < 420)
    {
        path += "420";
    }
    else
    {
        int tmp = getLowerValue(c);
        path += QString::number(tmp);
    }
    path += ".mp4";
    return path;
}

QString MainWindow::getValue2_0(double n)
{
    int c = ui->lcd_frequency->value();
    QString path = QString::number(n, 'f', 1) + "\\";

    if (c < 100)
    {
        path += "0";
    }
    else if (c < 170)
    {
        int tmp = getLowerValue(c);
        path += QString::number(tmp);
    }
    else if (c < 200)
    {
        path += "200";
    }
    else if (c < 320)
    {
        int tmp = getLowerValue(c);
        path += QString::number(tmp);

    }
    else if (c < 350)
    {
        path += "350";

    }
    else if (c < 380)
    {
        path += "380";
    }
    else if (c < 420)
    {
        path += "420";
    }
    else
    {
        path += "460";
    }
    path += ".mp4";
    return path;
}
