#include "germanpollenbackend.h"

//#include <QDebug>
//#include <QFile>
//#include <QUrl>
//#include <QUrlQuery>
//#include <QUuid>
//#include <QJsonObject>
//#include <QJsonArray>
//#include <QDateTime>
//#include <QVariantMap>
//#include <QJsonDocument>


GermanPollenBackend::GermanPollenBackend(QNetworkAccessManager *manager, QObject *parent) : QObject(parent) {
    qDebug() << "Initializing German Pollen Backend...";
    this->manager = manager;
//    this->applicationName = applicationName;
//    this->applicationVersion = applicationVersion;
}

GermanPollenBackend::~GermanPollenBackend() {
    qDebug() << "Shutting down German Pollen Backend...";
}

QNetworkReply *GermanPollenBackend::executeGetRequest(const QUrl &url) {
    qDebug() << "AbstractDataBackend::executeGetRequest " << url;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, MIME_TYPE_JSON);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);

    return manager->get(request);
}

void GermanPollenBackend::handleRequestError(QNetworkReply::NetworkError error) {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    qWarning() << "AbstractDataBackend::handleRequestError:" << static_cast<int>(error) << reply->errorString() << reply->readAll();

    emit requestError("Return code: " + QString::number(static_cast<int>(error)) + " - " + reply->errorString());
}


void GermanPollenBackend::fetchPollenData() {
    qDebug() << "GermanPollenBackend::fetchPollenData";
    QNetworkReply *reply = executeGetRequest(QUrl(GERMAN_POLLEN_API));

    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(handleRequestError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT(handleFetchPollenDataFinished()));
}

void GermanPollenBackend::handleFetchPollenDataFinished() {
    qDebug() << "GermanPollenBackend::handleFetchPollenDataFinished";

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    reply->deleteLater();
    if (reply->error() != QNetworkReply::NoError) {
        return;
    }

    emit pollenDataAvailable(reply->readAll());
}

