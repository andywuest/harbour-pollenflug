#ifndef POLLEN_BACKEND_TEST_H
#define POLLEN_BACKEND_TEST_H

#include "src/frenchpollenbackend.h"
#include "src/germanpollenbackend.h"
#include <QObject>

class PollenBackendTests : public QObject {
    Q_OBJECT

private:
    FrenchPollenBackend *frenchPollenBackend;
    GermanPollenBackend *germanPollenBackend;
private slots:
    void init();
    void testParseFrenchPollenData();
    void testIsFrenchPollenDataProvided();
    void testRemoveFrenchUnsupportedPollens();
    // TODO add german tests
};

#endif // POLLEN_BACKEND_TEST_H
