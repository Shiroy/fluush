#include "fluushnetworkrequest.h"
#include <QHttpPart>
#include <QString>
#include <QFile>

FluushNetworkRequest::FluushNetworkRequest(bool progressShown, const QString& apiKey, QObject *parent) : m_apiKey(apiKey), QObject(parent), showProgress(progressShown)
{
}

FluushNetworkRequest::~FluushNetworkRequest()
{

}

void FluushNetworkRequest::finished()
{
    QNetworkReply *response = qobject_cast<QNetworkReply*>(sender());
    if(!response)
        return;

    ResponseReceived(response);

    deleteLater();
}

void FluushNetworkRequest::postValue(QHttpPart &part, const QString &name, const QString &value)
{
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + name + "\""));
    part.setBody(QByteArray().append(value));
}

bool FluushNetworkRequest::postFile(QHttpPart &part, const QString &name, const QString &filename)
{
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + name + "\"; filename=\""+ filename + "\""));
    part.setHeader(QNetworkRequest::ContentTypeHeader, "image/png"); //For now, only png files can be uploaded

    QFile *file = new QFile(filename, this);
    if(!file->open(QIODevice::ReadOnly))
    {
        delete file;
        return false;
    }

    part.setBodyDevice(file);

    return true;
}
