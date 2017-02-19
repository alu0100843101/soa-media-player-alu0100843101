#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QMediaPlayer* player_ = new QMediaPlayer;
    QVideoWidget* videoW_ = new QVideoWidget;

    player_->setVideoOutput(videoW_);
    player_->setMedia(QUrl::fromLocalFile("/home/andperqui/Documentos/SOA/media-player/VideoPlayer/video.mov"));

    videoW_->setGeometry(500,500,300,400);


    videoW_->show();

    player_->play();
}

Dialog::~Dialog()
{
    delete ui;
}
