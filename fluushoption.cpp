#include "fluushoption.h"
#include "ui_fluushoption.h"
#include "screenshotrestriction.h"
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>
#include <QAction>
#include <QPixmap>
#include <QScreen>
#include <QDesktopWidget>
#include <QDateTime>
#include <QDir>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QProgressDialog>
#include <QMessageBox>
#include <QClipboard>

FluushOption::FluushOption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FluushOption)
{
    ui->setupUi(this);

    QMenu *contextMenu = new QMenu(this);
    QAction *showMe, *quit;

    showMe = new QAction(tr("Show options"), this);
    connect(showMe, SIGNAL(triggered()), this, SLOT(show()));

    quit = new QAction(tr("Quit"), this);
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    contextMenu->addAction(showMe);
    contextMenu->addAction(quit);

    trayIcon = new QSystemTrayIcon(QIcon(":/icons/fluush-icon"), this);
    trayIcon->setContextMenu(contextMenu);
    trayIcon->show();
    trayIcon->setToolTip(tr("Fluush - Right click to configure"));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(sysTrayActivated(QSystemTrayIcon::ActivationReason)));

    mgr = new QNetworkAccessManager(this);

    dia = new QProgressDialog(tr("Uploading to puush"), tr("Cancel"), 0, 100, this);
    dia->hide();
    dia->setAutoReset(false);
    dia->setAutoClose(false);
}

FluushOption::~FluushOption()
{
    delete ui;
}

void FluushOption::sysTrayActivated(QSystemTrayIcon::ActivationReason r)
{
    switch (r) {
    case QSystemTrayIcon::Trigger:
    {
        //If we click on the system tray icon, we'll take a screenshot
        /*if(ui->hideThis->isChecked() && isVisible())
            hide();*/

        QPixmap screenshot = QApplication::screens().first()->grabWindow(QApplication::desktop()->winId());
        screenshot.save("essai.png");
        ScreenShotRestriction *rest = new ScreenShotRestriction(screenshot, this);
        rest->showFullScreen();
        connect(rest, SIGNAL(imageCaptured(QPixmap)), this, SLOT(imageCaptured(QPixmap)));
        break;
    }
    default:
        break;
    }
}

void FluushOption::closeEvent(QCloseEvent *e)
{
    hide();
    e->ignore();
}

void FluushOption::imageCaptured(QPixmap p)
{
    QString savePath = QDir::tempPath() + "/" + QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss") + ".png";
    p.save(savePath);

    QNetworkRequest push(QUrl("https://puush.me/api/up"));

    QHttpMultiPart *postData = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart apiKey;
    apiKey.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"k\""));
    apiKey.setBody(QByteArray().append(ui->apiKey->text()));

    QHttpPart poop;
    poop.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"z\""));
    poop.setBody("poop");

    QHttpPart image;
    image.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"f\"; filename=\""+ savePath + "\""));
    image.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
    QFile *f = new QFile(savePath);
    if(!f->open(QIODevice::ReadOnly))
    {
        delete postData;
        delete f;
        return;
    }
    image.setBodyDevice(f);


    postData->append(apiKey);
    postData->append(poop);
    postData->append(image);

    QNetworkReply *rep = mgr->post(push, postData);
    connect(rep, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(uploadProgress(qint64,qint64)));
    connect(rep, SIGNAL(finished()), this, SLOT(done()));
    connect(dia, SIGNAL(canceled()), rep, SLOT(abort()));

    dia->show();
    dia->setLabelText(tr("Uploading to puush"));
    dia->setValue(0);
}

void FluushOption::uploadProgress(qint64 sent, qint64 total)
{
    dia->setMaximum(total);
    dia->setValue(sent);

    if(total == sent)
        dia->setLabelText(tr("Waiting for puush response"));
}

void FluushOption::done()
{
    dia->hide();

    QNetworkReply *rep = qobject_cast<QNetworkReply*>(sender());
    if(rep)
    {
        QString repStr = rep->readAll();
        QStringList lst = repStr.split(",");
        if(lst[0] != "0")
            QMessageBox::warning(this, tr("Upload faillure"), "Failed to upload to puush");
        else
        {
            trayIcon->showMessage(tr("Upload success"), lst[1]);
            ui->history->appendPlainText(lst[1]+"\n");
            QApplication::clipboard()->setText(lst[1]);
        }
    }
}
