#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QVideoWidget>

namespace Ui {
class Dialog;
}

class QMediaPlayer;
class QVideoWidget;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;

    QMediaPlayer* player_;
    QVideoWidget* videoW_;
};

#endif // DIALOG_H
