#include "dialog.h"
#include <QApplication>

#include <QMediaPlayer>
#include <QVideoWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Dialog w;
    QMediaPlayer* player_ = new QMediaPlayer;
    QVideoWidget* videoW_ = new QVideoWidget;

    player_->setVideoOutput(videoW_);
    player_->setMedia(QUrl::fromLocalFile("/home/andperqui/Documentos/SOA/media-player/VideoPlayer/video.mov"));

    videoW_->setGeometry(100,100,300,400);

    //w.show();
    videoW_->show();

    player_->play();

    return a.exec();
}
