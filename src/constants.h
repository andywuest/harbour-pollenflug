#ifndef CONSTANTS_H
#define CONSTANTS_H

enum Pollen {
    Mugwort = 1, // Beifuss
    Birch = 2, // Birke
    Alder = 3, // Erle
    AshTree = 4, // Esche
    Grass = 5, // Graser
    Hazel = 6, // Hasel
    Ambrosia = 7, // Ambrosia
    Rye = 8, // Roggen
};

const char MIME_TYPE_JSON[] = "application/json";
const char USER_AGENT[] = "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:73.0) Gecko/20100101 Firefox/73.0";

const char GERMAN_POLLEN_API[] = "https://opendata.dwd.de/climate_environment/health/alerts/s31fg.json";
const char FRENCH_POLLEN_API[] = "https://www.pollens.fr/load_vigilance_map";

#endif // CONSTANTS_H
