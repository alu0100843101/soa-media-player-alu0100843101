#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

/***********************************************************************************************
 * This part is a VideoWidgetSurface Class Implementation
 * All information of this class in - http://doc.qt.io/qt-5/qabstractvideosurface.html -
 * An example in - https://doc.qt.io/archives/4.6/multimedia-videowidget.html -
 *
 * Trademarks: https://doc.qt.io/archives/4.6/trademarks.html
 * **** Copyright © 2010 Nokia Corporation and/or its subsidiary(-ies) ****
***********************************************************************************************/

#include <QList>
#include <QDebug>
#include <QAbstractVideoSurface>

class VideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit VideoSurface(QObject *parent = 0);
    ~VideoSurface();
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType =
                                                            QAbstractVideoBuffer::NoHandle) const
    {
        //Metodo para devolver los tipos de formatos de video soportados.
        QList<QVideoFrame::PixelFormat> formats;
               formats << QVideoFrame::Format_ARGB32;
               formats << QVideoFrame::Format_ARGB32_Premultiplied;
               formats << QVideoFrame::Format_RGB32;
               formats << QVideoFrame::Format_RGB24;
               formats << QVideoFrame::Format_RGB565;
               formats << QVideoFrame::Format_RGB555;
               return formats;
    }

    //A través de este método nos darán el frame para que lo mostremos.
    bool present(const QVideoFrame &frame);

signals:
  void imageSignal(const QImage&);
};

#endif // VIDEOSURFACE_H
