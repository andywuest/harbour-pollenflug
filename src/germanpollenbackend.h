#ifndef GERMAN_POLLEN_BACKEND_H
#define GERMAN_POLLEN_BACKEND_H

#include <QObject>
#include <QNetworkReply>
#include <QSharedPointer>
#include <QMap>
#include <QNetworkAccessManager>
#include <QSequentialIterable>

#include "constants.h"
#include "abstractpollen.h"
#include "genericpollen.h"

// TODo extend abstract pollenbackend -> tests !!
class GermanPollenBackend : public QObject {
    Q_OBJECT
public:
    explicit  GermanPollenBackend(QNetworkAccessManager *manager, QObject *parent = nullptr);
    ~GermanPollenBackend();

    Q_INVOKABLE void fetchPollenData(const QList<int> &pollenIds, QString regionId, QString partRegionId);
    Q_INVOKABLE bool isPollenDataProvided(int pollenId);

    // signals for the qml part
    Q_SIGNAL void requestError(const QString &errorMessage);
    Q_SIGNAL void pollenDataAvailable(const QString &reply);

private:

    QMap<int, QSharedPointer<GenericPollen>> pollenIdToPollenData; // TODO move to baseclass
    QMap<QString, QString> pollutionIndexToLabelMap;
    QMap<QString, int> pollutionIndexToIndexMap;
    QList<int> pollenIds;
    int regionId;
    int partRegionId;

    bool isRegionNodeFound(int regionId, int partRegionId);
    QJsonObject getNodeForPollenId(QJsonObject pollenNode, int pollenId);

protected:

    QNetworkAccessManager *manager; // TODO obsoelt

    QNetworkReply *executeGetRequest(const QUrl &url); // TODO baseclass

    void addPollenData(int pollenId, QString jsonLookupKey, QString pollenMapKey); // TODO generic base class

    QString parsePollenData(QByteArray searchReply); // TODO rename
    QJsonObject createResultPollenObject(QJsonObject pollenSourceNode, QString dayString);

private slots:
    void handleFetchPollenDataFinished(); // virtual?
    void handleRequestError(QNetworkReply::NetworkError error); // TDODo generic base class

};

#endif // GERMAN_POLLEN_BACKEND_H
