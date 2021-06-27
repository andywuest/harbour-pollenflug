#include "abstractpollen.h"
#include "constants.h"

#include <QDebug>

AbstractPollen::AbstractPollen(int pollenId) {
    this->pollenId = pollenId;
}

QString AbstractPollen::getPollenName(int pollenId) {
    switch (pollenId) {
    case Pollen::Mugwort:
        return tr("Mugwort");
    case Pollen::Birch:
        return tr("Birch");
    case Pollen::Alder:
        return tr("Alder");
    case Pollen::AshTree:
        return tr("Ash Tree");
    case Pollen::Grass:
        return tr("Grass");
    case Pollen::Hazel:
        return tr("Hazel");
    case Pollen::Ambrosia:
        return tr("Ambrosia");
    case Pollen::Rye:
        return tr("Rye");
    case Pollen::Hornbeam:
        return tr("Hornbeam");
    case Pollen::Chestnut:
        return tr("Chestnut");
    case Pollen::Oak:
        return tr("Oak");
    case Pollen::Cypress:
        return tr("Cypress");
    case Pollen::Olive:
        return tr("Olive");
    case Pollen::Sorrel:
        return tr("Sorrel");
    case Pollen::Poplar:
        return tr("Poplar");
    case Pollen::Plantain:
        return tr("Plantain");
    case Pollen::Plane:
        return tr("Plane");
    case Pollen::Willow:
        return tr("Willow");
    case Pollen::Lime:
        return tr("Lime");
    case Pollen::Nettle:
        return tr("Nettle");
    }
    return QString("unsupported");
}

QString AbstractPollen::getPollenImageFileName(int pollenId) {
    return getInternalPollenName(pollenId).append(".svg");
}

QString AbstractPollen::getInternalPollenName(int pollenId) {
    switch (pollenId) {
    case Pollen::Mugwort:
        return "mugwort";
    case Pollen::Birch:
        return "birch";
    case Pollen::Alder:
        return "alder";
    case Pollen::AshTree:
        return "ashtree";
    case Pollen::Grass:
        return "grass";
    case Pollen::Hazel:
        return "hazel";
    case Pollen::Ambrosia:
        return "ambrosia";
    case Pollen::Rye:
        return "rye";
    case Pollen::Hornbeam:
        return "hornbeam";
    case Pollen::Chestnut:
        return "chestnut";
    case Pollen::Oak:
        return "oak";
    case Pollen::Cypress:
        return "cypress";
    case Pollen::Olive:
        return "olive";
    case Pollen::Sorrel:
        return "sorrel";
    case Pollen::Poplar:
        return "poplar";
    case Pollen::Plantain:
        return "plantain";
    case Pollen::Plane:
        return "plane";
    case Pollen::Willow:
        return "willow";
    case Pollen::Lime:
        return "lime";
    case Pollen::Nettle:
        return "nettle";
    }
    qDebug() << "Unsupported pollenId : " << pollenId;
    return QString("unsupported");
}
