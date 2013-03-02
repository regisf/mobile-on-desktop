#ifndef SMARTPHONEWINDOW_H
#define SMARTPHONEWINDOW_H

#include "webwidget.h"
#include <QtGui>

/* TODO:
 *     Blackberry devices,
 *     Firefox Devices (Including Gecko Engine ????? - I think this will be painful)
 */

// This is for the most common phones
enum DevicesResolution {
    // Phone
    Android320,           // 320x480
    Android480,           // 480x800
    Android720,           // 720x1280

    IOS3GS,              // 320x480
    IOS4 = IOS3GS,
    IOS4S,               // 480x960
    IOS5,                // 320 x 568

    WP480,               // 480x800
    WP720,               // 720x1280
    WP768,               //768x1280

    // Tablet
    IPAD,                // 1024x768
    IPAD2,               // 2 048 × 1 536 = iPad1 x 2
    IPADMini = IPAD2,
    AndroidTablet1024_1, // 1024x600 (16.9)
    AndroidTablet1024_2, // 1024x768 (4.3)
    AndroidTable1280     // 1280x800
};

typedef struct Device {
    DevicesResolution device;
    QPoint winPos;
    QSize winSize;
    QSize webSize;
    float scale;
    QString image;

    Device(DevicesResolution device,QString img,QPoint pos, QSize winSize, QSize size, float s) {
        this->device = device;
        this->image = img;
        this->winPos = pos;
        this->winSize = winSize;
        this->webSize = size;
        this->scale = s;
    }
} Device;

typedef QList<Device> DeviceList;

class SmartphoneWindow : public QFrame
{
    Q_OBJECT

public:
    SmartphoneWindow();

    virtual void paintEvent(QPaintEvent *);

public slots:
    void changeDevice(DevicesResolution device);

private:
    QPixmap mPixmap;
    DeviceList mDeviceList;

    WebWidget * mWebWidget;
    QWebInspector * mWebInspector;

};

#endif // SMARTPHONEWINDOW_H
