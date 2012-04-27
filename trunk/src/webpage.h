#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QtWebKit>

class WebPage : public QWebPage
{
        Q_OBJECT
    public:
        enum UserAgents {
            IOS,
            Android,
            WebOs
        };

        WebPage(QObject * parent = 0);
        void changeFor(UserAgents agent);
        virtual QString userAgentForUrl(const QUrl &) const;
        qreal originalSize();

    public slots:
        void doScroll(int dx, int dy, QRect rect);
        void onLoadFinished(bool);

    private:
        QStringList mUserAgents;
        UserAgents  mCurrentOs;
        qreal       mOriginalSize;

};

#endif // WEBPAGE_H
