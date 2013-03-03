#ifndef SMARTPHONEWINDOW_H
#define SMARTPHONEWINDOW_H

#include "webwidget.h"
#include "devices.h"
#include <QtGui>
/**
 * @brief The SmartphoneWindow class
 */
class SmartphoneWindow : public QFrame
{
    Q_OBJECT

public:
    /**
     * @brief SmartphoneWindow
     */
    SmartphoneWindow();

    /**
     * @brief paintEvent
     */
    virtual void paintEvent(QPaintEvent *);

    /**
     * @brief mousePressEvent
     */
    virtual void mousePressEvent(QMouseEvent *);

    /**
     * @brief mouseReleaseEvent
     */
    virtual void mouseReleaseEvent(QMouseEvent *);

    /**
     * @brief mouseMoveEvent
     */
    virtual void mouseMoveEvent(QMouseEvent *);

private: // Methods
    /**
     * @brief addToGroup
     * @param action
     * @param group
     * @param checked
     * @return
     */
    QAction * addToGroup(QAction * action, QActionGroup * group, bool checked=false);
    void uncheckAll();
    void setEnabledActionForAndroid(bool enable);

public slots:
    /**
     * @brief changeDevice
     * @param device
     */
    void changeDevice(DevicesName device);

    /**
     * @brief onChangeDevice
     */
    void onChangeDevice();

    /**
     * @brief onAbout
     */
    void onAbout();

    /**
     * @brief onLoadURL
     */
    void onLoadURL();

    /**
     * @brief onPreferences
     */
    void onPreferences();

    /**
     * @brief onReload
     */
    void onReload();

signals:
    void deviceHaveChanged(DevicesName);
    void resolutionHaveChanged(QSize &);

private: // Variables
    QPixmap mPixmap;
    DeviceList mDeviceList;
    QPoint mClickedPoint;
    Device mCurrentDevice;
    bool mIsDragging;

    QPushButton * mMenuBtn;
    WebWidget * mWebWidget;
    QWebInspector * mWebInspector;

    QMenu * devices;
    QAction * res320480Item;
    QAction * res320568Item;
    QAction * res480800Item;
    QAction * res7201280Item;
    QAction * res640960Item;
    QAction * res6401136Item;
};

#endif // SMARTPHONEWINDOW_H
