#ifndef FRENCHPOLLENBACKEND_H
#define FRENCHPOLLENBACKEND_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "constants.h"
#include "abstractpollen.h"

class FrenchPollenBackend : public QObject {
 Q_OBJECT
public:
    explicit  FrenchPollenBackend(QNetworkAccessManager *manager, QObject *parent = 0);
    ~FrenchPollenBackend();

    Q_INVOKABLE void fetchPollenData(const QList<int> &pollenIds, QString regionId, QString partRegionId);
    Q_INVOKABLE bool isPollenDataProvided(int pollenId);

    // signals for the qml part
    Q_SIGNAL void requestError(const QString &errorMessage);
    Q_SIGNAL void pollenDataAvailable(const QString &reply);

protected:

    QNetworkAccessManager *manager;

    QNetworkReply *executeGetRequest(const QUrl &url);

    void addPollenData(int pollenId, QString jsonLookupKey, QString pollenMapKey); // TODO generic base class

    QString parsePollenData(QByteArray searchReply); // TODO rename
    QJsonObject createResultPollenObject(QJsonObject pollenSourceNode, QString value);
    QList<int> removeUnsupportedPollens(const QList<int> &pollenIds);

private slots:
    void handleFetchPollenDataFinished();
    void handleRequestError(QNetworkReply::NetworkError error);

private:

    QMap<int, AbstractPollen> pollenIdToPollenData;
    QMap<int, QString> pollenIdToMapKey;
    QMap<int, QString> pollenIdToPollenNameMap;
    QMap<int, QString> pollenIdToLabelMap;
    QMap<QString, QString> pollutionIndexToLabelMap;
    QMap<QString, int> pollutionIndexToIndexMap;
    QList<int> pollenIds;
    QString regionId;

    QJsonObject getNodeForPollenId(QJsonArray risksArray, int pollenId);

#ifdef UNIT_TEST
    friend class FrenchPollenBackendTests;
#endif

};

#endif // FRENCHPOLLENBACKEND_H
