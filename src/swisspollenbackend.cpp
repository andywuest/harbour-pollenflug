#include "swisspollenbackend.h"
#include "genericpollen.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QRegularExpression>

SwissPollenBackend::SwissPollenBackend(QNetworkAccessManager *manager, QObject *parent)
    : AbstractBackend(manager, parent) {
    qDebug() << "Initializing Swiss Pollen Backend...";

    // TODO ids
    addPollenData(Pollen::Hazel, "Hasel", "0");
    addPollenData(Pollen::Alder, "Erle", "1");
    addPollenData(Pollen::AshTree, "Esche", "2");
    addPollenData(Pollen::Birch, "Birke", "3");
    addPollenData(Pollen::Hornbeam, "Buche", "4");
    addPollenData(Pollen::Oak, "Eiche", "5");
    addPollenData(Pollen::Grass, "Gräser", "6");

    // used for label - CH has the following categories keine - schwach - mässig - stark
    this->pollutionIndexToLabelMap.insert("keine", tr("no pollen exposure"));             // keine Belastung
    this->pollutionIndexToLabelMap.insert("schwach", tr("small pollen exposure"));        // schwache Belastung
    this->pollutionIndexToLabelMap.insert("mässig", tr("medium pollen exposure"));        // mässig Belastung
    this->pollutionIndexToLabelMap.insert("stark", tr("high pollen exposure"));           // starke Belastung
    this->pollutionIndexToLabelMap.insert("sehr stark", tr("very high pollen exposure")); // sehr starke Belastung

    // used for scale index
    this->pollutionIndexToIndexMap.insert("keine", 0);
    this->pollutionIndexToIndexMap.insert("schwach", 2);
    this->pollutionIndexToIndexMap.insert("mässig", 3);
    this->pollutionIndexToIndexMap.insert("stark", 5);
    this->pollutionIndexToIndexMap.insert("sehr stark", 6);
}

SwissPollenBackend::~SwissPollenBackend() {
    qDebug() << "Shutting down Swiss Pollen Backend...";
}

void SwissPollenBackend::resetData() {
    this->handledPollenIds.clear();
    this->searchStationDataResults.clear();
    this->searchStationDataResults.insert(KEY_TODAY, QMap<int, QJsonObject>());
    this->searchStationDataResults.insert(KEY_TOMORROW, QMap<int, QJsonObject>());
    this->searchStationDataResults.insert(KEY_DAY_AFTER_TOMORROW, QMap<int, QJsonObject>());
}

QString SwissPollenBackend::getDayNameForOffset(const int offset) {
    switch (offset) {
    case 0:
        return QString(KEY_TODAY);
    case 1:
        return QString(KEY_TOMORROW);
    case 2:
        return QString(KEY_DAY_AFTER_TOMORROW);
    }
    return "";
}

void SwissPollenBackend::fetchPollenData(const QList<int> &pollenIds, QString regionId, QString partRegionId) {
    qDebug() << "SwissPollenBackend::fetchPollenData";
    qDebug() << pollenIds << " region : " << regionId << ", " << partRegionId;

    this->pollenIds = removeUnsupportedPollens(pollenIds);
    this->stationName = regionId;

    resetData();

    for (int offset = 0; offset < this->numberOfRequestedDays; offset++) {
        const QString date = QDate::currentDate().addDays(offset).toString("yyyy-MM-dd");
        qDebug() << "looking up day : " << date;
        QNetworkReply *reply = executeGetRequest(QUrl(QString(POLLEN_API_SWITZERLAND)      //
                                                          .arg(this->stationName, date))); //

        reply->setProperty(NETWORK_REPLY_PROPERTY_REQUEST_DAY, getDayNameForOffset(offset));

        connect(reply,
                SIGNAL(error(QNetworkReply::NetworkError)),
                this,
                SLOT(handleRequestError(QNetworkReply::NetworkError)));
        connect(reply, SIGNAL(finished()), this, SLOT(handleFetchPollenDataFinished()));
    }
}

int SwissPollenBackend::getPollenIdForName(QString pollenName) {
    for (auto entry = this->pollenIdToPollenData.begin(); entry != this->pollenIdToPollenData.end(); ++entry) {
        if (entry.value()->getJsonLookupKey() == pollenName) {
            return entry.value()->getPollenId();
        }
    }
    qDebug() << "Warning : unknown pollenName : " << pollenName;
    return -1;
}

