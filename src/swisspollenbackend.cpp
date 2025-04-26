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
    addPollenData(Pollen::Grass, "Graeser", "6");

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

QString SwissPollenBackend::parsePollenData(QByteArray searchReply) {
    QJsonDocument resultDocument;
    QJsonArray resultArray;
    QJsonObject resultObject;

    const QStringList tokens = QString(searchReply)                                                       //
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
            pollenResultObject.insert("pollution", pollutionInfo);
            resultArray.push_back(pollenResultObject);

            qDebug() << "name : " << pollenName;
            qDebug() << "pollutionInfo : " << pollutionInfo;
        }
    }

    resultObject.insert("data", resultArray);

    resultDocument.setObject(resultObject);
    QString dataToString(resultDocument.toJson());

    return dataToString;
}
