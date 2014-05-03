#include "fluushoption.h"
#include "ui_fluushoption.h"
#include "screenshotrestriction.h"
#include "fluushrequestupload.h"
#include "fluushrequesthistory.h"
#include "thumbwidget.h"
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>
#include <QAction>
#include <QPixmap>
#include <QScreen>
#include <QDesktopWidget>
#include <QDateTime>
#include <QDir>
#include <QProgressDialog>
#include <QMessageBox>
#include <QClipboard>
#include <QSettings>

FluushOption::FluushOption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FluushOption)
{
    ui->setupUi(this);

    QMenu *contextMenu = new QMenu(this);
    QAction *takeFullScreen, *showMe, *quit;

    takeFullScreen = new QAction(tr("Take the full screen"), this);
    takeFullScreen->setCheckable(true);
    takeFullScreen->setChecked(ui->full_screen->isChecked());
    connect(takeFullScreen, SIGNAL(toggled(bool)), ui->full_screen, SLOT(setChecked(bool)));
    connect(ui->full_screen, SIGNAL(toggled(bool)), takeFullScreen, SLOT(setChecked(bool)));

    showMe = new QAction(tr("Show options"), this);
    connect(showMe, SIGNAL(triggered()), this, SLOT(show()));

    quit = new QAction(tr("Quit"), this);
    connect(quit, SIGNAL(triggered()), this, SLOT(quit()));

    contextMenu->addAction(takeFullScreen);
    contextMenu->addSeparator();
    contextMenu->addAction(showMe);
    contextMenu->addAction(quit);

    trayIcon = new QSystemTrayIcon(QIcon(":/icons/fluush-icon"), this);
    trayIcon->setContextMenu(contextMenu);
    trayIcon->show();
    trayIcon->setToolTip(tr("Fluush - Right click to configure"));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(sysTrayActivated(QSystemTrayIcon::ActivationReason)));

    net = new FluushNetwork(this);

    dia = new QProgressDialog(tr("Uploading to puush"), tr("Cancel"), 0, 100, this);
    dia->setVisible(false);
    dia->setAutoReset(false);
    dia->setAutoClose(false);

    connect(net, SIGNAL(showProgress()), dia, SLOT(show()));
    connect(net, SIGNAL(hideProgress()), dia, SLOT(hide()));
    connect(net, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(uploadProgress(qint64,qint64)));

    loadSettings();
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
        if(ui->hideThis->isChecked() && isVisible())
            hide();

        QPixmap screenshot = QApplication::screens().first()->grabWindow(QApplication::desktop()->winId());
        if(ui->full_screen->isChecked())
            imageCaptured(screenshot);
        else
        {
            ScreenShotRestriction *rest = new ScreenShotRestriction(screenshot, this);
            rest->showFullScreen();
            connect(rest, SIGNAL(imageCaptured(QPixmap)), this, SLOT(imageCaptured(QPixmap)));
        }
        break;
    }
    default:
        break;
    }
}

void FluushOption::closeEvent(QCloseEvent *e)
{
    saveSettings();
    hide();
    e->ignore();
}

void FluushOption::loadSettings()
{
    QSettings set("Shiroy", "Fluush", this);
    ui->apiKey->setText(set.value("apiKey", "").toString());
    ui->full_screen->setChecked(set.value("fullScreen", false).toBool());
    ui->hideThis->setChecked(set.value("hideThis", true).toBool());
}

void FluushOption::saveSettings()
{
    QSettings set("Shiroy", "Fluush", this);
    set.setValue("apiKey", ui->apiKey->text());
    set.setValue("fullScreen", ui->full_screen->isChecked());
    set.setValue("hideThis", ui->hideThis->isChecked());
}

void FluushOption::quit()
{
    saveSettings();
    qApp->quit();
}

void FluushOption::imageCaptured(QPixmap p)
{
    QString savePath = QDir::tempPath() + "/" + QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss") + ".png";
    p.save(savePath);

    FluushRequestUpload *upRequest = new FluushRequestUpload(savePath, ui->apiKey->text(), net);
    net->sendMessage(upRequest);

    connect(upRequest, SIGNAL(uploadSuccess(QString)), this, SLOT(uploadComplete(QString)));
    connect(upRequest, SIGNAL(requestFailed(QString)), this, SLOT(requestError(QString)));
}

void FluushOption::uploadProgress(qint64 sent, qint64 total)
{
    dia->setMaximum(total);
    dia->setValue(sent);

    if(total == sent)
        dia->setLabelText(tr("Waiting for puush response"));
    else
        dia->setLabelText(tr("Sending to puush"));
}

void FluushOption::uploadComplete(const QString &url)
{
    trayIcon->showMessage(tr("Upload success"), url+tr("\nThis URL have been copied to the clipboard"));
    //ui->history->appendPlainText(url);
    QApplication::clipboard()->setText(url);
}

void FluushOption::requestError(const QString &msg)
{
    QMessageBox::warning(this, tr("Request faillure"), msg);
}

void FluushOption::showEvent(QShowEvent *e)
{
    Q_UNUSED(e)

    FluushRequestHistory *histRequest = new FluushRequestHistory(ui->apiKey->text(), net);
    net->sendMessage(histRequest);

    connect(histRequest, SIGNAL(FileListSent(QList<FluushFileInfo>&)), this, SLOT(FileListSent(QList<FluushFileInfo>&)));
    connect(histRequest, SIGNAL(requestFailed(QString)), this, SLOT(requestError(QString)));
}

void FluushOption::FileListSent(QList<FluushFileInfo> &list)
{
    QVBoxLayout *lay = ui->history;

    for(int i  = 0 ; i < lay->count() ; i++)
    {
        QWidget* it = lay->itemAt(i)->widget();
        lay->removeWidget(it);
        it->deleteLater();
    }

    for(QList<FluushFileInfo>::iterator i = list.begin() ; i != list.end() ; i++)
    {
        ThumbWidget *wid= new ThumbWidget(ui->apiKey->text(), (*i).id, (*i).url, (*i).name, net, this);
        lay->addWidget(wid);
    }
}
