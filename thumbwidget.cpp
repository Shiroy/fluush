#include "thumbwidget.h"
#include "ui_thumbwidget.h"
#include "fluushrequestthumbnail.h"
#include <QFileInfo>
#include <QDir>
#include <QDesktopServices>

ThumbWidget::ThumbWidget(const QString &apiKey, const QString& id,const QString& url, const QString &name, FluushNetwork* const net, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThumbWidget),
    m_id(id),
    m_url(url),
    m_name(name),
    m_net(net), m_apiKey(apiKey)
{
    ui->setupUi(this);

    m_thumb_filename = QDir::tempPath() + "/thumb_" + m_id +".png";
    if(!QFileInfo(m_thumb_filename).exists())
    {
        FluushRequestThumbnail *thum = new FluushRequestThumbnail(m_id, m_apiKey, this);
        net->sendMessage(thum);
        connect(thum, SIGNAL(thumbAvailable()), this, SLOT(thumAvailable()));
    }
    else
    {
        ui->miniature->setText("");
        ui->miniature->setPixmap(QPixmap(m_thumb_filename));
    }

    ui->name->setText(name);
    ui->url->setText(url);
}

ThumbWidget::~ThumbWidget()
{
    delete ui;
}

void ThumbWidget::thumAvailable()
{
    m_thumb_filename = QDir::tempPath() + "/thumb_" + m_id +".png";
    if(QFileInfo(m_thumb_filename).exists())
    {
        ui->miniature->setText("");
        ui->miniature->setPixmap(QPixmap(m_thumb_filename));
    }
}

void ThumbWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    QDesktopServices::openUrl(QUrl(m_url));
}
