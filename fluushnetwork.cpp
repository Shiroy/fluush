#include "fluushnetwork.h"

FluushNetwork::FluushNetwork(QObject *parent) : QObject(parent)
{
    m_netManager = new QNetworkAccessManager(this);
}

FluushNetwork::~FluushNetwork()
{

}

void FluushNetwork::sendMessage(FluushNetworkRequest *msg)
{
    QNetworkRequest req;
    QHttpMultiPart *postData = new QHttpMultiPart(QHttpMultiPart::FormDataType, msg);

    msg->Prepare(req, postData);

    QNetworkReply *rep = m_netManager->post(req, postData);

    emit showProgress();
    emit uploadProgress(0, 100);

    connect(rep, SIGNAL(finished()), msg, SLOT(finished()));
    connect(rep, SIGNAL(finished()), this, SIGNAL(hideProgress()));
    connect(rep, SIGNAL(uploadProgress(qint64,qint64)), this, SIGNAL(uploadProgress(qint64,qint64)));
}

