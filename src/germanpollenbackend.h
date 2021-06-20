#ifndef GERMAN_POLLEN_BACKEND_H
#define GERMAN_POLLEN_BACKEND_H

#include <QObject>

#include "constants.h"
#include "abstractbackend.h"

class GermanPollenBackend : public AbstractBackend {
    Q_OBJECT
public:
    explicit  GermanPollenBackend(QNetworkAccessManager *manager, QObject *parent = nullptr);
    ~GermanPollenBackend();

    Q_INVOKABLE void fetchPollenData(const QList<int> &pollenIds, QString regionId, QString partRegionId);

protected:
    QString parsePollenData(QByteArray searchReply); // TODO rename -> abstract in basisklasse
    QJsonObject createResultPollenObject(QJsonObject pollenSourceNode, QString dayString);

private slots:
    void handleFetchPollenDataFinished(); // virtual?

private:
    int regionId;
    int partRegionId;

    bool isRegionNodeFound(int regionId, int partRegionId);
    QJsonObject getNodeForPollenId(QJsonObject pollenNode, int pollenId);

};

#endif // GERMAN_POLLEN_BACKEND_H
