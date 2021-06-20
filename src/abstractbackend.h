#ifndef ABSTRACT_BACKEND_H
#define ABSTRACT_BACKEND_H

#include <QObject>
#include <QSharedPointer>
#include <QMap>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "genericpollen.h"

class AbstractBackend : public QObject {
    Q_OBJECT

public:
    explicit AbstractBackend(QNetworkAccessManager *manager, QObject *parent);
    ~AbstractBackend();

    Q_INVOKABLE QString getPollenName(int pollenId);
    Q_INVOKABLE QString getPollenImageName(int pollenId);
    Q_INVOKABLE bool isPollenDataProvided(int pollenId);

    // signals for the qml part
    Q_SIGNAL void requestError(const QString &errorMessage);
    Q_SIGNAL void pollenDataAvailable(const QString &reply);

protected slots:
    void handleRequestError(QNetworkReply::NetworkError error);
    QList<int> removeUnsupportedPollens(const QList<int> &pollenIds);

protected:
    QNetworkAccessManager *manager;
    QMap<int, QSharedPointer<GenericPollen>> pollenIdToPollenData;

    QMap<QString, QString> pollutionIndexToLabelMap;
    QMap<QString, int> pollutionIndexToIndexMap;

    QList<int> pollenIds;

    QNetworkReply *executeGetRequest(const QUrl &url);
    void addPollenData(int pollenId, QString jsonLookupKey, QString pollenMapKey);

};

#endif // ABSTRACT_BACKEND_H
