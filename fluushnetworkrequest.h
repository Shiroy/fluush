#ifndef FLUUSHNETWORKREQUEST_H
#define FLUUSHNETWORKREQUEST_H

#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QNetworkReply>

class FluushNetworkRequest : public QObject
{
    Q_OBJECT
public:
    FluushNetworkRequest(bool progressShown, const QString& apiKey, QObject *parent = 0);
    virtual ~FluushNetworkRequest();

    virtual bool Prepare(QNetworkRequest &request, QHttpMultiPart *postData) = 0;
    virtual void ResponseReceived(QNetworkReply *reply) = 0;

    bool ProgressShown() const { return showProgress; }
    void SetProgressShown(bool shown) { showProgress = shown; }

signals:
    void requestFailed(const QString &msg);

public slots:
    void finished();

protected:
    QString m_apiKey;

    void postValue(QHttpPart &part, const QString& name, const QString& value);
    bool postFile(QHttpPart &part, const QString& name, const QString& filename);

private:
    void puushResponse(QNetworkReply *reply) { ResponseReceived(reply); }
    bool showProgress;
};

#endif // FLUUSHNETWORKREQUEST_H
