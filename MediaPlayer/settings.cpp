#include "settings.h"
#include "ui_settings.h"

Settings::Settings(const QList<QByteArray> &devices, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    //QList<QByteArray> devices = QCamera::availableDevices();
    qDebug() << "Capturando de... " << QCamera::deviceDescription(devices[0]);
    qDebug()<< "Numero de dispositivos...." << devices.size();

    int i=0;
    do {
        ui->comboBox->addItem(QCamera::deviceDescription(devices[i]));
        i++;
    }while(i<devices.size());

    ui->comboBox->setCurrentIndex(settings.value("index").toInt());
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_btnCancel_clicked()
{
    close();
}

void Settings::on_btnOk_clicked()
{
    index_ = ui->comboBox->currentIndex();

    settings.value("index", index_);
    emit cameraSignal(index_);
    close();
}
