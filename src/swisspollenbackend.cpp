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
    this->pollutionIndexToLabelMap.insert("keine", tr("no pollen exposure"));      // keine Belastung
    this->pollutionIndexToLabelMap.insert("schwach", tr("small pollen exposure")); // schwache Belastung
    this->pollutionIndexToLabelMap.insert("mässig", tr("medium pollen exposure")); // mässig Belastung
    this->pollutionIndexToLabelMap.insert("stark", tr("high pollen exposure"));    // starke Belastung

    // used for scale index
    this->pollutionIndexToIndexMap.insert("keine", 0);
    this->pollutionIndexToIndexMap.insert("schwach", 2);
    this->pollutionIndexToIndexMap.insert("mässig", 4);
    this->pollutionIndexToIndexMap.insert("stark", 6);
}

SwissPollenBackend::~SwissPollenBackend() {
    qDebug() << "Shutting down Swiss Pollen Backend...";
}

void SwissPollenBackend::resetData() {
    this->handledPollenIds.clear();
    this->searchStationDataResults.clear();

//    auto todayMap = QMap<int, QJsonObject>();
//    todayMap.insert(Pollen::Grass, QJsonObject());
//    todayMap.insert(Pollen::Hazel, QJsonObject());

    this->searchStationDataResults.insert(KEY_TODAY, QMap<int, QJsonObject>());
    //    this->searchStationDataResults[KEY_TOMORROW] = QMap<Pollen, QJsonObject>();
    //    this->searchStationDataResults[KEY_DAY_AFTER_TOMORROW] = QMap<Pollen, QJsonObject>();
}

void SwissPollenBackend::fetchPollenData(const QList<int> &pollenIds, QString regionId, QString partRegionId) {
    qDebug() << "SwissPollenBackend::fetchPollenData";
    qDebug() << pollenIds << " region : " << regionId << ", " << partRegionId;

    this->pollenIds = removeUnsupportedPollens(pollenIds);
    this->stationName = regionId;

    resetData();
//    this->handledPollenIds.clear();
//    this->searchStationDataResults.clear();
//    this->searchStationDataResults[KEY_TODAY] = QMap<int, QJsonObject>();
//    this->searchStationDataResults[KEY_TOMORROW] = QMap<Pollen, QJsonObject>();
//    this->searchStationDataResults[KEY_DAY_AFTER_TOMORROW] = QMap<Pollen, QJsonObject>();

    for (int i = 0; i < this->numberOfRequestedDays; i++) {
        const QString date = QDate::currentDate().addDays(i).toString("yyyy-MM-dd");
        qDebug() << "looking up day : " << date;
        QNetworkReply *reply = executeGetRequest(QUrl(QString(POLLEN_API_SWITZERLAND) //
                                                      .arg(this->stationName, date))); //

        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(handleRequestError(QNetworkReply::NetworkError)));
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

QString SwissPollenBackend::parsePollenDataStation(QByteArray stationData) {
    qDebug() << "SwissPollenBackend::parsePollenDataStation";
    QJsonArray resultArray;
    QJsonDocument resultDocument;
    QJsonObject resultObject;

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
            if (pollenId != -1 && !handledPollenIds.contains(pollenId)) {
                handledPollenIds.append(pollenId);
            }

            qDebug() << "size before : " << this->searchStationDataResults[KEY_TODAY].size();

            // TODO not only today
            QMap<int, QJsonObject> todayMap = this->searchStationDataResults.value(KEY_TODAY);
            todayMap.insert(pollenId, pollenResultObject);
            this->searchStationDataResults.insert(KEY_TODAY, todayMap);

            qDebug() << "size after : " << this->searchStationDataResults.value(KEY_TODAY).size();
            qDebug() << "name : " << pollenName;
            qDebug() << "pollutionInfo : " << pollutionInfo;
        }
    }

    resultObject.insert("data", resultArray);
    resultDocument.setObject(resultObject);
    QString dataToString(resultDocument.toJson());
    return dataToString;
}

QString SwissPollenBackend::parsePollenData(QByteArray searchReply) {
    qDebug() << "SwissPollenBackend::parsePollenData";
    QJsonDocument resultDocument;

    QJsonObject resultObject;

    parsePollenDataStation(searchReply);

    if (this->searchStationDataResults.size() == this->numberOfRequestedDays) {
        QJsonObject resultObject;
        resultObject.insert("lastUpdate", ""); // not supported
        resultObject.insert("nextUpdate", ""); // not suppored
        resultObject.insert("scaleElements", 4);               // predefined
        resultObject.insert("maxDaysPrediction", 3);           // predefined
        resultObject.insert("region", this->stationName); // dynamic from request

        QJsonArray resultArray;

        // add for each pollen an entry
        for(const int pollenId : handledPollenIds) {
           QJsonObject pollenResult;

           // handle today
           const QMap<int, QJsonObject> todayMap = this->searchStationDataResults[KEY_TODAY];
           pollenResult.insert("id", pollenId);
           pollenResult.insert("label", getPollenName(pollenId));
           pollenResult.insert("todayMapUrl", ""); // not supported (TODO check)
           pollenResult.insert(KEY_TODAY, todayMap[pollenId]);

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


