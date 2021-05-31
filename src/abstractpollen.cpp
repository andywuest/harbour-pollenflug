#include "abstractpollen.h"
#include "constants.h"

void AbstractPollen::getPollenName(int pollenId) {
    switch (pollenId) {
        case Pollen::Mugwort: return tr("Mugwort");
        case Pollen::Birch: return tr("Birch");
        case Pollen::Alder: return tr("Alder");
        case Pollen::Ash: return tr("Ash Tree");
        case Pollen::Grass: return tr("Grass");
        case Pollen::Hazel: return tr("Hazel");
        case Pollen::Ambrosia: return tr("Ambrosia");
        case Pollen::Rye: return tr("Rye");
        case Pollen::Hornbeam: return tr("Hornbeam");
        case Pollen::Chestnut: return tr("Chestnut");
        case Pollen::Oak: return tr("Oak");
        case Pollen::Cypress: return tr("Cypress");
        case Pollen::Olive: return tr("Olive");
        case Pollen::Sorrel: return tr("Sorrel");
        case Pollen::Poplar: return tr("Poplar");
        case Pollen::Plantain: return tr("Plantain");
        case Pollen::Plane: return tr("Plane");
        case Pollen::Willow: return tr("Willow");
        case Pollen::Lime: return tr("Lime");
        case Pollen::Nettle: return tr("Nettle");
    }

    return QString("unsupported");
}