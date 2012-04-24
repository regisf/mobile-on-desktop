#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "webpage.h"
#include "urlinputdialog.h"
#include "preferencesdialog.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle(qApp->applicationName());

    ui->setupUi(this);

    mWebWidget = new WebWidget(this);
    setCentralWidget(mWebWidget);
    setFixedSize(320,480);

    mProgressBar = new QProgressBar(this);
    mProgressBar->setMaximum(100);
    mProgressBar->setMinimum(0);
    mProgressBar->setValue(0);
    mProgressBar->setVisible(false);
    statusBar()->addWidget(mProgressBar, 1);

    connect(ui->actionNewWindow,    SIGNAL(triggered()),        SLOT(onNewWindow()));
    connect(ui->action_Close,       SIGNAL(triggered()),        SLOT(close()));
    connect(ui->actionLoadURL,      SIGNAL(triggered()),        SLOT(onLoadURL()));
    connect(ui->actionReload,       SIGNAL(triggered()),        SLOT(onReload()));
    connect(ui->actionQuit,         SIGNAL(triggered()),        SLOT(onQuit()));
    connect(ui->actionPreferences,  SIGNAL(triggered()),        SLOT(onPreferences()));
    connect(ui->actionAbout,        SIGNAL(triggered()),        SLOT(onAbout()));
    connect(ui->actionIOS,          SIGNAL(triggered()),        SLOT(onChangeForIOs()));
    connect(ui->actionAndroid,      SIGNAL(triggered()),        SLOT(onChangeForAndroid()));
    connect(ui->actionWebOS,        SIGNAL(triggered()),        SLOT(onChangeForWebOs()));
    connect(ui->action320x400,      SIGNAL(triggered()),        SLOT(onResolution400()));
    connect(ui->action320x480,      SIGNAL(triggered()),        SLOT(onResolution480()));
    connect(ui->action1024x768,     SIGNAL(triggered()),        SLOT(onResolution768()));

    connect(ui->actionStop,         SIGNAL(triggered()),        SLOT(onStop()));
    connect(ui->actionBack,         SIGNAL(triggered()),        SLOT(onGoBack()));
    connect(ui->actionForward,      SIGNAL(triggered()),        SLOT(onGoForward()));

    connect(mWebWidget,             SIGNAL(loadFinished(bool)), SLOT(onViewLoadFinished(bool)));
    connect(mWebWidget,             SIGNAL(loadStarted()),      SLOT(onViewLoadStart()));
    connect(mWebWidget,             SIGNAL(loadProgress(int)),  SLOT(onViewLoadProgress(int)));
    connect(mWebWidget,             SIGNAL(linkClicked(QUrl)),  SLOT(onViewLinkClicked(QUrl)));
    connect(mWebWidget,             SIGNAL(urlChanged(QUrl)),   SLOT(onViewUrlChanged(QUrl)));

    connect(mWebWidget,             SIGNAL(pageNotFound(QUrl)),     SLOT(onPageNotFound(QUrl)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewWindow()
{
    MainWindow * w = new MainWindow;
    w->show();
}

void MainWindow::onLoadURL()
{
    URLInputDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted)
    {
        mWebWidget->stop();
        mWebWidget->load(dlg.url());
    }
}

void MainWindow::onReload()
{
    mWebWidget->stop();
    mWebWidget->reload();
}

void MainWindow::onQuit()
{
    qApp->quit();
}

void MainWindow::onPreferences()
{
    PreferencesDialog dlg(this);

    dlg.exec();
}

void MainWindow::onAbout()
{
    AboutDialog(this).exec();
}

void MainWindow::onChangeForIOs()
{
    mWebWidget->changeFor(WebPage::IOS);
    ui->actionAndroid->setChecked(false);
    ui->actionWebOS->setChecked(false);
}

void MainWindow::onChangeForAndroid()
{
    mWebWidget->changeFor(WebPage::Android);
    ui->actionIOS->setChecked(false);
    ui->actionWebOS->setChecked(false);
}

void MainWindow::onChangeForWebOs()
{
    mWebWidget->changeFor(WebPage::WebOs);
    ui->actionIOS->setChecked(false);
    ui->actionAndroid->setChecked(false);
}

void MainWindow::onResolution400()
{
    setFixedSize(320,400);
    ui->action320x480->setChecked(false);
    ui->action1024x768->setChecked(false);
}

void MainWindow::onResolution480()
{
    setFixedSize(320,480);
    ui->action1024x768->setChecked(false);
    ui->action320x400->setChecked(false);
}

void MainWindow::onResolution768()
{
    setFixedSize(1024,768);
    ui->action320x480->setChecked(false);
    ui->action320x400->setChecked(false);
}

void MainWindow::onGoBack()
{

}

void MainWindow::onGoForward()
{

}

void MainWindow::onStop()
{
    mWebWidget->stop();
}

void MainWindow::onViewLoadStart()
{
    mProgressBar->setVisible(true);
    mProgressBar->setValue(0);
}

void MainWindow::onViewLoadFinished(bool)
{
    mProgressBar->setVisible(false);
}

void MainWindow::onViewLoadProgress(int progress)
{
    mProgressBar->setValue(progress);
}

void MainWindow::onViewUrlChanged(const QUrl & url)
{

}

void MainWindow::onViewLinkClicked(const QUrl & url)
{

}

void MainWindow::onPageNotFound(QUrl url)
{
    QMessageBox::critical(this, tr("Error"), tr("Page %1 was not found").arg(url.toString()));
}
