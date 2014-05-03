#ifndef THUMBWIDGET_H
#define THUMBWIDGET_H

#include <QWidget>
#include "fluushnetwork.h"
#include <QString>

namespace Ui {
class ThumbWidget;
}

class ThumbWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThumbWidget(const QString &apiKey, const QString& id, const QString& url, const QString &name, FluushNetwork * const net, QWidget *parent = 0);
    ~ThumbWidget();

    const QString& getId() const { return m_id; }
    const QString& getUrl() const { return m_url; }
    const QString& getName() const { return m_name; }

public slots:
    void thumAvailable();

private:
    Ui::ThumbWidget *ui;

    const QString &m_apiKey;
    QString m_id;
    QString m_url;
    QString m_name;
    FluushNetwork const *m_net;
    QString m_thumb_filename;
};

#endif // THUMBWIDGET_H
