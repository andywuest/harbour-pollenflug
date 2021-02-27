#include "frenchpollenbackend.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

FrenchPollenBackend::FrenchPollenBackend(QNetworkAccessManager *manager, QObject *parent) : QObject(parent) {
    qDebug() << "Initializing French Pollen Backend...";
    this->manager = manager;
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

void FrenchPollenBackend::fetchPollenData(const QList<int> &pollenIds, int regionId, int partRegionId) {
    qDebug() << "FrenchPollenBackend::fetchPollenData";
    qDebug() << pollenIds;

    // TODO
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

    QJsonObject responseObject = jsonDocument.object();
    QJsonDocument resultDocument;
    QJsonArray contentArray;

    QJsonArray resultArray;

    QJsonObject resultObject;
    resultObject.insert("lastUpdate", responseObject.value("last_update"));
    resultObject.insert("nextUpdate", responseObject.value("next_update"));
    resultObject.insert("scaleElements", 7); // predefined
    resultObject.insert("maxDaysPrediction", 3); // predefined
    // resultObject.insert("region", this->regionId); // dynamic from request
    // resultObject.insert("partRegion", this->partRegionId); // dynamic from request

    QJsonArray responseContentArray = responseObject.value("content").toArray();

//    qDebug() << "region/partregion (requested): " << this->regionId << "/" << this->partRegionId;

//    foreach (const QJsonValue &value, responseContentArray) {
//         QJsonObject rootObject = value.toObject();
//         int regionId = rootObject.value("region_id").toInt();
//         int partRegionId = rootObject.value("partregion_id").toInt();

//         if (isRegionNodeFound(regionId, partRegionId) == true) {
//             QJsonObject responsePollenObject = rootObject.value("Pollen").toObject();

//             for (int i = 0; i < this->pollenIds.size(); i++) {
//                 int pollenId = this->pollenIds.at(i);
//                 QJsonObject pollenIdNode = getNodeForPollenId(responsePollenObject, pollenId);

//                 QJsonObject pollenResultObject;
//                 pollenResultObject.insert("label", this->pollenIdToLabelMap[pollenId]);
//                 pollenResultObject.insert("id", pollenId);
//                 pollenResultObject.insert("today", createResultPollenObject(pollenIdNode, QString("today")));
//                 pollenResultObject.insert("tomorrow", createResultPollenObject(pollenIdNode, QString("tomorrow")));
//                 pollenResultObject.insert("dayAfterTomorrow", createResultPollenObject(pollenIdNode, QString("dayafter_to")));

//                 resultArray.push_back(pollenResultObject);
//             }
//         }
//    }
//    resultObject.insert("pollenData", resultArray);

    resultDocument.setObject(resultObject);
    QString dataToString(resultDocument.toJson());

    return dataToString;
}
