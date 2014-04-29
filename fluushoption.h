#ifndef FLUUSHOPTION_H
#define FLUUSHOPTION_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QProgressDialog>

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

public slots:
    void sysTrayActivated(QSystemTrayIcon::ActivationReason r);
    void imageCaptured(QPixmap p);

    void uploadProgress(qint64 sent, qint64 total);
    void done();

private:

    QSystemTrayIcon *trayIcon;

    Ui::FluushOption *ui;
    QNetworkAccessManager *mgr;
    QProgressDialog *dia;
};

#endif // FLUUSHOPTION_H
