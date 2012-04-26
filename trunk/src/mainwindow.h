#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "webwidget.h"

#include <QMainWindow>
#include <QProgressBar>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
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
        void onResolution400();
        void onResolution480();
        void onResolution768();
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


    private:
        Ui::MainWindow * ui;
        WebWidget * mWebWidget;
        QProgressBar * mProgressBar;
        QWebInspector * mWebInspector;
};

#endif // MAINWINDOW_H
