#include "frenchpollenbackend.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

FrenchPollenBackend::FrenchPollenBackend(QNetworkAccessManager *manager, QObject *parent) : QObject(parent) {
    qDebug() << "Initializing French Pollen Backend...";
    this->manager = manager;

    // internally used in json object lookup
    this->pollenIdToPollenNameMap.insert(Pollen::Mugwort, "Armoise");
    this->pollenIdToPollenNameMap.insert(Pollen::Birch, "Bouleau");
    this->pollenIdToPollenNameMap.insert(Pollen::Alder, "Aulne");
    // this->pollenIdToPollenNameMap.insert(4, "Esche"); ?? TODO
    this->pollenIdToPollenNameMap.insert(Pollen::Grass, "Graminées");
    this->pollenIdToPollenNameMap.insert(Pollen::Hazel, "Noisetier");
    this->pollenIdToPollenNameMap.insert(Pollen::Ambrosia, "Ambroisies");
    // this->pollenIdToPollenNameMap.insert(8, "Roggen"); ?? TODO

    // TODO english
    this->pollenIdToLabelMap.insert(Pollen::Mugwort, tr("Mugwort")); // Beifuss
    this->pollenIdToLabelMap.insert(Pollen::Birch, tr("Birch")); // Birke
    this->pollenIdToLabelMap.insert(Pollen::Alder, tr("Alder")); // Erle
    // this->pollenIdToLabelMap.insert(4, tr("Ash Tree")); // Esche
    this->pollenIdToLabelMap.insert(Pollen::Grass, tr("Grass")); // Gräser
    this->pollenIdToLabelMap.insert(Pollen::Hazel, tr("Hazel")); // Hasel
    this->pollenIdToLabelMap.insert(Pollen::Ambrosia, tr("Ambrosia")); // Ambrosia
    // this->pollenIdToLabelMap.insert(8, tr("Rye")); // Roggen ?? TODO

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

void FrenchPollenBackend::fetchPollenData(const QList<int> &pollenIds, QString regionId, int partRegionId) {
    qDebug() << "FrenchPollenBackend::fetchPollenData";
    qDebug() << pollenIds;

    this->pollenIds = pollenIds;
    this->regionId = regionId;

    QNetworkReply *reply = executeGetRequest(QUrl(FRENCH_POLLEN_API));

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
    resultObject.insert("maxDaysPrediction", 1); // predefined
    resultObject.insert("region", this->regionId); // dynamic from request
    resultObject.insert("partRegion", "-"); // not supported

    QJsonArray responseContentArray = responseObject.value("content").toArray();

    for (int i = 0; i < this->pollenIds.size(); i++) {
        int pollenId = this->pollenIds.at(i);
        QJsonObject pollenIdNode = getNodeForPollenId(risks, pollenId);
        qDebug() << "found node : " << pollenIdNode;

        QJsonObject pollenResultObject;
        pollenResultObject.insert("label", this->pollenIdToLabelMap[pollenId]);
        pollenResultObject.insert("id", pollenId);
        pollenResultObject.insert("today", createResultPollenObject(pollenIdNode, QString("level")));
        // tomorrow / dayAfterTomorrow not supported

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
        qDebug() << " found value for key " << pollenId;

        foreach (const QJsonValue &riskNode, risksArray) {
            QString pollenName = riskNode.toObject().value("pollenName").toString();
            qDebug() << "pollenname : " << pollenName;
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
