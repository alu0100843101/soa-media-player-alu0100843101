#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QCamera>
#include <QSettings>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    //Añadir lista de dispositivos.
    explicit Settings(const QList<QByteArray> &devices, QWidget *parent = 0);
    ~Settings();

signals:
    void cameraSignal(int);

private slots:
    void on_btnCancel_clicked();
    void on_btnOk_clicked();

private:
    Ui::Settings *ui;
    QSettings settings;
    int index_;
};

#endif // SETTINGS_H
