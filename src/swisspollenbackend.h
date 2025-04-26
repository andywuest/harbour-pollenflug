#ifndef SWISS_POLLEN_BACKEND_H
#define SWISS_POLLEN_BACKEND_H

#include <QObject>

#include "abstractbackend.h"
#include "constants.h"

class SwissPollenBackend : public AbstractBackend {
    Q_OBJECT
public:
    explicit SwissPollenBackend(QNetworkAccessManager *manager, QObject *parent = nullptr);
    ~SwissPollenBackend() override;

protected:
    QString parsePollenData(QByteArray searchReply) override;

#ifdef UNIT_TEST
    friend class PollenBackendTests; // to test non public methods
#endif
};

#endif // SWISS_POLLEN_BACKEND_H
