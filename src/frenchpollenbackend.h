#ifndef FRENCH_POLLEN_BACKEND_H
#define FRENCH_POLLEN_BACKEND_H

#include <QObject>

#include "abstractbackend.h"
#include "constants.h"

class FrenchPollenBackend : public AbstractBackend {
    Q_OBJECT
public:
    explicit FrenchPollenBackend(QNetworkAccessManager *manager, QObject *parent = nullptr);
    ~FrenchPollenBackend() override;

    Q_INVOKABLE void fetchPollenData(const QList<int> &pollenIds, QString regionId, QString partRegionId);

protected:
    QString parsePollenData(QByteArray searchReply, QNetworkReply *reply) override;
    QJsonObject createResultPollenObject(const QJsonObject &pollenSourceNode, const QString &value);

private:
    QString regionId;

    QJsonObject getNodeForPollenId(const QJsonArray &risksArray, int pollenId);

#ifdef UNIT_TEST
    friend class PollenBackendTests; // to test non public methods
#endif
};

#endif // FRENCH_POLLEN_BACKEND_H
