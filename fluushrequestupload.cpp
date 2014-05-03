#include "fluushrequestupload.h"
#include <QFile>

FluushRequestUpload::FluushRequestUpload(const QString& file, const QString &apiKey, QObject *parent) : FluushNetworkRequest(true, apiKey, parent), fileToUpload(file)
{
    SetProgressShown(true);
}

bool FluushRequestUpload::Prepare(QNetworkRequest &request, QHttpMultiPart *postData)
{
    request.setUrl(QUrl("https://puush.me/api/up"));

    QHttpPart apiKey;
    postValue(apiKey, "k", m_apiKey);

    QHttpPart poop;
    postValue(poop, "z", "poop");

    QHttpPart image;
    if(!postFile(image, "f", fileToUpload))
        return false;

    postData->append(apiKey);
    postData->append(poop);
    postData->append(image);

    return true;
}

void FluushRequestUpload::ResponseReceived(QNetworkReply *rep)
{
    QString repStr = rep->readAll();

    QStringList repElement = repStr.split(",");
    if(repElement[0] != "0")
        emit requestFailed(tr("Error while uploading") + repStr); //Todo : Check what errors codes mean
    else
        emit uploadSuccess(repElement[1]);

    deleteLater();
}
