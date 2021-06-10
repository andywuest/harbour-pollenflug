#include "germanpollenbackend.h"
#include "genericpollen.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

GermanPollenBackend::GermanPollenBackend(QNetworkAccessManager *manager, QObject *parent) : QObject(parent) {
    qDebug() << "Initializing German Pollen Backend...";
    this->manager = manager;

    addPollenData(Pollen::Mugwort, "Beifuss", "5");
    addPollenData(Pollen::Birch, "Birke", "2");
    addPollenData(Pollen::Alder, "Erle", "1");
    addPollenData(Pollen::AshTree, "Esche", "7");
    addPollenData(Pollen::Grass, "Graeser", "3");
    addPollenData(Pollen::Hazel, "Hasel", "0");
    addPollenData(Pollen::Ambrosia, "Ambrosia", "6");
    addPollenData(Pollen::Rye, "Roggen", "4");

    // used for label
    this->pollutionIndexToLabelMap.insert("0", tr("no pollen exposure")); // keine Belastung
    this->pollutionIndexToLabelMap.insert("0-1", tr("none to small pollen exposure")); // keine bis geringe Belastung
    this->pollutionIndexToLabelMap.insert("1", tr("small pollen exposure")); // geringe Belastung
    this->pollutionIndexToLabelMap.insert("1-2", tr("small to medium pollen exposure")); // geringe bis mittlere Belastung
    this->pollutionIndexToLabelMap.insert("2", tr("medium pollen exposure")); // mittlere Belastung
    this->pollutionIndexToLabelMap.insert("2-3", tr("medium to high pollen exposure")); // mittlere bis hohe Belastung
    this->pollutionIndexToLabelMap.insert("3", tr("high pollen exposure")); // hohe Belastung

    // used for scale index
    this->pollutionIndexToIndexMap.insert("-1", -1);
    this->pollutionIndexToIndexMap.insert("0", 0);
    this->pollutionIndexToIndexMap.insert("0-1", 1);
    this->pollutionIndexToIndexMap.insert("1", 2);
    this->pollutionIndexToIndexMap.insert("1-2", 3);
    this->pollutionIndexToIndexMap.insert("2", 4);
    this->pollutionIndexToIndexMap.insert("2-3", 5);
    this->pollutionIndexToIndexMap.insert("3", 6);
}

GermanPollenBackend::~GermanPollenBackend() {
    qDebug() << "Shutting down German Pollen Backend...";
}

void GermanPollenBackend::addPollenData(int pollenId, QString jsonLookupKey, QString pollenMapKey) {
    QSharedPointer<GenericPollen> pointer (new GenericPollen(pollenId, jsonLookupKey, pollenMapKey));
    this->pollenIdToPollenData.insert(pollenId, pointer);
    // this->pollenIdToPollenData.insert(pollenId, new GenericPollen(pollenId, jsonLookupKey, pollenMapKey));
}

QNetworkReply *GermanPollenBackend::executeGetRequest(const QUrl &url) {
    qDebug() << "GermanPollenBackend::executeGetRequest " << url;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, MIME_TYPE_JSON);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);

    return manager->get(request);
}

void GermanPollenBackend::handleRequestError(QNetworkReply::NetworkError error) {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    qWarning() << "GermanPollenBackend::handleRequestError:" << static_cast<int>(error) << reply->errorString() << reply->readAll();

    emit requestError("Return code: " + QString::number(static_cast<int>(error)) + " - " + reply->errorString());
}

void GermanPollenBackend::fetchPollenData(const QList<int> &pollenIds, QString regionId, QString partRegionId) {
    qDebug() << "GermanPollenBackend::fetchPollenData";
    qDebug() << pollenIds;

    this->pollenIds = pollenIds;
    this->regionId = regionId.toInt();
    this->partRegionId = partRegionId.toInt();

    QNetworkReply *reply = executeGetRequest(QUrl(POLLEN_API_GERMANY));

    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(handleRequestError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT(handleFetchPollenDataFinished()));
}

void GermanPollenBackend::handleFetchPollenDataFinished() {
    qDebug() << "GermanPollenBackend::handleFetchPollenDataFinished";

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    reply->deleteLater();
    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    emit pollenDataAvailable(parsePollenData(reply->readAll()));
}

bool GermanPollenBackend::isRegionNodeFound(int regionId, int partRegionId) {
    if (this->regionId == regionId && this->partRegionId == partRegionId) {
        qDebug() << "FOUND region/partregion: " << regionId << "/" << partRegionId;
        return true;
    }
    return false;
}

