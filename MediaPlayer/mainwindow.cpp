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

    //** Webcam
    index_ = settings_.value("index_").toInt();

    help_ = NULL;
    camera_ = NULL;
    videoSurface_ = NULL;
    cameraSettings_ = NULL;
    devices_ = QCamera::availableDevices();
    //**
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player_;

    delete help_;
    delete camera_;
    delete cameraSettings_;
    delete videoSurface_;
}

void MainWindow::on_actionExit_triggered()
{
    //qApp apunta al objeto creado en el fichero main.cpp: "QApplication a(argc, argv);"
    qApp->quit();
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
    if(camera_==NULL)
    {
        player_->setPlaybackRate(1.0);
        player_->play();
        ui->statusBar->showMessage("Playing");
    } else {
        camera_->start();

        ui->statusBar->showMessage("Webcam");
        connect(videoSurface_, SIGNAL(imageSignal(QImage)), this, SLOT(signalImage(QImage)));
        connect(ui->actionPlay, SIGNAL(triggered()), camera_, SLOT(start()));
        //Stop y Pause pararán la captura de cam.
        connect(ui->actionPause, SIGNAL(triggered()), camera_, SLOT(stop()));
        connect(ui->actionStop, SIGNAL(triggered()), camera_, SLOT(stop()));

        /***
        camera_ = new QCamera(devices_[index_]);
        cameraViewfinder_ = new QCameraViewfinder();
        camera_->setViewfinder(cameraViewfinder_);
        cameraViewfinder_->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
        setCentralWidget(cameraViewfinder_);
        camera->setCaptureMode(QCamera::CaptureViewfinder);
        camera_->start();
        ***/
    }

}

void MainWindow::on_actionPause_triggered()
{
    if(player_!=NULL)
    {
        player_->pause();
        ui->statusBar->showMessage("Paused...");
    } else if(camera_!=NULL){
        camera_->stop();
        ui->statusBar->showMessage("Webcam");
    }
}

void MainWindow::on_actionStop_triggered()
{
    if(player_!=NULL)
    {
        player_->stop();
        ui->statusBar->showMessage("Stopped");
    } else if(camera_!=NULL){
        camera_->stop();
        ui->statusBar->showMessage("Webcam");
    }
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

void MainWindow::on_actionHelp_triggered()
{
    help_ = new HelpDialog();
    help_->help();
    help_->exec();
}

void MainWindow::on_actionWebcam_triggered()
{
    if(player_!=NULL)
    {
        delete player_;
        player_ = NULL;
    }

    on_actionPlay_triggered();
}

void MainWindow::signalImage(const QImage &image)
{
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    QPixmap pixmap;
    pixmap=pixmap.fromImage(image);
    QPainter paint(&pixmap);
    paint.setPen(Qt::green);

    paint.drawText(0, 0, pixmap.width(), pixmap.height(), Qt::AlignRight |Qt::AlignBottom, timeString, 0);
    ui->label->setPixmap(pixmap);
}

void MainWindow::on_actionsettings_triggered()
{
    cameraSettings_ = new Settings(devices_);
    cameraSettings_->show();
    connect(cameraSettings_, SIGNAL(cameraSignal(int)), this, SLOT(signalUpdate(int)));
}

void MainWindow::signalUpdate(int ind)
{
    index_ = ind;
    if(camera_!=NULL)
    {
        camera_->stop();
        delete camera_;
    }

    on_actionWebcam_triggered();
}
