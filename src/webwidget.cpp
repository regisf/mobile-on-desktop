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

#include "webwidget.h"
#include "smartphonewindow.h"
#include <QDebug>


WebWidget::WebWidget(QWidget * parent) : QWebView(parent), mButtonDown(false)
{
    mWebPage = new WebPage(this);

    connect(mWebPage->networkAccessManager(), SIGNAL(finished(QNetworkReply*)), SLOT(onNetworkReply(QNetworkReply *)));
    connect(this, SIGNAL(loadFinished(bool)), SLOT(refitPage(bool)));
    connect(mWebPage, SIGNAL(contentsChanged()), SLOT(refitPage()));
    connect(dynamic_cast<SmartphoneWindow *>(parent), SIGNAL(deviceHaveChanged(DevicesName)), SLOT(onDeviceChanged(DevicesName)));

    setPage(mWebPage);
    setHtml(QFile(":/DefaultPage.html").readAll().data());

    QResource res(":/DefaultPage.html");
    QByteArray arr(reinterpret_cast<const char *>(res.data()));
    setHtml(arr);
}

void WebWidget::changeFor(WebPage::UserAgents agent)
{
    mWebPage->changeFor(agent);
    reload();
}

void WebWidget::onNetworkReply(QNetworkReply * reply)
{
    switch (reply->error())
    {
        case QNetworkReply::NoError:
            return;
            break;

        case QNetworkReply::ConnectionRefusedError:
            emit(connectionRefused());
            break;

        case QNetworkReply::RemoteHostClosedError:
            emit(remotlyClosed());
            break;

        case QNetworkReply::HostNotFoundError:
            emit(noHostFound(reply->url()));
            break;

        case QNetworkReply::TimeoutError:
            emit(timeOut());
            break;

        case QNetworkReply::OperationCanceledError:
            emit(operationCancelled());
            break;

        case QNetworkReply::TemporaryNetworkFailureError:
            break;

        case QNetworkReply::ContentAccessDenied:
            break;

        case QNetworkReply::ContentOperationNotPermittedError:
            break;

        case QNetworkReply::ContentNotFoundError:
            emit(pageNotFound(reply->url()));
            break;

        case QNetworkReply::AuthenticationRequiredError:
            break;

        case QNetworkReply::ContentReSendError:
            break;

        case QNetworkReply::UnknownContentError:
            break;

        // All unhandled error
        case QNetworkReply::UnknownNetworkError:
        default:
            break;
    }
}

void WebWidget::refitPage(bool b)
{
    Q_UNUSED(b)
    refitPage();
}

void WebWidget::refitPage()
{
    QRect mySize = this->contentsRect();
    qreal factor = 1.0;

    if (mWebPage->originalSize() > mySize.width())
        factor = static_cast<qreal>(mySize.width()) / mWebPage->originalSize();
    setZoomFactor(factor);
}

void WebWidget::onDeviceChanged(DevicesName name)
{
    qDebug() << DevicesString[name];
}

void WebWidget::onResolutionChanged(DevicesResolution resolution)
{

}

//void WebWidget::mouseMoveEvent(QMouseEvent *evt)
//{
//    if (mButtonDown == true)
//    {
//        qDebug() << "Drag";
//    }
//    else
//    {
//        qDebug() << "Move";
//    }
//    qDebug() << evt;}

//void WebWidget::mousePressEvent(QMouseEvent *evt)
//{
//    Q_UNUSED(evt);
//    mButtonDown = true;
//}

//void WebWidget::mouseReleaseEvent(QMouseEvent *evt)
//{
//    Q_UNUSED(evt);
//    mButtonDown = false;
//}

void WebWidget::wheelEvent(QWheelEvent * evt)
{
    QRect r = frameGeometry();
    mWebPage->doScroll(0, evt->delta(), r);
    qDebug() << evt;
}
