#ifndef FLUUSHNETWORK_H
#define FLUUSHNETWORK_H

#include <QNetworkAccessManager>
#include "fluushnetworkrequest.h"

class FluushNetwork : public QObject
{
    Q_OBJECT
public:
    FluushNetwork(QObject *parent = 0);
    ~FluushNetwork();

    void sendMessage(FluushNetworkRequest *msg);

signals:
    void showProgress();
    void uploadProgress(qint64, qint64);
    void hideProgress();

private:

    QNetworkAccessManager *m_netManager;
};

#endif // FLUUSHNETWORK_H
