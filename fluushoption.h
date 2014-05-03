#ifndef FLUUSHOPTION_H
#define FLUUSHOPTION_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QProgressDialog>

#include "fluushnetwork.h"

namespace Ui {
class FluushOption;
}

class FluushOption : public QDialog
{
    Q_OBJECT

public:
    explicit FluushOption(QWidget *parent = 0);
    ~FluushOption();

    virtual void closeEvent(QCloseEvent *e);
    void loadSettings();
    void saveSettings();

public slots:
    void sysTrayActivated(QSystemTrayIcon::ActivationReason r);
    void imageCaptured(QPixmap p);

    void uploadProgress(qint64 sent, qint64 total);
    void requestError(const QString& msg);
    void uploadComplete(const QString& url);

    void quit();
private:

    QSystemTrayIcon *trayIcon;

    Ui::FluushOption *ui;
    QProgressDialog *dia;

    FluushNetwork *net;
};

#endif // FLUUSHOPTION_H
