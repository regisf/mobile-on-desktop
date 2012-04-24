#include "urlinputdialog.h"

URLInputDialog::URLInputDialog(QWidget* parent) : QInputDialog(parent)
{
    setLabelText(tr("Enter the new URL"));
    setTextValue("http://");
}

QUrl URLInputDialog::url()
{
    QString u = textValue();
    if (!u.startsWith("http://")) {
        u = "http://" + u;
    }

    return QUrl(u);
}

