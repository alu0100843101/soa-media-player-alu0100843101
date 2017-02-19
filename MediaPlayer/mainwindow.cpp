#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player_ = new QMediaPlayer(this);
    videoW_ = new QVideoWidget(this);
    player_->setVideoOutput(videoW_);
    player_->setVolume(100);

    //Otra forma: setCentralWidget(videoW_);
    this->setCentralWidget(videoW_);

    //Otra forma: volumeSlider_ = new QSlider(Qt::Horizontal, this);
    volumeSlider_ = new QSlider(this);
    volumeSlider_->setOrientation(Qt::Horizontal);
    ui->statusBar->addPermanentWidget(volumeSlider_);
    volumeSlider_->setRange(0, 100);
    volumeSlider_->setSliderPosition(100);

    //Otra forma: slider_ = new QSlider(Qt::Horizontal, this);
    slider_ = new QSlider(this);
    slider_->setOrientation(Qt::Horizontal);
    ui->statusBar->addPermanentWidget(slider_);

    progBar_= new QProgressBar(this);
    ui->statusBar->addPermanentWidget(progBar_);

    connect(volumeSlider_, SIGNAL(sliderMoved(int)), this, SLOT(on_volume_changed(int)));

    connect(player_, &QMediaPlayer::durationChanged, slider_, &QSlider::setMaximum);
    connect(player_, &QMediaPlayer::positionChanged, slider_, &QSlider::setValue);
    connect(slider_, &QSlider::sliderMoved, player_, &QMediaPlayer::setPosition);

    connect(player_, &QMediaPlayer::durationChanged, progBar_, &QProgressBar::setMaximum);
    connect(player_, &QMediaPlayer::positionChanged, progBar_, &QProgressBar::setValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open"));
    if (filename.isEmpty()) {
        return;
    }

    on_actionStop_triggered();

    player_->setMedia(QUrl::fromLocalFile(filename));

    on_actionPlay_triggered();
}

void MainWindow::on_actionPlay_triggered()
{
    player_->setPlaybackRate(1.0);
    player_->play();
    ui->statusBar->showMessage("Playing");
}

void MainWindow::on_actionPause_triggered()
{
    player_->pause();
    ui->statusBar->showMessage("Paused...");
}

void MainWindow::on_actionStop_triggered()
{
    player_->stop();
    ui->statusBar->showMessage("Stopped");
}

void MainWindow::on_volume_changed(int value)
{
    player_->setVolume(value);
}

void MainWindow::on_actionMute_triggered()
{
    player_->setMuted(true);
}

void MainWindow::on_actionUnmute_triggered()
{
    player_->setMuted(false);
}

void MainWindow::on_actionRewind_triggered()
{
    player_->setPlaybackRate(-2.0);

}

void MainWindow::on_actionForward_triggered()
{
    player_->setPlaybackRate(4.0);
}
