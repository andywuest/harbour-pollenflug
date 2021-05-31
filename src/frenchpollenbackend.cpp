#include "frenchpollenbackend.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

FrenchPollenBackend::FrenchPollenBackend(QNetworkAccessManager *manager, QObject *parent) : QObject(parent) {
    qDebug() << "Initializing French Pollen Backend...";
    this->manager = manager;

    // mapping for map
    this->pollenIdToMapKey.insert(Pollen::Mugwort, "armoise");
    this->pollenIdToMapKey.insert(Pollen::Birch, "bouleau");
    this->pollenIdToMapKey.insert(Pollen::Alder, "aulne");
    // this->pollenIdToMapKey.insert(Pollen::AshTree, "7");
    this->pollenIdToMapKey.insert(Pollen::Grass, "graminees");
    this->pollenIdToMapKey.insert(Pollen::Hazel, "noisetier");
    this->pollenIdToMapKey.insert(Pollen::Ambrosia, "ambroisie");
    // this->pollenIdToMapKey.insert(Pollen::Rye, "4");
    this->pollenIdToMapKey.insert(Pollen::Hornbeam, "charme");
    this->pollenIdToMapKey.insert(Pollen::Chestnut, "chataignier");
    this->pollenIdToMapKey.insert(Pollen::Oak, "chene");
    this->pollenIdToMapKey.insert(Pollen::Cypress, "cypres");
    this->pollenIdToMapKey.insert(Pollen::Olive, "olivier");
    this->pollenIdToMapKey.insert(Pollen::Sorrel, "oseille");
    this->pollenIdToMapKey.insert(Pollen::Poplar, "peuplier");
    this->pollenIdToMapKey.insert(Pollen::Plantain, "plantain");
    this->pollenIdToMapKey.insert(Pollen::Plane, "platane");
    this->pollenIdToMapKey.insert(Pollen::Willow, "saule");
    this->pollenIdToMapKey.insert(Pollen::Lime, "tilleul");
    this->pollenIdToMapKey.insert(Pollen::Nettle, "parietaire");

    // internally used in json object lookup
    this->pollenIdToPollenNameMap.insert(Pollen::Mugwort, "Armoise");
    this->pollenIdToPollenNameMap.insert(Pollen::Birch, "Bouleau");
    this->pollenIdToPollenNameMap.insert(Pollen::Alder, "Aulne");
    // this->pollenIdToPollenNameMap.insert(4, "Esche"); ?? TODO
    this->pollenIdToPollenNameMap.insert(Pollen::Grass, "Graminées");
    this->pollenIdToPollenNameMap.insert(Pollen::Hazel, "Noisetier");
    this->pollenIdToPollenNameMap.insert(Pollen::Ambrosia, "Ambroisies");
    // this->pollenIdToPollenNameMap.insert(8, "Roggen"); ?? TODO

    // TODO fix from here
    this->pollenIdToPollenNameMap.insert(Pollen::Hornbeam, "Charme");
    this->pollenIdToPollenNameMap.insert(Pollen::Chestnut, "Châtaignier");
    this->pollenIdToPollenNameMap.insert(Pollen::Oak, "Chêne");
    this->pollenIdToPollenNameMap.insert(Pollen::Cypress, "Cupressacées");
    this->pollenIdToPollenNameMap.insert(Pollen::Olive, "Olivier");
    this->pollenIdToPollenNameMap.insert(Pollen::Sorrel, "Oseille");
    this->pollenIdToPollenNameMap.insert(Pollen::Poplar, "Peuplier");
    this->pollenIdToPollenNameMap.insert(Pollen::Plantain, "Plantain");
    this->pollenIdToPollenNameMap.insert(Pollen::Plane, "Platane");
    this->pollenIdToPollenNameMap.insert(Pollen::Willow, "Saule");
    this->pollenIdToPollenNameMap.insert(Pollen::Lime, "Tilleul");
    this->pollenIdToPollenNameMap.insert(Pollen::Nettle, "Urticacées");

    // TODO english
    this->pollenIdToLabelMap.insert(Pollen::Mugwort, tr("Mugwort")); // Beifuss
    this->pollenIdToLabelMap.insert(Pollen::Birch, tr("Birch")); // Birke
    this->pollenIdToLabelMap.insert(Pollen::Alder, tr("Alder")); // Erle
    // this->pollenIdToLabelMap.insert(4, tr("Ash Tree")); // Esche
    this->pollenIdToLabelMap.insert(Pollen::Grass, tr("Grass")); // Gräser
    this->pollenIdToLabelMap.insert(Pollen::Hazel, tr("Hazel")); // Hasel
    this->pollenIdToLabelMap.insert(Pollen::Ambrosia, tr("Ambrosia")); // Ambrosia
    // this->pollenIdToLabelMap.insert(8, tr("Rye")); // Roggen ?? TODO
    this->pollenIdToLabelMap.insert(Pollen::Hornbeam, tr("Hornbeam")); // Ambrosia
    this->pollenIdToLabelMap.insert(Pollen::Chestnut, tr("Chestnut")); // Ambrosia
    this->pollenIdToLabelMap.insert(Pollen::Oak, tr("Oak")); // Ambrosia
    this->pollenIdToLabelMap.insert(Pollen::Cypress, tr("Cypress")); // Ambrosia
    this->pollenIdToLabelMap.insert(Pollen::Olive, tr("Olive")); // Ambrosia
    this->pollenIdToLabelMap.insert(Pollen::Sorrel, tr("Sorrel")); // Ambrosia
    this->pollenIdToLabelMap.insert(Pollen::Poplar, tr("Poplar")); // Ambrosia
    this->pollenIdToLabelMap.insert(Pollen::Plantain, tr("Plantain")); // Ambrosia
    this->pollenIdToLabelMap.insert(Pollen::Plane, tr("Plane")); // Ambrosia
    this->pollenIdToLabelMap.insert(Pollen::Willow, tr("Willow")); // Ambrosia
    this->pollenIdToLabelMap.insert(Pollen::Lime, tr("Lime")); // Ambrosia
    this->pollenIdToLabelMap.insert(Pollen::Nettle, tr("Nettle")); // Ambrosia

    // TODO fix scaling
    // used for label
    this->pollutionIndexToLabelMap.insert("0", tr("no pollen exposure")); // nul
    this->pollutionIndexToLabelMap.insert("1", tr("very small pollen exposure")); // très faible
    this->pollutionIndexToLabelMap.insert("2", tr("small pollen exposure")); // faible
    this->pollutionIndexToLabelMap.insert("3", tr("medium pollen exposure")); // moyen
    this->pollutionIndexToLabelMap.insert("4", tr("high pollen exposure")); // élevé
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

QNetworkReply *FrenchPollenBackend::executeGetRequest(const QUrl &url) {
    qDebug() << "FrenchPollenBackend::executeGetRequest " << url;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, MIME_TYPE_JSON);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);

    return manager->get(request);
}

