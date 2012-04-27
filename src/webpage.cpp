#include "webpage.h"
#include <QDebug>

WebPage::WebPage(QObject * parent) : QWebPage(parent), mOriginalSize(0)
{
    mUserAgents
        << "Mozilla/5.0 (iPhone; U; CPU iPhone OS 4_3_2 like Mac OS X; en-us) AppleWebKit/533.17.9 (KHTML, like Gecko) Version/5.0.2 Mobile/8H7 Safari/6533.18.5"
        << "Mozilla/5.0 (Linux; U; Android 2.2; en-us; Nexus One Build/FRF91) AppleWebKit/533.1 (KHTML, like Gecko) Version/4.0 Mobile Safari/533.1"
        << "Mozilla/5.0 (webOS/1.3; U; en-US) AppleWebKit/525.27.1 (KHTML, like Gecko) Version/1.0 Safari/525.27.1 Desktop/1.0";
    mCurrentOs = IOS;
    mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);

    connect(this, SIGNAL(loadFinished(bool)), SLOT(onLoadFinished(bool)));
}

QString WebPage::userAgentForUrl(const QUrl &) const
{
    return mUserAgents[mCurrentOs];
}

void WebPage::changeFor(UserAgents agent)
{
    mCurrentOs = agent;
}

void WebPage::doScroll(int dx, int dy, QRect  rect)
{
    // TODO : Smoother scrolling and horizontal scrolling
    mainFrame()->scroll(dx, dy);
}

void WebPage::onLoadFinished(bool b)
{
    Q_UNUSED(b);
    mOriginalSize = static_cast<qreal>(mainFrame()->contentsSize().width());
}

qreal WebPage::originalSize()
{
    return mOriginalSize;
}
