#include "abstractpollenbackend.h"
#include "constants.h"

#include <QDebug>

AbstractPollenBackend::AbstractPollenBackend(QNetworkAccessManager *manager, QObject *parent)
    : QObject(parent) {
    qDebug() << "Initializing Pollen Backend...";
    this->manager = manager;
}

AbstractPollenBackend::~AbstractPollenBackend() {
    qDebug() << "Shutting down AbstractPollenBackend...";
}

void AbstractPollenBackend::handleRequestError(QNetworkReply::NetworkError error) {
    auto *reply = qobject_cast<QNetworkReply *>(sender());
    qWarning() << "AbstractPollenBackend::handleRequestError:" << static_cast<int>(error) << reply->errorString()
               << reply->readAll();

    emit requestError("Return code: " + QString::number(static_cast<int>(error)) + " - " + reply->errorString());
}
