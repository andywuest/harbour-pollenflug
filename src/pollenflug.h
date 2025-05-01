#ifndef POLLENFLUG_H
#define POLLENFLUG_H

#include <QNetworkAccessManager>
#include <QNetworkConfigurationManager>
#include <QObject>
#include <QSettings>
#include <QVariant>

#include "frenchpollenbackend.h"
#include "germanpollenbackend.h"
#include "swisspollenbackend.h"

class Pollenflug : public QObject {
    Q_OBJECT
public:
    explicit Pollenflug(QObject *parent = nullptr);
    ~Pollenflug() = default;
    GermanPollenBackend *getGermanPollenBackend();
    FrenchPollenBackend *getFrenchPollenBackend();
    SwissPollenBackend *getSwissPollenBackend();

signals:

public slots:

private:
    QNetworkAccessManager *const networkAccessManager;
    QNetworkConfigurationManager *const networkConfigurationManager;

    // pollen backends
    GermanPollenBackend *germanPollenBackend;
    FrenchPollenBackend *frenchPollenBackend;
    SwissPollenBackend *swissPollenBackend;

    QSettings settings;
};

#endif // POLLENFLUG_H
