#ifndef FLUUSHREQUESTTHUMBNAIL_H
#define FLUUSHREQUESTTHUMBNAIL_H

#include "fluushnetworkrequest.h"

class FluushRequestThumbnail : public FluushNetworkRequest
{
    Q_OBJECT
public:
    explicit FluushRequestThumbnail(const QString &id, const QString& apiKey, QObject *parent = 0);

    bool Prepare(QNetworkRequest &request, QHttpMultiPart *postData);
    void ResponseReceived(QNetworkReply *rep);

signals:
    void thumbAvailable();

public slots:

private:
    QString m_id;

};

#endif // FLUUSHREQUESTTHUMBNAIL_H