void FrenchPollenBackend::handleRequestError(QNetworkReply::NetworkError error) {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    qWarning() << "AbstractDataBackend::handleRequestError:" << static_cast<int>(error) << reply->errorString() << reply->readAll();

    emit requestError("Return code: " + QString::number(static_cast<int>(error)) + " - " + reply->errorString());
}

void FrenchPollenBackend::fetchPollenData(const QList<int> &pollenIds, QString regionId, QString partRegionId) {
    qDebug() << "FrenchPollenBackend::fetchPollenData";
    qDebug() << pollenIds << " region : " << regionId << ", " << partRegionId;

    this->pollenIds = removeUnsupportedPollens(pollenIds);
    this->regionId = regionId;

    QNetworkReply *reply = executeGetRequest(QUrl(POLLEN_API_FRANCE));

    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(handleRequestError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT(handleFetchPollenDataFinished()));
}

void FrenchPollenBackend::handleFetchPollenDataFinished() {
    qDebug() << "FrenchPollenBackend::handleFetchPollenDataFinished";

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    reply->deleteLater();
    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    emit pollenDataAvailable(parsePollenData(reply->readAll()));
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

    QJsonDocument countiesDocument = QJsonDocument::fromJson(responseObject.value("vigilanceMapCounties").toString().toUtf8());
    QJsonObject countyObject = countiesDocument.object().value(this->regionId).toObject();
    QJsonArray risks = countyObject.value("risks").toArray();

    QJsonDocument resultDocument;
    QJsonArray contentArray;

    QJsonArray resultArray;

    QJsonObject resultObject;
    resultObject.insert("lastUpdate", ""); // TODO not supported
    resultObject.insert("nextUpdate", ""); // TODO not supported
    resultObject.insert("scaleElements", 6); // predefined
    resultObject.insert("maxDaysPrediction", 3); // predefined - only one day - but we show 3 anyway
    resultObject.insert("region", this->regionId); // dynamic from request
    resultObject.insert("partRegion", "-"); // not supported

    QJsonArray responseContentArray = responseObject.value("content").toArray();

    for (int i = 0; i < this->pollenIds.size(); i++) {
        int pollenId = this->pollenIds.at(i);
        QJsonObject pollenIdNode = getNodeForPollenId(risks, pollenId);
        // qDebug() << "found node : " << pollenIdNode;

        QJsonObject pollenResultObject;
        pollenResultObject.insert("label", this->pollenIdToLabelMap[pollenId]);
        pollenResultObject.insert("id", pollenId);
        pollenResultObject.insert("today", createResultPollenObject(pollenIdNode, QString("level")));
        // tomorrow / dayAfterTomorrow not supported
        const QString mapUrl = QString(MAP_URL_FRANCE).arg(this->pollenIdToMapKey[pollenId]);
        pollenResultObject.insert("todayMapUrl" , mapUrl);

        resultArray.push_back(pollenResultObject);
    }

    resultObject.insert("pollenData", resultArray);

    resultDocument.setObject(resultObject);
    QString dataToString(resultDocument.toJson());

    return dataToString;
}

QJsonObject FrenchPollenBackend::getNodeForPollenId(QJsonArray risksArray, int pollenId) {
    if (this->pollenIdToPollenNameMap.contains(pollenId)) {
        QString key = this->pollenIdToPollenNameMap[pollenId];
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

bool FrenchPollenBackend::isPollenDataProvided(int pollenId) {
    return this->pollenIdToPollenNameMap.contains(pollenId);
}

QList<int> FrenchPollenBackend::removeUnsupportedPollens(const QList<int> &pollenIds) {
    QList<int> supportedPollenIds;
    for (auto pollenId : pollenIds) {
        if (isPollenDataProvided(pollenId)) {
            supportedPollenIds.append(pollenId);
        }
    }
    return supportedPollenIds;
}
