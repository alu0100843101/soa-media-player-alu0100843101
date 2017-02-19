#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>

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
    void on_actionOpen_triggered();
    void on_actionPlay_triggered();
    void on_actionPause_triggered();
    void on_actionStop_triggered();
    void on_actionMute_triggered();
    void on_actionUnmute_triggered();
    void on_actionRewind_triggered();
    void on_actionForward_triggered();

    void on_volume_changed(int value);

private:
    Ui::MainWindow *ui;

    QMediaPlayer *player_;
    QVideoWidget *videoW_;
    QProgressBar *progBar_;
    QSlider *slider_; //Progress Slider.
    QSlider* volumeSlider_;
};

#endif // MAINWINDOW_H
