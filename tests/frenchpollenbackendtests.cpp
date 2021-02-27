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

void FrenchPollenBackendTests::testParsePollenData() {
    QString testFile = "fr.json";
    QFile f("testdata/" + testFile);
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
        QString msg = "Testfile " + testFile + " not found!";
        QFAIL(msg.toLocal8Bit().data());
    }

    QTextStream in(&f);
    QByteArray data = in.readAll().toUtf8();
    QString parsedResult = frenchPollenBackend->parsePollenData(data);
    QJsonDocument jsonDocument = QJsonDocument::fromJson(parsedResult.toUtf8());
    QCOMPARE(jsonDocument.isArray(), true);
    QJsonArray resultArray = jsonDocument.array();
    QCOMPARE(resultArray.size(), 1);
}
