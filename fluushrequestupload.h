#ifndef FLUUSHREQUESTUPLOAD_H
#define FLUUSHREQUESTUPLOAD_H

#include "fluushnetworkrequest.h"

class FluushRequestUpload : public FluushNetworkRequest
{
    Q_OBJECT
    QString fileToUpload;

public:
    FluushRequestUpload(const QString &file, const QString &apiKey, QObject *parent = 0);

    bool Prepare(QNetworkRequest &request, QHttpMultiPart *postData) override;
    void ResponseReceived(QNetworkReply *rep) override;

signals:
    void uploadSuccess(const QString &url);
};

#endif // FLUUSHREQUESTUPLOAD_H
