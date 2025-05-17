#ifndef POLLEN_BACKEND_TEST_H
#define POLLEN_BACKEND_TEST_H

#include "src/frenchpollenbackend.h"
#include "src/germanpollenbackend.h"
#include "src/swisspollenbackend.h"
#include <QObject>

class PollenBackendTests : public QObject {
    Q_OBJECT

private:
    FrenchPollenBackend *frenchPollenBackend;
    GermanPollenBackend *germanPollenBackend;
    SwissPollenBackend *swissPollenBackend;

protected:
    QByteArray readFileData(const QString &fileName);

private slots:
    void init();
    void testParseFrenchPollenData();
    void testIsFrenchPollenDataProvided();
    void testRemoveFrenchUnsupportedPollens();
    // TODO add german tests
    void testIsGermanPollenDataProvided();
    // swiss tests
    void testParseSwissHtmlResponse();
    void testGetPollenIdForName();
    void testGetDayNameForOffset();
};

#endif // POLLEN_BACKEND_TEST_H
