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
        virtual void wheelEvent(QWheelEvent *);

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
};

#endif // WEBWIDGET_H
