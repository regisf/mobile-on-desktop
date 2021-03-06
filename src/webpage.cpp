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

#include "webpage.h"
#include <QDebug>

WebPage::WebPage(QObject * parent) : QWebPage(parent), mOriginalSize(0)
{
    mUserAgents
        << "Mozilla/5.0 (iPhone; U; CPU iPhone OS 4_3_2 like Mac OS X; en-us) AppleWebKit/533.17.9 (KHTML, like Gecko) Version/5.0.2 Mobile/8H7 Safari/6533.18.5"
        << "Mozilla/5.0 (Linux; U; Android 2.2; en-us; Nexus One Build/FRF91) AppleWebKit/533.1 (KHTML, like Gecko) Version/4.0 Mobile Safari/533.1"
        << "Mozilla/5.0 (compatible; MSIE 9.0; Windows Phone OS 7.5; Trident/5.0; IEMobile/9.0; Microsoft)";

    mCurrentOs = Android;
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
