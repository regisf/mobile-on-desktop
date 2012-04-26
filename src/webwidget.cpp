#include "webwidget.h"
#include <QDebug>

WebWidget::WebWidget(QWidget * parent) : QWebView(parent)
{
    mWebPage = new WebPage(this);

    connect(mWebPage->networkAccessManager(),
            SIGNAL(finished(QNetworkReply*)),
            SLOT(onNetworkReply(QNetworkReply *)));

    setPage(mWebPage);
    setHtml(QFile(":/DefaultPage.html").readAll().data());
    qDebug() << QFile(":/DefaultPage.html").readAll().data();
}

void WebWidget::changeFor(WebPage::UserAgents agent)
{
    mWebPage->changeFor(agent);
    reload();
}

void WebWidget::wheelEvent(QWheelEvent * evt)
{
    QRect r = frameGeometry();
    mWebPage->doScroll(0, evt->delta(), r);
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
