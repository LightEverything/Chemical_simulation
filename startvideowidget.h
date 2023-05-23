#ifndef STARTVIDEOWIDGET_H
#define STARTVIDEOWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QKeyEvent>

class StartVideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit StartVideoWidget(QWidget *parent = nullptr);

private:
    QMediaPlayer start_video_source;

protected:
    virtual void keyPressEvent(QKeyEvent *event);

signals:
    void changeScense();
};

#endif // STARTVIDEOWIDGET_H
