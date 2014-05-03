#include "fluushrequestthumbnail.h"
#include <QPixmap>
#include <QDir>

FluushRequestThumbnail::FluushRequestThumbnail(const QString& id, const QString &apiKey, QObject *parent) :
    FluushNetworkRequest(false, apiKey, parent), m_id(id)
{
}

bool FluushRequestThumbnail::Prepare(QNetworkRequest &request, QHttpMultiPart *postData)
{
    request.setUrl(QUrl("https://puush.me/api/thumb"));

    QHttpPart api;
    postValue(api, "k", m_apiKey);

    QHttpPart i;
    postValue(i, "i", m_id);

    postData->append(api);
    postData->append(i);

    return true;
}

void FluushRequestThumbnail::ResponseReceived(QNetworkReply *rep)
{
    QByteArray data = rep->readAll();

    if(data.isEmpty())
        return;

    QString savePath = QDir::tempPath() + "/thumb_" + m_id +".png";

    QFile f(savePath);
    if(!f.open(QIODevice::WriteOnly))
        return;

    f.write(data);

    emit thumbAvailable();
}
