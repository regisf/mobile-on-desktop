#include <QtGui>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load("mobileondesktop");
    app.installTranslator(&translator);
    app.setApplicationName("Mobile On Desktop");
    app.setWindowIcon(QIcon(":/mobileondesktop-icon.png"));

    MainWindow w;
    w.show();

    return app.exec();
}
