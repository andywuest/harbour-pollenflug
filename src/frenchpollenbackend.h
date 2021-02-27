#ifndef FRENCHPOLLENBACKEND_H
#define FRENCHPOLLENBACKEND_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "constants.h"

class FrenchPollenBackend : public QObject {
 Q_OBJECT
public:
    explicit  FrenchPollenBackend(QNetworkAccessManager *manager, QObject *parent = 0);
    ~FrenchPollenBackend();

    Q_INVOKABLE void fetchPollenData(const QList<int> &pollenIds, int regionId, int partRegionId);

    // signals for the qml part
    Q_SIGNAL void requestError(const QString &errorMessage);
    Q_SIGNAL void pollenDataAvailable(const QString &reply);

protected:

    QNetworkAccessManager *manager;

    QNetworkReply *executeGetRequest(const QUrl &url);

    QString parsePollenData(QByteArray searchReply); // TODO rename
    QJsonObject createResultPollenObject(QJsonObject pollenSourceNode, QString dayString);

private slots:
    void handleFetchPollenDataFinished();
    void handleRequestError(QNetworkReply::NetworkError error);

#ifdef UNIT_TEST
    friend class FrenchPollenBackendTests;
#endif

};

#endif // FRENCHPOLLENBACKEND_H
