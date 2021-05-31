#ifndef GERMAN_POLLEN_BACKEND_H
#define GERMAN_POLLEN_BACKEND_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QSequentialIterable>

#include "constants.h"
#include "abstractpollen.h"

// TODo extend abstract pollenbackend -> tests !!
class GermanPollenBackend : public QObject {
    Q_OBJECT
public:
    explicit  GermanPollenBackend(QNetworkAccessManager *manager, QObject *parent = 0);
    ~GermanPollenBackend();

    Q_INVOKABLE void fetchPollenData(const QList<int> &pollenIds, QString regionId, QString partRegionId);
    Q_INVOKABLE bool isPollenDataProvided(int pollenId);

    // signals for the qml part
    Q_SIGNAL void requestError(const QString &errorMessage);
    Q_SIGNAL void pollenDataAvailable(const QString &reply);

private:

    QMap<int, AbstractPollen> pollenIdToPollenData;
    QMap<int, QString> pollenIdToMapKey;
    QMap<int, QString> pollenIdToKeyMap;
    QMap<int, QString> pollenIdToLabelMap;
    QMap<QString, QString> pollutionIndexToLabelMap;
    QMap<QString, int> pollutionIndexToIndexMap;
    QList<int> pollenIds;
    int regionId;
    int partRegionId;

    bool isRegionNodeFound(int regionId, int partRegionId);
    QJsonObject getNodeForPollenId(QJsonObject pollenNode, int pollenId);

protected:

    QNetworkAccessManager *manager;

    QNetworkReply *executeGetRequest(const QUrl &url);

    void addPollenData(int pollenId, QString jsonLookupKey, QString pollenMapKey); // TODO generic base class

    QString parsePollenData(QByteArray searchReply); // TODO rename
    QJsonObject createResultPollenObject(QJsonObject pollenSourceNode, QString dayString);

private slots:
    void handleFetchPollenDataFinished();
    void handleRequestError(QNetworkReply::NetworkError error);

};

#endif // GERMAN_POLLEN_BACKEND_H
