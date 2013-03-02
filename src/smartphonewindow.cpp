#include "smartphonewindow.h"


SmartphoneWindow::SmartphoneWindow()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    mDeviceList
            << Device(Android320, ":/android_320_480", QPoint(30,97), QSize(400,715), QSize(320,480), 1.0)
            ;

    mWebWidget = new WebWidget(this);
    changeDevice(Android320);
}

void SmartphoneWindow::changeDevice(DevicesResolution device)
{
    foreach(Device dev, mDeviceList) {
        if (dev.device == device) {
            mPixmap.load(dev.image);
            setFixedSize(dev.winSize);
            mWebWidget->move(dev.winPos);
            mWebWidget->setFixedSize(dev.webSize);
            return;
        }
    }
    qDebug() << "Device " << device << " not found";
}

void SmartphoneWindow::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.drawPixmap(0,0,mPixmap);
}
