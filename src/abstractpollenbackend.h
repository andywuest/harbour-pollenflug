#ifndef ABSTRACT_POLLEN_BACKEND_H
#define ABSTRACT_POLLEN_BACKEND_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

#include "abstractpollen.h"

class AbstractPollenBackend : public QObject {
    Q_OBJECT
public:
    explicit AbstractPollenBackend(QNetworkAccessManager *manager, QObject *parent = nullptr);
    ~AbstractPollenBackend() = 0;

    // signals for the qml part
    Q_SIGNAL void requestError(const QString &errorMessage);
    Q_SIGNAL void pollenDataAvailable(const QString &reply);

protected:
    QNetworkAccessManager *manager;

protected slots:
    void handleRequestError(QNetworkReply::NetworkError error);
};

#endif // ABSTRACT_POLLEN_BACKEND_H