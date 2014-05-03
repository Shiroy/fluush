#include "fluushrequesthistory.h"
#include <QNetworkRequest>
#include <QHttpMultiPart>

FluushRequestHistory::FluushRequestHistory(const QString &apiKey, QObject *parent) : FluushNetworkRequest(false, apiKey, parent)
{
}

bool FluushRequestHistory::Prepare(QNetworkRequest &request, QHttpMultiPart *postData)
{
    request.setUrl(QUrl("https://puush.me/api/hist"));
    QHttpPart apiKey;
    postValue(apiKey, "k", m_apiKey);

    postData->append(apiKey);

    return true;
}

void FluushRequestHistory::ResponseReceived(QNetworkReply *rep)
{
    QString repStr = rep->readAll();

    QStringList lines = repStr.split("\n", QString::SkipEmptyParts);

    if(lines.first() != "0")
    {
        emit requestFailed(tr("Error while recovering history, check your api key\n") + repStr);
        return;
    }

    QList<FluushFileInfo> listFiles;

    for(int i = 1 ; i < lines.size() ; i++)
    {
        FluushFileInfo finfo;
        QString currentFile = lines[i];
        QStringList fileDetails = currentFile.split(",");

        finfo.id = fileDetails[0];
        finfo.name = fileDetails[3];
        finfo.url = fileDetails[2];

        listFiles.append(finfo);
    }

    emit FileListSent(listFiles);
}
