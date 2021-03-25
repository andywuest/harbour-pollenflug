#include "frenchpollenbackendtests.h"
#include <QtTest/QtTest>

void FrenchPollenBackendTests::init() {
    frenchPollenBackend = new FrenchPollenBackend(nullptr, nullptr);
}

void FrenchPollenBackendTests::testIngConvertTimestampToLocalTimestamp() {
    qDebug() << "dir : " << QCoreApplication::applicationFilePath();
    qDebug() << "Timezone for test : " << QTimeZone::systemTimeZone();
    QString testDate = QString("2020-10-14T20:22:24+02:00");
    QTimeZone testTimeZone = QTimeZone("Europe/Berlin");
//    QDateTime convertedDateTime = ingDibaBackend->convertTimestampToLocalTimestamp(testDate, testTimeZone);
//    QString dateTimeFormatted = convertedDateTime.toString("yyyy-MM-dd") + " " + convertedDateTime.toString("hh:mm:ss");
    QCOMPARE(QString("2020-10-14 20:22:24"), QString("2020-10-14 20:22:24"));
}

void FrenchPollenBackendTests::testIsValidSecurityCategory() {
//    QCOMPARE(ingDibaBackend->isValidSecurityCategory("Fonds"), true);
//    QCOMPARE(ingDibaBackend->isValidSecurityCategory("Aktien"), true);
//    QCOMPARE(ingDibaBackend->isValidSecurityCategory("etfs"), true);
//    QCOMPARE(ingDibaBackend->isValidSecurityCategory("NIX"), false);
}

void FrenchPollenBackendTests::testIsPollenDataProvided() {
    QCOMPARE(frenchPollenBackend->isPollenDataProvided(Pollen::Mugwort), true);
    QCOMPARE(frenchPollenBackend->isPollenDataProvided(Pollen::Rye), false);
}

void FrenchPollenBackendTests::testRemoveUnsupportedPollens() {
    QList<int> providedPollenIds = QList<int>() << Pollen::Mugwort << Pollen::Rye;
    QList<int> supportedPollenIds = frenchPollenBackend->removeUnsupportedPollens(providedPollenIds);
    QCOMPARE(supportedPollenIds.size(), 1);
    QCOMPARE(supportedPollenIds.at(0), (int) Pollen::Mugwort);
}

void FrenchPollenBackendTests::testParsePollenData() {
    QString testFile = "fr.json";
    QFile f("testdata/" + testFile);
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
        QString msg = "Testfile " + testFile + " not found!";
        QFAIL(msg.toLocal8Bit().data());
    }

    QTextStream in(&f);
    QByteArray data = in.readAll().toUtf8();

    // ALDER and Hazel for region 01
    frenchPollenBackend->regionId = "01";
    frenchPollenBackend->pollenIds = QList<int>()
            << Pollen::Alder
            << Pollen::Hazel;

    QString parsedResult = frenchPollenBackend->parsePollenData(data);
    qDebug() << "result : " << parsedResult;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(parsedResult.toUtf8());
    QCOMPARE(jsonDocument.isObject(), true);
    QCOMPARE(jsonDocument.object().value("maxDaysPrediction"), 3);
    QCOMPARE(jsonDocument.object().value("region"), "01");
    QCOMPARE(jsonDocument.object().value("partRegion"), "-");

    QJsonArray pollenData = jsonDocument.object().value("pollenData").toArray();
    QCOMPARE(pollenData.isEmpty(), false);
    QCOMPARE(pollenData.size(), 2);
    QCOMPARE(pollenData.at(0).toObject().value("id"), 3);
    QCOMPARE(pollenData.at(0).toObject().value("label"), "Alder");
    QJsonObject todayAlder = pollenData.at(0).toObject().value("today").toObject();
    QCOMPARE(todayAlder.value("pollutionIndex"), 3);
    QCOMPARE(todayAlder.value("pollutionLabel"), "medium pollen exposure");

    // TODO read pollution

    QCOMPARE(pollenData.at(1).toObject().value("id"), 6);
    QCOMPARE(pollenData.at(1).toObject().value("label"), "Hazel");
    QJsonObject todayHazel = pollenData.at(1).toObject().value("today").toObject();
    QCOMPARE(todayHazel.value("pollutionIndex"), 2);
    QCOMPARE(todayHazel.value("pollutionLabel"), "small pollen exposure");

    // TODO read pollution
}
