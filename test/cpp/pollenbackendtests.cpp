#include "pollenbackendtests.h"
#include <QtTest/QtTest>

#include "src/constants.h"

void PollenBackendTests::init() {
    frenchPollenBackend = new FrenchPollenBackend(nullptr, nullptr);
    germanPollenBackend = new GermanPollenBackend(nullptr, nullptr);
    swissPollenBackend = new SwissPollenBackend(nullptr, nullptr);
}

void PollenBackendTests::testIsFrenchPollenDataProvided() {
    QCOMPARE(frenchPollenBackend->isPollenDataProvided(Pollen::Mugwort), true);
    QCOMPARE(frenchPollenBackend->isPollenDataProvided(Pollen::Rye), false);
}

void PollenBackendTests::testIsGermanPollenDataProvided() {
    QCOMPARE(germanPollenBackend->isPollenDataProvided(Pollen::Grass), true);
    QCOMPARE(germanPollenBackend->isPollenDataProvided(Pollen::Nettle), false);
}

void PollenBackendTests::testRemoveFrenchUnsupportedPollens() {
    QList<int> providedPollenIds = QList<int>() << Pollen::Mugwort << Pollen::Rye;
    QList<int> supportedPollenIds = frenchPollenBackend->removeUnsupportedPollens(providedPollenIds);
    QCOMPARE(supportedPollenIds.size(), 1);
    QCOMPARE(supportedPollenIds.at(0), Pollen::Mugwort);
}

void PollenBackendTests::testParseFrenchPollenData() {
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
    frenchPollenBackend->pollenIds = QList<int>() << Pollen::Alder << Pollen::Hazel;

    QString parsedResult = frenchPollenBackend->parsePollenData(data, nullptr);
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

void PollenBackendTests::testGetPollenIdForName() {
    QCOMPARE(swissPollenBackend->getPollenIdForName("Eiche"), Pollen::Oak);
    QCOMPARE(swissPollenBackend->getPollenIdForName("Gräser"), Pollen::Grass);
    QCOMPARE(swissPollenBackend->getPollenIdForName("Birke"), Pollen::Birch);
}

void PollenBackendTests::testGetDayNameForOffset() {
    QCOMPARE(swissPollenBackend->getDayNameForOffset(0), KEY_TODAY);
    QCOMPARE(swissPollenBackend->getDayNameForOffset(1), KEY_TOMORROW);
    QCOMPARE(swissPollenBackend->getDayNameForOffset(2), KEY_DAY_AFTER_TOMORROW);
    QCOMPARE(swissPollenBackend->getDayNameForOffset(3), "");
}

void PollenBackendTests::testParseSwissHtmlResponse() {
    QByteArray data = readFileData("ch_lugano.html");
    QVERIFY2(data.length() > 0, "Testfile not found!");

    swissPollenBackend->resetData();
    QString parsedResult = swissPollenBackend->parsePollenDataStation(data, "today");
    qDebug() << "result : " << parsedResult;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(parsedResult.toUtf8());
    QCOMPARE(jsonDocument.isObject(), true);
    QJsonArray pollenData = jsonDocument.object().value("data").toArray();
    QCOMPARE(pollenData.isEmpty(), false);
    QCOMPARE(pollenData.size(), 7);

    const QJsonObject hasel = pollenData.at(0).toObject();
    QCOMPARE(hasel.value("name"), "Hasel");
    QCOMPARE(hasel.value("pollution"), "keine");
    QCOMPARE(hasel.value("pollutionIndex"), 0);

    const QJsonObject birke = pollenData.at(3).toObject();
    QCOMPARE(birke.value("name"), "Birke");
    QCOMPARE(birke.value("pollution"), "stark");
    QCOMPARE(birke.value("pollutionIndex"), 5);

    const QJsonObject graeser = pollenData.at(6).toObject();
    QCOMPARE(graeser.value("name"), "Gräser");
    QCOMPARE(graeser.value("pollution"), "schwach");
    QCOMPARE(graeser.value("pollutionIndex"), 2);
}

QByteArray PollenBackendTests::readFileData(const QString &fileName) {
    QFile f("testdata/" + fileName);
    // QFile f("/home/andy/projects/sailfishos/github/harbour-pollenflug/test/cpp/testdata/" + fileName);
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
        QString msg = "Testfile " + fileName + " not found!";
        qDebug() << msg << f.fileName() << QFileInfo(f).absoluteFilePath();
        return QByteArray();
    }

    QTextStream in(&f);
    return in.readAll().toUtf8();
}
