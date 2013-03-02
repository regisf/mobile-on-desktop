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

#ifndef WEBWIDGET_H
#define WEBWIDGET_H

#include "webpage.h"

#include <QtWebKit>
#include <QStringList>

class WebWidget : public QWebView
{
        Q_OBJECT
    public:
        WebWidget(QWidget * parent=0);

        /*
         * Catch those events for simulating finger on a touch screen
         */
        virtual void mouseMoveEvent(QMouseEvent *);
        virtual void wheelEvent(QWheelEvent * evt); // Swipe event
        virtual void mousePressEvent(QMouseEvent *);
        virtual void mouseReleaseEvent(QMouseEvent *);

    public slots:
        void changeFor(WebPage::UserAgents agent);
        void refitPage();

    private slots:
        void onNetworkReply(QNetworkReply * reply);
        void refitPage(bool b);

    signals:
        void noHostFound(QUrl);
        void connectionRefused();
        void remotlyClosed();
        void timeOut();
        void operationCancelled();
        void pageNotFound(QUrl);

    private:
        WebPage * mWebPage;
        bool mButtonDown;
};

#endif // WEBWIDGET_H
