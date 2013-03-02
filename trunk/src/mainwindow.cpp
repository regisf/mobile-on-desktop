/* Mobile On Desktop - A Smartphone emulator on desktop
 * Copyright (c) 2012 Régis FLORET
 *
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Régis FLORET nor the names of its contributors
 * 	  may be used to endorse or promote products derived from this
 * 	  software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
    ui->setupUi(this);
//    this->setWindowFlags(Qt::FramelessWindowHint);
    changeWindowTitle();

    mWebWidget = new WebWidget(this);
    mWebWidget->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    setCentralWidget(mWebWidget);
    setFixedSize(320,480);

    mWebInspector = new QWebInspector;
    mWebInspector->setPage(mWebWidget->page());

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
    connect(ui->actionWinPhone7,    SIGNAL(triggered()),        SLOT(onChangeForWinPhone7()));
    connect(ui->action320x400,      SIGNAL(triggered()),        SLOT(onResolution320x400()));
    connect(ui->action320x480,      SIGNAL(triggered()),        SLOT(onResolution320x480()));
    connect(ui->action480x800,      SIGNAL(triggered()),        SLOT(onResolution480x800()));
    connect(ui->action1024x768,     SIGNAL(triggered()),        SLOT(onResolution1024x768()));
    connect(ui->actionInspector,    SIGNAL(triggered()),        SLOT(onShowHideInspector()));

    connect(ui->actionStop,         SIGNAL(triggered()),        SLOT(onStop()));
    connect(ui->actionBack,         SIGNAL(triggered()),        SLOT(onGoBack()));
    connect(ui->actionForward,      SIGNAL(triggered()),        SLOT(onGoForward()));

    connect(mWebWidget,             SIGNAL(loadFinished(bool)), SLOT(onViewLoadFinished(bool)));
    connect(mWebWidget,             SIGNAL(loadStarted()),      SLOT(onViewLoadStart()));
    connect(mWebWidget,             SIGNAL(loadProgress(int)),  SLOT(onViewLoadProgress(int)));
    connect(mWebWidget,             SIGNAL(linkClicked(QUrl)),  SLOT(onViewLinkClicked(QUrl)));
    connect(mWebWidget,             SIGNAL(urlChanged(QUrl)),   SLOT(onViewUrlChanged(QUrl)));

    connect(mWebWidget,             SIGNAL(pageNotFound(QUrl)), SLOT(onPageNotFound(QUrl)));
    connect(mWebWidget,             SIGNAL(noHostFound(QUrl)),      SLOT(onNoHostFound(QUrl)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    mWebWidget->refitPage();
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
        mWebInspector->setPage(mWebWidget->page());
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
    ensureOSChecked(WebPage::IOS);
    changeWindowTitle();
}

void MainWindow::onChangeForAndroid()
{
    mWebWidget->changeFor(WebPage::Android);
    ensureOSChecked(WebPage::Android);
    changeWindowTitle();
}

void MainWindow::onChangeForWebOs()
{
    mWebWidget->changeFor(WebPage::WebOs);
    ensureOSChecked(WebPage::WebOs);
    changeWindowTitle();
}

void MainWindow::onChangeForWinPhone7()
{
    mWebWidget->changeFor(WebPage::WindowsPhone7);
    ensureOSChecked(WebPage::WindowsPhone7);
    changeWindowTitle();
}

void MainWindow::onResolution320x400()
{
    setFixedSize(320,400);
    ensureResolutionChecked(R320x400);
    changeWindowTitle();
    mWebWidget->reload();
}

void MainWindow::onResolution320x480()
{
    setFixedSize(320,480);
    ensureResolutionChecked(R320x480);
    changeWindowTitle();
    mWebWidget->reload();
}

void MainWindow::onResolution1024x768()
{
    setFixedSize(1024,768);
    ensureResolutionChecked(R1024x768);
    changeWindowTitle();
    mWebWidget->reload();
}

void MainWindow::onResolution480x800()
{
    setFixedSize(480,800);
    ensureResolutionChecked(R480x800);
    changeWindowTitle();
    mWebWidget->reload();
}

void MainWindow::ensureResolutionChecked(Resolution toCheck)
{
    ui->action320x400->setChecked(toCheck == R320x400);
    ui->action320x480->setChecked(toCheck == R320x480);
    ui->action480x800->setChecked(toCheck == R480x800);
    ui->action1024x768->setChecked(toCheck == R1024x768);
}

void MainWindow::ensureOSChecked(WebPage::UserAgents toCheck)
{
    ui->actionIOS->setChecked(toCheck == WebPage::IOS);
    ui->actionAndroid->setChecked(toCheck == WebPage::Android);
    ui->actionWebOS->setChecked(toCheck == WebPage::WebOs);
    ui->actionWinPhone7->setChecked(toCheck == WebPage::WindowsPhone7);
}

void MainWindow::changeWindowTitle()
{
    QString size;
    QString plateform;

    if (ui->action320x480->isChecked())
        size = "320x480";
    else if (ui->action320x400->isChecked())
        size = "320x400";
    else if (ui->action1024x768->isChecked())
        size = "1024x768";
    else if (ui->action480x800->isChecked())
        size = "480x800";

    if (ui->actionAndroid->isChecked())
        plateform = "Android";
    else if (ui->actionIOS->isChecked())
        plateform = "iOS";
    else if (ui->actionWebOS->isChecked())
        plateform = "WebOS";
    else if (ui->actionWinPhone7->isChecked())
        plateform = "Windows Phone 7";

    setWindowTitle(QString("%1 - %2 - %3").arg(qApp->applicationName()).arg(plateform).arg(size));
}

void MainWindow::onGoBack()
{
    mWebWidget->back();
}

void MainWindow::onGoForward()
{
    mWebWidget->forward();
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
    mWebInspector->setPage(mWebWidget->page());
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
//    QMessageBox::critical(this, tr("Error"), tr("Page %1 was not found").arg(url.toString()));
}

void MainWindow::onShowHideInspector()
{
    qDebug() << (mWebWidget->page() == NULL);
    qDebug() << mWebWidget->settings()->testAttribute(QWebSettings::DeveloperExtrasEnabled);
    mWebInspector->setVisible(!mWebInspector->isVisible());
}

void MainWindow::onNoHostFound(QUrl url)
{
    QMessageBox::critical(this, tr("No host found"), tr("The host %1 was not found").arg(url.toString()));
}
