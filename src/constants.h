#ifndef CONSTANTS_H
#define CONSTANTS_H

enum Pollen {
    Mugwort = 1,   // Beifuss
    Birch = 2,     // Birke
    Alder = 3,     // Erle
    AshTree = 4,   // Esche
    Grass = 5,     // Graser
    Hazel = 6,     // Hasel
    Ambrosia = 7,  // Ambrosia
    Rye = 8,       // Roggen
    Hornbeam = 9,  // Buche
    Chestnut = 10, // Kastanie
    Oak = 11,      // Eiche
    Cypress = 12,  // Zypresse
    Olive = 13,    // Olive
    Sorrel = 14,   // Sauerampfer
    Poplar = 15,   // Pappel
    Plantain = 16, // Wegerich
    Plane = 17,    // Platane
    Willow = 18,   // Weide
    Lime = 19,     // Linde
    Nettle = 20    // Brennessel
};

const char MIME_TYPE_JSON[] = "application/json";
const char USER_AGENT[] = "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:73.0) "
                          "Gecko/20100101 Firefox/73.0";

const char POLLEN_API_GERMANY[] = "https://opendata.dwd.de/climate_environment/health/alerts/s31fg.json";
const char POLLEN_API_FRANCE[] = "https://www.pollens.fr/load_vigilance_map";

const char MAP_URL_GERMANY[] = "https://www.dwd.de/DWD/warnungen/medizin/pollen/pollen_1_%1.png";
const char MAP_URL_FRANCE[] = "https://www.pollens.fr/uploads/historic/2021/%1.png";

#endif // CONSTANTS_H
