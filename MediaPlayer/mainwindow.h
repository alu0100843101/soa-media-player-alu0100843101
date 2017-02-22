#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//MediaPlayer:
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
//QCamera:
//#include <QCameraViewfinder>
#include <QCamera>
//Settings/Devices:
#include <QSettings>
#include <QPixmap>
#include <QDateTime>
#include <QPainter>
//Owner:
#include "videosurface.h"
#include "helpdialog.h"
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void on_actionOpen_triggered();
    void on_actionPlay_triggered();
    void on_actionPause_triggered();
    void on_actionStop_triggered();
    void on_actionMute_triggered();
    void on_actionUnmute_triggered();
    void on_actionRewind_triggered();
    void on_actionForward_triggered();
    void on_actionHelp_triggered();
    void on_actionWebcam_triggered();
    void on_actionsettings_triggered();

    void on_volume_changed(int value);
    void signalUpdate(int);
    void signalImage(const QImage&);

private:
    Ui::MainWindow *ui;

    QMediaPlayer *player_;
    QVideoWidget *videoW_;
    QProgressBar *progBar_;
    QSlider *slider_; //Progress Slider.
    QSlider* volumeSlider_;

    QSettings settings_;
    HelpDialog* help_;
    Settings* cameraSettings_;
    QCamera* camera_;
    //QCameraViewfinder* cameraViewfinder_;
    VideoSurface* videoSurface_;
    QList<QByteArray> devices_;
    int index_;
};

#endif // MAINWINDOW_H
