#include "videosurface.h"

/***********************************************************************************************
 * This part is a VideoWidgetSurface Class Implementation
 * All information of this class in - http://doc.qt.io/qt-5/qabstractvideosurface.html -
 * An example in - https://doc.qt.io/archives/4.6/multimedia-videowidget.html -
 *
 * Trademarks: https://doc.qt.io/archives/4.6/trademarks.html
 * **** Copyright © 2010 Nokia Corporation and/or its subsidiary(-ies) ****
***********************************************************************************************/

VideoSurface::VideoSurface(QObject *parent) :
    QAbstractVideoSurface(parent)
{}

VideoSurface::~VideoSurface()
{}

bool VideoSurface:: present(const QVideoFrame &frame)
{
   QVideoFrame frame2(frame);

   frame2.map(QAbstractVideoBuffer::ReadOnly);

   QImage frameAsImage = QImage(frame2.bits(), frame2.width(),frame2.height(), frame2.bytesPerLine(),
                                  QVideoFrame::imageFormatFromPixelFormat(frame2.pixelFormat()));

   frameAsImage.copy();
   emit imageSignal(frameAsImage);

   frame2.unmap();

 return true;
}
