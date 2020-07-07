#include "germanpollenbackend.h"

//#include <QDebug>
//#include <QFile>
//#include <QUrl>
//#include <QUrlQuery>
//#include <QUuid>
//#include <QJsonObject>
//#include <QJsonArray>
//#include <QDateTime>
//#include <QVariantMap>
//#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariant>
#include <QVariantList>
#include <QSequentialIterable>
#include <QSequentialIterable>



GermanPollenBackend::GermanPollenBackend(QNetworkAccessManager *manager, QObject *parent) : QObject(parent) {
    qDebug() << "Initializing German Pollen Backend...";
    this->manager = manager;

    // internally used in json object lookup
    this->pollenIdToKeyMap.insert(1, "Beifuss");
    this->pollenIdToKeyMap.insert(2, "Birke");
    this->pollenIdToKeyMap.insert(3, "Erle");
    this->pollenIdToKeyMap.insert(4, "Esche");
    this->pollenIdToKeyMap.insert(5, "Graeser");
    this->pollenIdToKeyMap.insert(6, "Hasel");
    this->pollenIdToKeyMap.insert(7, "Ambrosia");
    this->pollenIdToKeyMap.insert(8, "Roggen");

    // TODO english
    this->pollenIdToLabelMap.insert(1, tr("Beifuss"));
    this->pollenIdToLabelMap.insert(2, tr("Birke"));
    this->pollenIdToLabelMap.insert(3, tr("Erle"));
    this->pollenIdToLabelMap.insert(4, tr("Esche"));
    this->pollenIdToLabelMap.insert(5, tr("Gräser"));
    this->pollenIdToLabelMap.insert(6, tr("Hasel"));
    this->pollenIdToLabelMap.insert(7, tr("Ambrosia"));
    this->pollenIdToLabelMap.insert(8, tr("Roggen"));

    // used for label
    this->pollutionIndexToLabelMap.insert("0", tr("keine Belastung"));
    this->pollutionIndexToLabelMap.insert("0-1", tr("keine bis geringe Belastung"));
    this->pollutionIndexToLabelMap.insert("1", tr("geringe Belastung"));
    this->pollutionIndexToLabelMap.insert("1-2", tr("geringe bis mittlere Belastung"));
    this->pollutionIndexToLabelMap.insert("2", tr("mittlere Belastung"));
    this->pollutionIndexToLabelMap.insert("2-3", tr("mittlere bis hohe Belastung"));
    this->pollutionIndexToLabelMap.insert("3", tr("hohe Belastung"));

    // used for scale index
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

QNetworkReply *GermanPollenBackend::executeGetRequest(const QUrl &url) {
    qDebug() << "AbstractDataBackend::executeGetRequest " << url;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, MIME_TYPE_JSON);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);

    return manager->get(request);
}

void GermanPollenBackend::handleRequestError(QNetworkReply::NetworkError error) {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    qWarning() << "AbstractDataBackend::handleRequestError:" << static_cast<int>(error) << reply->errorString() << reply->readAll();

    emit requestError("Return code: " + QString::number(static_cast<int>(error)) + " - " + reply->errorString());
}

void GermanPollenBackend::fetchPollenData(const QList<int> &pollenIds, int regionId, int partRegionId) {
    qDebug() << "GermanPollenBackend::fetchPollenData";
    qDebug() << pollenIds;

    this->pollenIds = pollenIds;
    this->regionId = regionId;
    this->partRegionId = partRegionId;

    QNetworkReply *reply = executeGetRequest(QUrl(GERMAN_POLLEN_API));

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

    QByteArray searchReply = reply->readAll();

    // qDebug() << parsePollenData(searchReply);

    emit pollenDataAvailable(parsePollenData(searchReply));
}

bool GermanPollenBackend::isRegionNodeFound(int regionId, int partRegionId) {
    if (this->regionId == regionId) {
        if (this->partRegionId != -1 && this->partRegionId == partRegionId) {
            qDebug() << " fOUND !!!";
            return true;
        } else if (this->partRegionId == -1) {
            qDebug() << " fOUND !!!";
            return true;
       }
    }
    return false;
}