QString SwissPollenBackend::parsePollenDataStation(QByteArray stationData, QString dayName) {
    qDebug() << "SwissPollenBackend::parsePollenDataStation";
    QJsonArray resultArray;
    QJsonDocument resultDocument;
    QJsonObject resultObject;

    // qDebug() << "data: " << QString(stationData);

    const QStringList tokens = QString(stationData)                                                       //
                                   .replace(QRegExp(".*<div class=\"data-box mb-0 pb-0 pb-lg-3\" >"), "") //
                                   .split("<div class=\"data-row\">");

    for (const auto &pollenInformation : tokens) {
        const QStringList dataTokens = pollenInformation.split("<div class=\"data-row-bar\">");
        if (dataTokens.size() == 2) {
            QString token1 = dataTokens.at(0);
            QString token2 = dataTokens.at(1);
            const QString pollenName = token1
                                           .replace(QRegExp("</div>.*"), "") //
                                           .replace(QRegExp(".*>"), "")      //
                                           .trimmed();
            const QString pollutionInfo = token2
                                              .replace(QRegExp("</span>.*"), "") //
                                              .replace(QRegExp(".*>"), "")       //
                                              .trimmed();

            QJsonObject pollenResultObject;
            pollenResultObject.insert("name", pollenName);
            pollenResultObject.insert("pollutionIndex", this->pollutionIndexToIndexMap[pollutionInfo]); // TODO fixme
            pollenResultObject.insert("pollution", pollutionInfo);
            pollenResultObject.insert("pollutionLabel", this->pollutionIndexToLabelMap[pollutionInfo]);
            resultArray.push_back(pollenResultObject);

            const int pollenId = getPollenIdForName(pollenName);

            qDebug() << " current pollenId " << pollenId;

            // only handle supported pollens
            if (this->pollenIds.contains(pollenId) && pollenId != -1) {
                // update handledPollenIds -> only once, independent of the currently handled dayName
                if (!handledPollenIds.contains(pollenId)) {
                    handledPollenIds.append(pollenId);
                }

                // TODO not only today
                QMap<int, QJsonObject> todayMap = this->searchStationDataResults.value(dayName);
                todayMap.insert(pollenId, pollenResultObject);
                this->searchStationDataResults.insert(dayName, todayMap);

                qDebug() << dayName << ", name : " << pollenName;
                qDebug() << dayName << ", pollutionInfo : " << pollutionInfo;
            }
        }
    }

    resultObject.insert("data", resultArray);
    resultDocument.setObject(resultObject);
    QString dataToString(resultDocument.toJson());
    return dataToString;
}

QString SwissPollenBackend::parsePollenData(QByteArray searchReply, QNetworkReply *reply) {
    qDebug() << "SwissPollenBackend::parsePollenData";
    const QString requestDayName = reply->property(NETWORK_REPLY_PROPERTY_REQUEST_DAY).toString();
    qDebug() << "handling response : " << requestDayName << ", size: " << searchReply.length();

    QJsonDocument resultDocument;

    QJsonObject resultObject;

    parsePollenDataStation(searchReply, requestDayName);

    if (this->searchStationDataResults.size() == this->numberOfRequestedDays) {
        QJsonObject resultObject;
        resultObject.insert("lastUpdate", "");            // not supported
        resultObject.insert("nextUpdate", "");            // not suppored
        resultObject.insert("scaleElements", 5);          // predefined
        resultObject.insert("maxDaysPrediction", 3);      // predefined
        resultObject.insert("region", this->stationName); // dynamic from request

        QJsonArray resultArray;

        // add an entry for each handled pollenId
        for (const int pollenId : handledPollenIds) {
            QJsonObject pollenResult;
            pollenResult.insert("id", pollenId);
            pollenResult.insert("label", getPollenName(pollenId));
            pollenResult.insert("todayMapUrl", ""); // not supported (TODO check)

            for (int offset = 0; offset < this->numberOfRequestedDays; offset++) {
                const QString currentDayName = this->getDayNameForOffset(offset);
                const QMap<int, QJsonObject> dayMap = this->searchStationDataResults[currentDayName];
                qDebug() << "insert for " << currentDayName;
                pollenResult.insert(currentDayName, dayMap[pollenId]);
            }

            resultArray.push_back(pollenResult);
        }

        resultObject.insert("pollenData", resultArray);

        resultDocument.setObject(resultObject);
        QString dataToString(resultDocument.toJson());

        return dataToString;
    }

    // if we are not yet finished, only return empty response
    return "{}";
}
