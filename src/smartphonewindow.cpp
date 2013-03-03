#include "smartphonewindow.h"
#include "aboutdialog.h"
#include "urlinputdialog.h"
#include "preferencesdialog.h"

SmartphoneWindow::SmartphoneWindow()
{
    // Set the window decoration
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // Create the devices list
    mDeviceList
            << Device(Android23, ":/android_320_480", QPoint(30,97), QSize(401,715), QSize(320,480), QPoint(290,20), 1.0f);

    // create the menu button
    mMenuBtn = new QPushButton(QIcon(":/list.png"),"", this);
    QMenu * menu = new QMenu(mMenuBtn);
    QAction * item;
    item = menu->addAction("Load page", this, SLOT(onLoadURL()));
    item->setShortcut(QKeySequence("Ctrl+L"));
    item = menu->addAction("Reload", this, SLOT(onReload()));
    item->setShortcut(QKeySequence::Refresh);
    menu->addSeparator();

    devices = new QMenu(this);
    QActionGroup * devGroup = new QActionGroup(this);

    addToGroup(devices->addAction(DevicesString[iPhone3GS4]), devGroup);
    addToGroup(devices->addAction(DevicesString[iPhone4S]), devGroup);
    addToGroup(devices->addAction(DevicesString[iPhone5]), devGroup);
    devices->addSeparator();
    addToGroup(devices->addAction(DevicesString[Android22]), devGroup);
    addToGroup(devices->addAction(DevicesString[Android23]), devGroup, true);
    addToGroup(devices->addAction(DevicesString[Android32]), devGroup);
    addToGroup(devices->addAction(DevicesString[Android40]), devGroup);
    addToGroup(devices->addAction(DevicesString[Android41]), devGroup);
    addToGroup(devices->addAction(DevicesString[Android42]), devGroup);
    devices->addSeparator();
    addToGroup(devices->addAction(DevicesString[WP75]), devGroup);
    addToGroup(devices->addAction(DevicesString[WP78]), devGroup);
    addToGroup(devices->addAction(DevicesString[WP80]), devGroup);

    item = menu->addAction("Devices");
    item->setMenu(devices);

    QMenu * resolutions = new QMenu(this);
    QActionGroup * resGroup = new QActionGroup(this);
    res320480Item =  addToGroup(resolutions->addAction(DevicesResString[_320480]), resGroup, true);
    res320568Item =  addToGroup(resolutions->addAction(DevicesResString[_320568]), resGroup);
    res320568Item->setEnabled(false);
    res480800Item =  addToGroup(resolutions->addAction(DevicesResString[_480800]), resGroup);
    res7201280Item = addToGroup(resolutions->addAction(DevicesResString[_7201280]), resGroup);
    resolutions->addSeparator();
    res640960Item =  addToGroup(resolutions->addAction(DevicesResString[_640960]), resGroup);
    res640960Item->setEnabled(false);
    res6401136Item = addToGroup(resolutions->addAction(DevicesResString[_6401136]), resGroup);
    res6401136Item->setEnabled(false);

    item = menu->addAction(tr("Resolutions"));
    item->setMenu(resolutions);

    menu->addSeparator();

    item = menu->addAction("Preferences...", this, SLOT(onPreferences()));
    item->setShortcut(QKeySequence::Preferences);

    menu->addSeparator();

    menu->addAction("About Mobile on Device...", this, SLOT(onAbout()));
    menu->addSeparator();

    item = menu->addAction("Quit", qApp, SLOT(quit()));
    item->setShortcut(QKeySequence::Quit);

    mMenuBtn->setMenu(menu);

    // Create the WebKit widget
    mWebWidget = new WebWidget(this);
    changeDevice(Android23);
}

QAction * SmartphoneWindow::addToGroup(QAction * action, QActionGroup * group, bool checked)
{
    group->addAction(action);
    action->setCheckable(true);
    action->setChecked(checked);
    connect(action, SIGNAL(triggered()), SLOT(onChangeDevice()));
    return action;
}

