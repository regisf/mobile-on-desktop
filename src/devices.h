#ifndef DEVICES_H
#define DEVICES_H

const QString DevicesResString[] = {
    "320 x 480",
    "320 x 568",
    "480 x 800",
    "720 x 1280",
    "640 x 960  (Retina)",
    "640 x 1136 (Retina)"
};

const QString DevicesString[] = {
    "iPhone 3GS/4",
    "iPhone 4S",
    "iPhone 5",
    "Android 2.2",
    "Android 2.3",
    "Android 3.2",
    "Android 4.0",
    "Android 4.1",
    "Android 4.2",
    "Windows Phone 7.5",
    "Windows Phone 7.8",
    "Windows Phone 8"
};

/* TODO:
 *     Blackberry devices,
 *     Firefox Devices (Including Gecko Engine ????? - I think this will be painful)
 */

// This is for the most common phones
enum DevicesName {
    // Phone
    iPhone3GS4,
    iPhone4S,
    iPhone5,
    Android22,
    Android23,
    Android32,
    Android40,
    Android41,
    Android42,
    WP75,
    WP78,
    WP80
};

enum DevicesResolution {
    _320480,
    _320568,
    _480800,
    _7201280,
    _640960,
    _6401136
};
//    // Tablet
//    IPAD,                // 1024x768
//    IPAD2,               // 2 048 × 1 536 = iPad1 x 2
//    IPADMini = IPAD2,
//    AndroidTablet1024_1, // 1024x600 (16.9)
//    AndroidTablet1024_2, // 1024x768 (4.3)
//    AndroidTable1280     // 1280x800
//};

/**
 * Device struct to store everything needed
 */
typedef struct Device {
    QPoint winPos;//! The WebWidget position
    QSize winSize;//! The WebWidget size
    QSize webSize;//! The
    QString image;
    QPoint uiBtnPos;
    DevicesName device;
    DevicesResolution res;
    float scale;

    Device() {}

    /** Constructor
     * @param device The device type as defined in the enum
     * @param img The resource path for the window decoration
     * @param pos The position of the web view
     * @param winSize The web view size regarding the decoration
     * @param size The real phone resolution
     * @param uibtnpos The position of the ui button
     * @param scale The scale to fit in the winSize
     */
    Device(DevicesName device,QString img,QPoint pos, QSize winSize, QSize size, QPoint uibtnpos, float scale) {
        this->device = device;
        this->image = img;
        this->winPos = pos;
        this->winSize = winSize;
        this->webSize = size;
        this->uiBtnPos = uibtnpos;
        this->scale = scale;
    }
} Device;

/** Declare a QList for strong type
 */
typedef QList<Device> DeviceList;


#endif // DEVICES_H
