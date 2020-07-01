#ifndef GERMANPOLLENBACKEND_H
#define GERMANPOLLENBACKEND_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "constants.h"

class GermanPollenBackend : public QObject {
    Q_OBJECT
public:
    explicit  GermanPollenBackend(QNetworkAccessManager *manager, QObject *parent = 0);
    ~GermanPollenBackend();

    Q_INVOKABLE void fetchPollenData();

    // signals for the qml part
    Q_SIGNAL void requestError(const QString &errorMessage);
    Q_SIGNAL void pollenDataAvailable(const QString &reply);

protected:

    QString applicationName;
    QString applicationVersion;
    QNetworkAccessManager *manager;

    QNetworkReply *executeGetRequest(const QUrl &url);

private slots:
    void handleFetchPollenDataFinished();
    void handleRequestError(QNetworkReply::NetworkError error);

};

#endif // GERMANPOLLENBACKEND_H
