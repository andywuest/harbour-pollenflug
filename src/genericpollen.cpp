#include "genericpollen.h"

void GenericPollen::GenericPollen(int pollenId, QString jsonLookupKey, QString pollenMapKey) {
    this->pollenId = pollenId,
    this->jsonLookupKey = jsonLookupKey;
    this->pollenMapKey = pollenMapKey;
}

int GenericPollen::getPollenId() {
  return this->pollenId;
}

QString GenericPollen::getJsonLookupKey() {
  return this->jsonLookupKey;
}

QString GenericPollen::getPollenMapKey() {
  return this->pollenMapKey;
}
