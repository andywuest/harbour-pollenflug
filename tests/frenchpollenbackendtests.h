#ifndef FRENCHPOLLENBACKENDTEST_H
#define FRENCHPOLLENBACKENDTEST_H

#include "src/frenchpollenbackend.h"
#include <QObject>

class FrenchPollenBackendTests : public QObject {
    Q_OBJECT

private:
    FrenchPollenBackend *frenchPollenBackend;
private slots:
    void init();
    void testIngConvertTimestampToLocalTimestamp();
    void testIsValidSecurityCategory();
    void testParsePollenData();
    void testIsPollenDataProvided();
    void testRemoveUnsupportedPollens();
};

#endif // FRENCHPOLLENBACKENDTEST_H
