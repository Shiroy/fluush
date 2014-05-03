#ifndef FLUUSHREQUESTHISTORY_H
#define FLUUSHREQUESTHISTORY_H

#include "fluushnetworkrequest.h"
#include <QString>
#include <QList>

struct FluushFileInfo
{
    QString id;
    QString name;
    QString url;
};

class FluushRequestHistory : public FluushNetworkRequest
{
    Q_OBJECT
public:
    FluushRequestHistory(const QString& apiKey, QObject* parent = 0);

    bool Prepare(QNetworkRequest &request, QHttpMultiPart *postData) override;
    void ResponseReceived(QNetworkReply *rep) override;

signals:
    void FileListSent(QList<FluushFileInfo>& list);
};

#endif // FLUUSHREQUESTHISTORY_H