QJsonObject GermanPollenBackend::getNodeForPollenId(QJsonObject pollenNode, int pollenId) {
    if (this->pollenIdToPollenData.contains(pollenId)) {
        QString key = this->pollenIdToPollenData[pollenId]->getJsonLookupKey();
        qDebug() << " found value for key " << pollenId;
        return pollenNode.value(key).toObject();
    }
    qDebug() << " error no value found found key " << pollenId;
    return QJsonObject();
}

QJsonObject GermanPollenBackend::createResultPollenObject(QJsonObject pollenSourceNode, QString dayString) {
    QJsonObject jsonObject;
    jsonObject.insert("pollutionIndex", this->pollutionIndexToIndexMap[pollenSourceNode.value(dayString).toString()]);
    jsonObject.insert("pollutionLabel", this->pollutionIndexToLabelMap[pollenSourceNode.value(dayString).toString()]);
    return jsonObject;
}

QString GermanPollenBackend::parsePollenData(QByteArray searchReply) {
    qDebug() << "GermanPollenBackend::parsePollenData";
    QJsonDocument jsonDocument = QJsonDocument::fromJson(searchReply);
    if (!jsonDocument.isObject()) {
        qDebug() << "not a json object!";
    }

    QJsonObject responseObject = jsonDocument.object();
    QJsonDocument resultDocument;
    QJsonArray contentArray;

    QJsonArray resultArray;

    QJsonObject resultObject;
    resultObject.insert("lastUpdate", responseObject.value("last_update"));
    resultObject.insert("nextUpdate", responseObject.value("next_update"));
    resultObject.insert("scaleElements", 7); // predefined
    resultObject.insert("maxDaysPrediction", 3); // predefined
    resultObject.insert("region", this->regionId); // dynamic from request
    resultObject.insert("partRegion", this->partRegionId); // dynamic from request

    QJsonArray responseContentArray = responseObject.value("content").toArray();

    qDebug() << "region/partregion (requested): " << this->regionId << "/" << this->partRegionId;

    foreach (const QJsonValue &value, responseContentArray) {
         QJsonObject rootObject = value.toObject();
         int regionId = rootObject.value("region_id").toInt();
         int partRegionId = rootObject.value("partregion_id").toInt();

         if (isRegionNodeFound(regionId, partRegionId) == true) {
             QJsonObject responsePollenObject = rootObject.value("Pollen").toObject();

             for (int i = 0; i < this->pollenIds.size(); i++) {
                 int pollenId = this->pollenIds.at(i);
                 QJsonObject pollenIdNode = getNodeForPollenId(responsePollenObject, pollenId);

                 QJsonObject pollenResultObject;
                 QSharedPointer<GenericPollen> pollenDataPointer = this->pollenIdToPollenData[pollenId];
                 pollenResultObject.insert("label", pollenDataPointer->getPollenName(pollenId));
                 pollenResultObject.insert("id", pollenId);
                 pollenResultObject.insert("today", createResultPollenObject(pollenIdNode, QString("today")));
                 pollenResultObject.insert("tomorrow", createResultPollenObject(pollenIdNode, QString("tomorrow")));
                 pollenResultObject.insert("dayAfterTomorrow", createResultPollenObject(pollenIdNode, QString("dayafter_to")));
                 const QString mapUrl = QString(MAP_URL_GERMANY).arg(pollenDataPointer->getPollenMapKey());
                 pollenResultObject.insert("todayMapUrl" , mapUrl);

                 resultArray.push_back(pollenResultObject);
             }
         }
    }
    resultObject.insert("pollenData", resultArray);

    resultDocument.setObject(resultObject);
    QString dataToString(resultDocument.toJson());

    return dataToString;
}

QString GermanPollenBackend::getPollenName(int pollenId) {
    // TODO call static method??
    return this->pollenIdToPollenData[pollenId]->getPollenName(pollenId);
}

QString GermanPollenBackend::getPollenImageName(int pollenId) {
    // TODO call static method??
    return this->pollenIdToPollenData[pollenId]->getPollenImageFileName(pollenId);
}

bool GermanPollenBackend::isPollenDataProvided(int pollenId) {
    // TODO for some reason the map contains an entry for a not supported pollenId with
    // a null value
    return this->pollenIdToPollenData.contains(pollenId) && this->pollenIdToPollenData[pollenId] != nullptr;
}
