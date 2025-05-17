#ifndef ABSTRACT_BACKEND_H
#define ABSTRACT_BACKEND_H

#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QSharedPointer>

#include "genericpollen.h"

class AbstractBackend : public QObject {
    Q_OBJECT

public:
    explicit AbstractBackend(QNetworkAccessManager *manager, QObject *parent);
    ~AbstractBackend() override;

    Q_INVOKABLE QString getPollenName(int pollenId);
    Q_INVOKABLE QString getPollenImageName(int pollenId);
    Q_INVOKABLE bool isPollenDataProvided(int pollenId);

    // signals for the qml part
    Q_SIGNAL void requestError(const QString &errorMessage);
    Q_SIGNAL void pollenDataAvailable(const QString &reply);

protected slots:
    void handleRequestError(QNetworkReply::NetworkError error);
    void handleFetchPollenDataFinished();
    QList<int> removeUnsupportedPollens(const QList<int> &pollenIds);

protected:
    QNetworkAccessManager *manager;
    QMap<int, QSharedPointer<GenericPollen>> pollenIdToPollenData;

    QMap<QString, QString> pollutionIndexToLabelMap;
    QMap<QString, int> pollutionIndexToIndexMap;

    QList<int> pollenIds;

    QNetworkReply *executeGetRequest(const QUrl &url);
    virtual QString parsePollenData(QByteArray searchReply, QNetworkReply *reply) = 0;
    void addPollenData(int pollenId, const QString &jsonLookupKey, const QString &pollenMapKey);
};

#endif // ABSTRACT_BACKEND_H
