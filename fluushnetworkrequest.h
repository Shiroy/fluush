#ifndef FLUUSHNETWORKREQUEST_H
#define FLUUSHNETWORKREQUEST_H

#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QNetworkReply>

class FluushNetworkRequest : public QObject
{
    Q_OBJECT
public:
    FluushNetworkRequest(const QString& apiKey, QObject *parent = 0);
    virtual ~FluushNetworkRequest();

    virtual bool Prepare(QNetworkRequest &request, QHttpMultiPart *postData) = 0;
    virtual void ResponseReceived(QNetworkReply *reply) = 0;

signals:
    void requestFailed(const QString &msg);

public slots:
    void finished();

protected:
    QString m_apiKey;

private:
    void puushResponse(QNetworkReply *reply) { ResponseReceived(reply); }
};

#endif // FLUUSHNETWORKREQUEST_H