QJsonObject GermanPollenBackend::getNodeForPollenId(QJsonObject pollenNode, int pollenId) {
    if (this->pollenIdToKeyMap.contains(pollenId)) {
        QString key = this->pollenIdToKeyMap[pollenId];
        qDebug() << " found value for key " << pollenId;
        return pollenNode.value(key).toObject();
    }
    qDebug() << " error no value found found key " << pollenId;
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
    resultObject.insert("last_update", responseObject.value("last_update"));
    resultObject.insert("next_update", responseObject.value("next_update"));
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

         qDebug() << "region/partregion: " << regionId << "/" << partRegionId;

         if (isRegionNodeFound(regionId, partRegionId) == true) {
             qDebug()<< "variant : " << this->pollenIds;
             QJsonObject responsePollenObject = rootObject.value("Pollen").toObject();


             for (int i = 0; i < this->pollenIds.size(); i++) {
                 int pollenId = this->pollenIds.at(i);

                 QJsonObject pollenIdNode = getNodeForPollenId(responsePollenObject, pollenId);

//                 qDebug() << " today : " << pollenIdNode.value("today").toString();
//                 qDebug() << " tomorrow : " << pollenIdNode.value("tomorrow").toString();
//                 qDebug() << " dayafter_to : " << pollenIdNode.value("dayafter_to").toString();


//                 QJsonObject todayObject;
//                 todayObject.insert("pollutionIndex", this->pollutionIndexToIndexMap[pollenIdNode.value("today").toString()]);
//                 todayObject.insert("pollutionLabel", this->pollutionIndexToLabelMap[pollenIdNode.value("today").toString()]);

                 // TODO morrow, day after tommore

                 QJsonObject pollenResultObject;
                 pollenResultObject.insert("label", this->pollenIdToLabelMap[pollenId]);
                 pollenResultObject.insert("id", pollenId);
                 pollenResultObject.insert("today", createResultPollenObject(pollenIdNode, QString("today")));
                 pollenResultObject.insert("tomorrow", createResultPollenObject(pollenIdNode, QString("tomorrow")));
                 pollenResultObject.insert("dayAfterTomorrow", createResultPollenObject(pollenIdNode, QString("dayafter_to")));

                 resultArray.push_back(pollenResultObject);
             }
         }
    }

    resultObject.insert("pollenData", resultArray);






//            last_update: "10.10.2020 12:23"
//            next_update: "10.10.2020 12:23"
//            scaleElements: 7
//            maxDaysPrediction: 3
//            region: 10
//            regionPart: -1



//    foreach (const QJsonValue & value, responseArray) {
//        QJsonObject rootObject = value.toObject();
//        QJsonObject exchangeObject = rootObject["exchange"].toObject();

//        QJsonObject resultObject;
//        resultObject.insert("extRefId", rootObject.value("id"));
//        resultObject.insert("name", rootObject.value("name"));
//        resultObject.insert("currency", rootObject.value("currency"));
//        resultObject.insert("price", rootObject.value("last"));
//        resultObject.insert("symbol1", rootObject.value("symbol"));
//        resultObject.insert("isin", rootObject.value("isin"));
//        resultObject.insert("stockMarketName", exchangeObject.value("name"));
//        resultObject.insert("changeAbsolute", rootObject.value("change"));
//        resultObject.insert("changeRelative", rootObject.value("changeInPercentage"));
//        resultObject.insert("high", rootObject.value("high"));
//        resultObject.insert("low", rootObject.value("low"));
//        resultObject.insert("ask", rootObject.value("ask"));
//        resultObject.insert("bid", rootObject.value("bid"));
//        resultObject.insert("volume", rootObject.value("volume"));
//        resultObject.insert("numberOfStocks", rootObject.value("numberOfStocks"));

//        QJsonValue jsonUpdatedAt = rootObject.value("updatedAt");
//        QDateTime updatedAtLocalTime = convertUTCDateTimeToLocalDateTime(jsonUpdatedAt.toString());
//        resultObject.insert("quoteTimestamp", convertToDatabaseDateTimeFormat(updatedAtLocalTime));

//        resultObject.insert("lastChangeTimestamp", convertToDatabaseDateTimeFormat(QDateTime::currentDateTime()));

//        resultArray.push_back(resultObject);
//    }

    resultDocument.setObject(resultObject);
    QString dataToString(resultDocument.toJson());

    return dataToString;
}



/**

Customer Data Model:

  client provides the configured allergenes as list "1, 2, 3"
  Response

  {
    last_update: "10.10.2020 12:23"
    next_update: "10.10.2020 12:23"
    scaleElements: 7
    maxDaysPrediction: 3
    region: 10
    regionPart: -1

    content: [
       {
           label: Gräser
           today {
              pollutionIndex: 2
              pollutionLabel: "keine Belastung"
           }
           tomorrow {
              pollutionIndex: 2
              pollutionLabel: "keine Belastung"
           }
           dayAfterTomorrow {
              pollutionIndex: -1
           }
       },
       {
           label: Birke
       }

    ];



  }





*/


