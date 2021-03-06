#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "webwidget.h"
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

#include <QMainWindow>
#include <QProgressBar>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        enum Resolution {
            R320x400,
            R320x480,
            R480x800,
            R1024x768
        };

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void onNewWindow();
        void onLoadURL();
        void onReload();
        void onQuit();
        void onPreferences();
        void onChangeForIOs();
        void onChangeForAndroid();
        void onChangeForWebOs();
        void onChangeForWinPhone7();
        void onResolution320x400();
        void onResolution320x480();
        void onResolution480x800();
        void onResolution1024x768();
        void onShowHideInspector();
        void onAbout();

        void onStop();
        void onGoBack();
        void onGoForward();

        void onViewLoadStart();
        void onViewLoadFinished(bool);
        void onViewLoadProgress(int);
        void onViewUrlChanged(const QUrl &);
        void onViewLinkClicked(const QUrl &);

        void onPageNotFound(QUrl url);
        void onNoHostFound(QUrl url);

    protected:
        virtual void resizeEvent(QResizeEvent *);

    private:
        void changeWindowTitle();
        void ensureResolutionChecked(Resolution toCheck);
        void ensureOSChecked(WebPage::UserAgents toCheck);

    private:
        Ui::MainWindow * ui;
        WebWidget * mWebWidget;
        QProgressBar * mProgressBar;
        QWebInspector * mWebInspector;
};

#endif // MAINWINDOW_H
