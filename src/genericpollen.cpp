#include "genericpollen.h"

GenericPollen::GenericPollen(int pollenId, QString jsonLookupKey, QString pollenMapKey)
    : AbstractPollen(pollenId) {
    this->jsonLookupKey = jsonLookupKey;
    this->pollenMapKey = pollenMapKey;
}

GenericPollen::~GenericPollen() {
}

QString GenericPollen::getJsonLookupKey() {
    return this->jsonLookupKey;
}

QString GenericPollen::getPollenMapKey() {
    return this->pollenMapKey;
}
