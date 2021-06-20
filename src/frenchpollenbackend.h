#ifndef FRENCH_POLLEN_BACKEND_H
#define FRENCH_POLLEN_BACKEND_H

#include <QObject>

#include "constants.h"
#include "abstractbackend.h"

class FrenchPollenBackend : public AbstractBackend {
    Q_OBJECT
public:
    explicit  FrenchPollenBackend(QNetworkAccessManager *manager, QObject *parent = nullptr);
    ~FrenchPollenBackend();

    Q_INVOKABLE void fetchPollenData(const QList<int> &pollenIds, QString regionId, QString partRegionId);

protected:
    QString parsePollenData(QByteArray searchReply); // TODO rename -> abstract in basisklasse
    QJsonObject createResultPollenObject(QJsonObject pollenSourceNode, QString value);

private slots:
    void handleFetchPollenDataFinished();

private:
    QString regionId;

    QJsonObject getNodeForPollenId(QJsonArray risksArray, int pollenId);

#ifdef UNIT_TEST
    friend class PollenBackendTests; // to test non public methods
#endif

};

#endif // FRENCH_POLLEN_BACKEND_H
