#ifndef URLINPUTDIALOG_H
#define URLINPUTDIALOG_H

#include <QInputDialog>
#include <QUrl>

class URLInputDialog : public QInputDialog
{
        Q_OBJECT
    public:
        URLInputDialog(QWidget * parent = 0);

        QUrl url();
};

#endif // URLINPUTDIALOG_H
