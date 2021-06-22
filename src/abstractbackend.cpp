#include "abstractbackend.h"
#include "constants.h"

AbstractBackend::AbstractBackend(QNetworkAccessManager *manager, QObject *parent)
    : QObject(parent) {
    qDebug() << "Initializing Abstract Pollen Backend...";
    this->manager = manager;
}

AbstractBackend::~AbstractBackend() {
    qDebug() << "Shutting down Abstract Pollen Backend...";
}

QNetworkReply *AbstractBackend::executeGetRequest(const QUrl &url) {
    qDebug() << "FrenchPollenBackend::executeGetRequest " << url;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, MIME_TYPE_JSON);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);

    return manager->get(request);
}

void AbstractBackend::handleRequestError(QNetworkReply::NetworkError error) {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    qWarning() << "GermanPollenBackend::handleRequestError:" << static_cast<int>(error) << reply->errorString()
               << reply->readAll();

    emit requestError("Return code: " + QString::number(static_cast<int>(error)) + " - " + reply->errorString());
}

void AbstractBackend::handleFetchPollenDataFinished() {
    qDebug() << "AbstractBackend::handleFetchPollenDataFinished";

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    reply->deleteLater();
    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    emit pollenDataAvailable(parsePollenData(reply->readAll()));
}

void AbstractBackend::addPollenData(int pollenId, QString jsonLookupKey, QString pollenMapKey) {
    QSharedPointer<GenericPollen> pointer(new GenericPollen(pollenId, jsonLookupKey, pollenMapKey));
    this->pollenIdToPollenData.insert(pollenId, pointer);
}

bool AbstractBackend::isPollenDataProvided(int pollenId) {
    // TODO for some reason the map contains an entry for a not supported pollenId
    // with a null value
    return this->pollenIdToPollenData.contains(pollenId) && this->pollenIdToPollenData[pollenId] != nullptr;
}

QString AbstractBackend::getPollenName(int pollenId) {
    return AbstractPollen::getPollenName(pollenId);
}

QString AbstractBackend::getPollenImageName(int pollenId) {
    return AbstractPollen::getPollenImageFileName(pollenId);
}

QList<int> AbstractBackend::removeUnsupportedPollens(const QList<int> &pollenIds) {
    QList<int> supportedPollenIds;
    for (auto pollenId : pollenIds) {
        if (isPollenDataProvided(pollenId)) {
            supportedPollenIds.append(pollenId);
        }
    }
    return supportedPollenIds;
}
