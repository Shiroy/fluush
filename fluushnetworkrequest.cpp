#include "fluushnetworkrequest.h"

FluushNetworkRequest::FluushNetworkRequest(const QString& apiKey, QObject *parent) : m_apiKey(apiKey), QObject(parent)
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
}
