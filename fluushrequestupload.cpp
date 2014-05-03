#include "fluushrequestupload.h"
#include <QFile>

FluushRequestUpload::FluushRequestUpload(const QString& file, const QString &apiKey, QObject *parent) : FluushNetworkRequest(apiKey, parent), fileToUpload(file)
{
}



bool FluushRequestUpload::Prepare(QNetworkRequest &request, QHttpMultiPart *postData)
{
    request.setUrl(QUrl("https://puush.me/api/up"));

    QHttpPart apiKey;
    apiKey.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"k\""));
    apiKey.setBody(QByteArray().append(m_apiKey));
    qDebug("Api KEY : %s", m_apiKey.toStdString().c_str());

    QHttpPart poop;
    poop.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"z\""));
    poop.setBody("poop");

    QHttpPart image;
    image.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"f\"; filename=\""+ fileToUpload + "\""));
    qDebug("Uploading : %s", fileToUpload.toStdString().c_str());
    image.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");

    QFile *f = new QFile(fileToUpload, this);
    if(!f->open(QIODevice::ReadOnly))
    {
        delete f;
        return false;
    }
    image.setBodyDevice(f);


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
