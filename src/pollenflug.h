#ifndef POLLENFLUG_H
#define POLLENFLUG_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkConfigurationManager>
#include <QSettings>

#include "germanpollenbackend.h"
// #include "onvistanews.h"

class Pollenflug : public QObject {
    Q_OBJECT
public:
    explicit Pollenflug(QObject *parent = nullptr);
    ~Pollenflug();
    GermanPollenBackend *getGermanPollenBackend();

signals:

public slots:

private:
    QNetworkAccessManager * const networkAccessManager;
    QNetworkConfigurationManager * const networkConfigurationManager;

    // pollen backends
    GermanPollenBackend *germanPollenBackend;

    QSettings settings;

};

#endif // POLLENFLUG_H
