#include "germanpollenbackend.h"
#include "genericpollen.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

GermanPollenBackend::GermanPollenBackend(QNetworkAccessManager *manager, QObject *parent)
    : AbstractBackend(manager, parent) {
    qDebug() << "Initializing German Pollen Backend...";

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
    this->pollutionIndexToLabelMap.insert("0-1",
                                          tr("none to small pollen exposure")); // keine bis geringe Belastung
    this->pollutionIndexToLabelMap.insert("1", tr("small pollen exposure"));    // geringe Belastung
    this->pollutionIndexToLabelMap.insert("1-2",
                                          tr("small to medium pollen exposure")); // geringe bis mittlere Belastung
    this->pollutionIndexToLabelMap.insert("2", tr("medium pollen exposure"));     // mittlere Belastung
    this->pollutionIndexToLabelMap.insert("2-3",
                                          tr("medium to high pollen exposure")); // mittlere bis hohe Belastung
    this->pollutionIndexToLabelMap.insert("3", tr("high pollen exposure"));      // hohe Belastung

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

void GermanPollenBackend::fetchPollenData(const QList<int> &pollenIds, QString regionId, QString partRegionId) {
    qDebug() << "GermanPollenBackend::fetchPollenData";
    qDebug() << pollenIds;

    this->pollenIds = removeUnsupportedPollens(pollenIds);
    this->regionId = regionId.toInt();
    this->partRegionId = partRegionId.toInt();

    QNetworkReply *reply = executeGetRequest(QUrl(POLLEN_API_GERMANY));

    connect(reply,
            SIGNAL(error(QNetworkReply::NetworkError)),
            this,
            SLOT(handleRequestError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT(handleFetchPollenDataFinished()));
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

    QJsonArray resultArray;

    QJsonObject resultObject;
    resultObject.insert("lastUpdate", responseObject.value("last_update"));
    resultObject.insert("nextUpdate", responseObject.value("next_update"));
    resultObject.insert("scaleElements", 7);               // predefined
    resultObject.insert("maxDaysPrediction", 3);           // predefined
    resultObject.insert("region", this->regionId);         // dynamic from request
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
                pollenResultObject.insert("dayAfterTomorrow",
                                          createResultPollenObject(pollenIdNode, QString("dayafter_to")));
                const QString mapUrl = QString(MAP_URL_GERMANY).arg(pollenDataPointer->getPollenMapKey());
                pollenResultObject.insert("todayMapUrl", mapUrl);

                resultArray.push_back(pollenResultObject);
            }
        }
    }
    resultObject.insert("pollenData", resultArray);

    resultDocument.setObject(resultObject);
    QString dataToString(resultDocument.toJson());

    return dataToString;
}
