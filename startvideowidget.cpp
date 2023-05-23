#include "startvideowidget.h"

StartVideoWidget::StartVideoWidget(QWidget *parent)
    : QVideoWidget(parent),
      start_video_source(parent)
{
    setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
    start_video_source.setLoops(-1);
    setFocusPolicy(Qt::StrongFocus);

    start_video_source.setSource(QUrl::fromLocalFile(".\\videos\\start.mp4"));
    start_video_source.setVideoOutput(this);
    start_video_source.play();
}

void StartVideoWidget::keyPressEvent(QKeyEvent *event)
{
    start_video_source.stop();
    emit changeScense();
    return QVideoWidget::keyPressEvent(event);
}
