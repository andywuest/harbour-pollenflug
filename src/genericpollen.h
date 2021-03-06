#ifndef GENERIC_POLLEN_H
#define GENERIC_POLLEN_H

#include "abstractpollen.h"

class GenericPollen : public AbstractPollen {
public:
    explicit GenericPollen(int pollenId, const QString &jsonLookupKey, const QString &pollenMapKey);
    ~GenericPollen() override;

    QString getJsonLookupKey();
    QString getPollenMapKey();

private:
    QString jsonLookupKey;
    QString pollenMapKey;
};

#endif // GENERIC_POLLEN_H
