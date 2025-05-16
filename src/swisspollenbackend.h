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

    Q_INVOKABLE void fetchPollenData(const QList<int> &pollenIds, QString regionId, QString partRegionId);

protected:
    QString parsePollenData(QByteArray searchReply, QNetworkReply *reply) override;
    QString parsePollenDataStation(QByteArray stationData, const QString dayName);
    void resetData();
    int getPollenIdForName(QString pollenName);

private:
    const int numberOfRequestedDays = 3;                            // swiss backend provides the next three days
    QMap<QString, QMap<int, QJsonObject>> searchStationDataResults; // first key is the day
    QList<int> handledPollenIds;
    QString stationName;
    QString getDayNameForOffset(const int offset);

#ifdef UNIT_TEST
    friend class PollenBackendTests; // to test non public methods
#endif
};

#endif // SWISS_POLLEN_BACKEND_H
