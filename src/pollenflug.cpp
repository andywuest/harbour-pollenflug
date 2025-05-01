/*
 * harbour-pollenflug - Sailfish OS Version
 * Copyright © 2020 Andreas Wüst (andreas.wuest.freelancer@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "pollenflug.h"

Pollenflug::Pollenflug(QObject *parent)
    : QObject(parent)
    , networkAccessManager(new QNetworkAccessManager(this))
    , networkConfigurationManager(new QNetworkConfigurationManager(this))
    , settings("harbour-pollenflug", "settings") {
    // pollen backends
    germanPollenBackend = new GermanPollenBackend(this->networkAccessManager, this);
    frenchPollenBackend = new FrenchPollenBackend(this->networkAccessManager, this);
    swissPollenBackend = new SwissPollenBackend(this->networkAccessManager, this);
}

GermanPollenBackend *Pollenflug::getGermanPollenBackend() {
    return this->germanPollenBackend;
}

FrenchPollenBackend *Pollenflug::getFrenchPollenBackend() {
    return this->frenchPollenBackend;
}

SwissPollenBackend *Pollenflug::getSwissPollenBackend() {
    return this->swissPollenBackend;
}
