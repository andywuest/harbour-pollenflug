#include "frenchpollenbackend.h"
#include "genericpollen.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

FrenchPollenBackend::FrenchPollenBackend(QNetworkAccessManager *manager, QObject *parent)
    : AbstractBackend(manager, parent) {
    qDebug() << "Initializing French Pollen Backend...";

    addPollenData(Pollen::Mugwort, "Armoise", "armoise");
    addPollenData(Pollen::Birch, "Bouleau", "bouleau");
    addPollenData(Pollen::Alder, "Aulne", "aulne");
    addPollenData(Pollen::Grass, "Graminées", "graminees");
    addPollenData(Pollen::Hazel, "Noisetier", "noisetier");
    addPollenData(Pollen::Ambrosia, "Ambroisies", "ambroisie");
    addPollenData(Pollen::Hornbeam, "Charme", "charme");
    addPollenData(Pollen::Chestnut, "Châtaignier", "chataignier");
    addPollenData(Pollen::Oak, "Chêne", "chene");
    addPollenData(Pollen::Cypress, "Cupressacées", "cypres");
    addPollenData(Pollen::Olive, "Olivier", "olivier");
    addPollenData(Pollen::Sorrel, "Oseille", "oseille");
    addPollenData(Pollen::Poplar, "Peuplier", "peuplier");
    addPollenData(Pollen::Plantain, "Plantain", "plantain");
    addPollenData(Pollen::Plane, "Platane", "platane");
    addPollenData(Pollen::Willow, "Saule", "saule");
    addPollenData(Pollen::Lime, "Tilleul", "tilleul");
    addPollenData(Pollen::Nettle, "Urticacées", "parietaire");

    // TODO fix scaling
    // used for label
    this->pollutionIndexToLabelMap.insert("0", tr("no pollen exposure"));         // nul
    this->pollutionIndexToLabelMap.insert("1", tr("very small pollen exposure")); // très faible
    this->pollutionIndexToLabelMap.insert("2",
                                          tr("small pollen exposure")); // faible
    this->pollutionIndexToLabelMap.insert("3",
                                          tr("medium pollen exposure")); // moyen
    this->pollutionIndexToLabelMap.insert("4",
                                          tr("high pollen exposure"));           // élevé
    this->pollutionIndexToLabelMap.insert("5", tr("very high pollen exposure")); // très élevé

    // used for scale index
    this->pollutionIndexToIndexMap.insert("0", 0);
    this->pollutionIndexToIndexMap.insert("1", 1);
    this->pollutionIndexToIndexMap.insert("2", 2);
    this->pollutionIndexToIndexMap.insert("3", 3);
    this->pollutionIndexToIndexMap.insert("4", 4);
    this->pollutionIndexToIndexMap.insert("5", 5);
}

FrenchPollenBackend::~FrenchPollenBackend() {
    qDebug() << "Shutting down French Pollen Backend...";
}

void FrenchPollenBackend::fetchPollenData(const QList<int> &pollenIds, QString regionId, QString partRegionId) {
    qDebug() << "FrenchPollenBackend::fetchPollenData";
    qDebug() << pollenIds << " region : " << regionId << ", " << partRegionId;

    this->pollenIds = removeUnsupportedPollens(pollenIds);
    this->regionId = regionId;

    QNetworkReply *reply = executeGetRequest(QUrl(POLLEN_API_FRANCE));

    connect(reply,
            SIGNAL(error(QNetworkReply::NetworkError)),
            this,
            SLOT(handleRequestError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT(handleFetchPollenDataFinished()));
}

QString FrenchPollenBackend::parsePollenData(QByteArray searchReply) {
    qDebug() << "FrenchPollenBackend::parsePollenData";
    QJsonDocument jsonDocument = QJsonDocument::fromJson(searchReply);
    if (!jsonDocument.isObject()) {
        qDebug() << "not a json object!";
    }

    qDebug() << "region/partregion (requested): " << this->regionId;

    QJsonObject responseObject = jsonDocument.object();
    // the vigilanceMapCountries does provide a String that contains json data

    QJsonDocument countiesDocument = QJsonDocument::fromJson(
        responseObject.value("vigilanceMapCounties").toString().toUtf8());
    QJsonObject countyObject = countiesDocument.object().value(this->regionId).toObject();
    QJsonArray risks = countyObject.value("risks").toArray();

    QJsonDocument resultDocument;

    QJsonArray resultArray;

    QJsonObject resultObject;
    resultObject.insert("lastUpdate", "");   // TODO not supported
    resultObject.insert("nextUpdate", "");   // TODO not supported
    resultObject.insert("scaleElements", 6); // predefined
    resultObject.insert("maxDaysPrediction",
                        3);                        // predefined - only one day - but we show 3 anyway
    resultObject.insert("region", this->regionId); // dynamic from request
    resultObject.insert("partRegion", "-");        // not supported

    for (int i = 0; i < this->pollenIds.size(); i++) {
        int pollenId = this->pollenIds.at(i);
        QJsonObject pollenIdNode = getNodeForPollenId(risks, pollenId);
        // qDebug() << "found node : " << pollenIdNode;

        QJsonObject pollenResultObject;
        QSharedPointer<GenericPollen> pollenDataPointer = this->pollenIdToPollenData[pollenId];
        pollenResultObject.insert("label", pollenDataPointer->getPollenName(pollenId));
        pollenResultObject.insert("id", pollenId);
        pollenResultObject.insert("today", createResultPollenObject(pollenIdNode, QString("level")));
        // tomorrow / dayAfterTomorrow not supported
        const QString mapUrl = QString(MAP_URL_FRANCE).arg(pollenDataPointer->getPollenMapKey());
        pollenResultObject.insert("todayMapUrl", mapUrl);

        resultArray.push_back(pollenResultObject);
    }

    resultObject.insert("pollenData", resultArray);

    resultDocument.setObject(resultObject);
    QString dataToString(resultDocument.toJson());

    return dataToString;
}

QJsonObject FrenchPollenBackend::getNodeForPollenId(QJsonArray risksArray, int pollenId) {
    if (this->pollenIdToPollenData.contains(pollenId)) {
        QString key = this->pollenIdToPollenData[pollenId]->getJsonLookupKey();
        // qDebug() << " found value for key " << pollenId;

        foreach (const QJsonValue &riskNode, risksArray) {
            QString pollenName = riskNode.toObject().value("pollenName").toString();
            // qDebug() << "pollenname : " << pollenName;
            if (QString::compare(pollenName, key, Qt::CaseInsensitive) == 0) {
                return riskNode.toObject();
            }
        }
    }
    qDebug() << " error no value found found key " << pollenId;
    return QJsonObject();
}

QJsonObject FrenchPollenBackend::createResultPollenObject(QJsonObject pollenSourceNode, QString value) {
    QJsonObject jsonObject;
    int riskLevel = pollenSourceNode.value(value).toInt();
    QString riskLevelValue;
    riskLevelValue.setNum(riskLevel);
    jsonObject.insert("pollutionIndex", this->pollutionIndexToIndexMap[riskLevelValue]);
    jsonObject.insert("pollutionLabel", this->pollutionIndexToLabelMap[riskLevelValue]);
    return jsonObject;
}