void SmartphoneWindow::changeDevice(DevicesName device)
{
    foreach(Device dev, mDeviceList) {
        if (dev.device == device) {
            mPixmap.load(dev.image);
            setFixedSize(dev.winSize);
            mWebWidget->move(dev.winPos);
            mWebWidget->setFixedSize(dev.webSize);
            mMenuBtn->move(dev.uiBtnPos);
            mCurrentDevice = dev;
            emit(deviceHaveChanged(device));
            emit(resolutionHaveChanged(dev.webSize));
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

void SmartphoneWindow::mouseMoveEvent(QMouseEvent *evt)
{
    if (mIsDragging) {
        this->move(evt->globalPos() - mClickedPoint);
    }
}

void SmartphoneWindow::mousePressEvent(QMouseEvent *evt)
{
    QPoint pos = evt->pos();
    if (evt->button() == Qt::LeftButton) {
        mClickedPoint = pos;
        mIsDragging = true;
        setCursor(Qt::SizeAllCursor);
    }
}

void SmartphoneWindow::mouseReleaseEvent(QMouseEvent *)
{
    mIsDragging = false;
    setCursor(Qt::ArrowCursor);
}

void SmartphoneWindow::uncheckAll()
{
    res320480Item->setEnabled(false);
    res320480Item->setChecked(false);

    res320568Item->setEnabled(false);
    res320568Item->setChecked(false);

    res480800Item->setEnabled(false);
    res480800Item->setChecked(false);

    res7201280Item->setEnabled(false);
    res7201280Item->setChecked(false);

    res640960Item->setEnabled(false);
    res640960Item->setChecked(false);

    res6401136Item->setEnabled(false);
    res6401136Item->setChecked(false);
}

void SmartphoneWindow::setEnabledActionForAndroid(bool enable)
{
    res320480Item->setEnabled(enable);
    res320568Item->setEnabled(false);
    res480800Item->setEnabled(enable);
    res7201280Item->setEnabled(enable);
    res640960Item->setEnabled(false);
    res6401136Item->setEnabled(false);
}

void SmartphoneWindow::onChangeDevice()
{
    QAction * action = dynamic_cast<QAction *>(sender());
    QString menuText =  action->text();

    uncheckAll();

    if (menuText == DevicesString[iPhone3GS4])
    {
        res320480Item->setEnabled(true);
        res320480Item->setChecked(true);

        emit(deviceHaveChanged(iPhone3GS4));
        //emit(resolutionHaveChanged());
        return;
    }
    else if (menuText == DevicesString[iPhone4S])
    {
        res320480Item->setEnabled(true);
        res640960Item->setEnabled(true);
        res640960Item->setChecked(true);
        res6401136Item->setEnabled(false);
        emit(deviceHaveChanged(iPhone4S));
        //emit(resolutionHaveChanged());
        return;
    }
    else if (menuText == DevicesString[iPhone5])
    {
        res320568Item->setEnabled(true);
        res6401136Item->setEnabled(true);
        res6401136Item->setChecked(true);
        emit(deviceHaveChanged(iPhone5));
        //emit(resolutionHaveChanged());
        return;
    }
    else if (menuText == DevicesString[Android22])
    {
        res320480Item->setEnabled(true);
        res320480Item->setChecked(true);
        res480800Item->setEnabled(true);
        emit(deviceHaveChanged(Android22));
        //emit(resolutionHaveChanged());
        return;
    }
    else if (menuText == DevicesString[Android23])
    {
        res320480Item->setEnabled(true);
        res320480Item->setChecked(true);
        res480800Item->setEnabled(true);
        emit(deviceHaveChanged(Android23));
        //emit(resolutionHaveChanged());
        return;
    }
    else if (menuText == DevicesString[Android32])
    {
        setEnabledActionForAndroid(true);
        res320480Item->setChecked(true);
        emit(deviceHaveChanged(Android32));
        //emit(resolutionHaveChanged());
        return;
    }
    else if (menuText == DevicesString[Android40])
    {
        setEnabledActionForAndroid(true);
        res320480Item->setChecked(true);
        emit(deviceHaveChanged(Android40));
        //emit(resolutionHaveChanged());
        return;
    }
    else if (menuText == DevicesString[Android41])
    {
        setEnabledActionForAndroid(true);
        res320480Item->setChecked(true);
        emit(deviceHaveChanged(Android41));
        //emit(resolutionHaveChanged());
        return;
    }
    else if (menuText == DevicesString[Android42])
    {
        setEnabledActionForAndroid(true);
        res320480Item->setChecked(true);
        emit(deviceHaveChanged(Android42));
        //emit(resolutionHaveChanged());
        return;
    }
    else if (menuText == DevicesString[WP75])
    {
        qDebug() << "Windows Phone 7.5";
    }
    else if (menuText == DevicesString[WP78])
    {
        qDebug() << "Windows Phone 7.8";
    }
    else if (menuText == DevicesString[WP80])
    {
        qDebug() << "Windows Phone 8.0";
    }

    if (menuText == DevicesResString[_320480])
    {
        qDebug() << " 320 par 480";
    }
    else if (menuText == DevicesResString[_320568])
    {
        qDebug() << " 320 par 568";
    }
    else if (menuText == DevicesResString[_480800])
    {
        qDebug() << " 480 par 800";
    }
    else if (menuText == DevicesResString[_7201280])
    {
        qDebug() << " 720 par 1280";
    }
    else if (menuText == DevicesResString[_640960])
    {
        qDebug() << " 640 par 960";
    }
    else if (menuText == DevicesResString[_6401136])
    {
        qDebug() << " 640 par 1136";
    }

}

void SmartphoneWindow::onLoadURL()
{
    URLInputDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted)
    {
        mWebWidget->stop();
        mWebWidget->load(dlg.url());
//        mWebInspector->setPage(mWebWidget->page());
    }
}

void SmartphoneWindow::onReload()
{
    mWebWidget->stop();
    mWebWidget->reload();
}


void SmartphoneWindow::onPreferences()
{
    PreferencesDialog dlg(this);
    dlg.exec();
}

void SmartphoneWindow::onAbout()
{
    AboutDialog(this).exec();
}
