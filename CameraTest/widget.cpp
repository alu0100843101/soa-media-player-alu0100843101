#include "widget.h"
#include "ui_widget.h"
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QDateTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    mCamera = new QCamera(this);
    mCameraViewfinder = new QCameraViewfinder(this);
    mCameraImageCapture = new QCameraImageCapture(mCamera, this);
    mLayout = new QVBoxLayout;
    mOpcionesMenu = new QMenu("Opciones", this);
    mEncenderAction = new QAction("Encender", this);
    mApagarAction = new QAction("Apagar", this);
    mCapturarAction = new QAction("Capturar", this);

    mOpcionesMenu->addActions({ mEncenderAction, mApagarAction, mCapturarAction });
    ui->opcionesPushButton->setMenu(mOpcionesMenu);

    mCamera->setViewfinder(mCameraViewfinder);
    mCameraViewfinder->show();

    mLayout->addWidget(mCameraViewfinder);

    mLayout->setMargin(0);
    ui->scrollArea->setLayout(mLayout);

    connect(mEncenderAction, &QAction::triggered, [&](){
        mCamera->start();
    });
    connect(mApagarAction, &QAction::triggered, [&](){
        mCamera->stop();
    });
    connect(mCapturarAction, &QAction::triggered, [&](){
        QString filename = QFileDialog::getSaveFileName(this, tr("Capturar"), "/", tr("image (*.jpg *.jpeg)"));
        //QString filename = "Image_" + QDateTime::currentDateTime().toString("dd.MM.yy-h-m-s") + ".jpg";

        if(filename.isEmpty())
            return;

        mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
        QImageEncoderSettings imageEncoderSettings;
        imageEncoderSettings.setCodec("image/jpeg");
        //imageEncoderSettings.setResolution(640, 480);
        mCameraImageCapture->setEncodingSettings(imageEncoderSettings);

        //mCamera->setCaptureMode(QCamera::CaptureStillImage);
        mCamera->setCaptureMode(QCamera::CaptureViewfinder);
        mCamera->start();
        mCamera->searchAndLock();
        mCameraImageCapture->capture(filename);
        mCamera->unlock();
    });
}

Widget::~Widget()
{
    delete ui;
}
