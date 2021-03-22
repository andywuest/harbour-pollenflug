
// supported countries - order of countries in settings comboBox
var COUNTRY_GERMANY = 1;
var COUNTRY_FRANCE = 2;

var COUNTRY_MAP = [];
COUNTRY_MAP[1] = "Germany";
COUNTRY_MAP[2] = "France";

var MUGWORT_ID = 1;
var BIRCH_ID = 2;
var ALDER_ID = 3;
var ASH_TREE_ID = 4;
var GRASS_ID = 5;
var HAZEL_ID = 6;
var AMBROSIA_ID = 7;
var RYE_ID = 8;

var MAX_SCALE_ELEMENTS = 3;

function createPollenItem(id, label, imageSource) {
    var entry = {

    }
    entry.id = id
    entry.label = label
    entry.imageSource = imageSource
    return entry
}

function buildPollenList() {
    var pollenList = []
    pollenList.push(createPollenItem(MUGWORT_ID, qsTr("Mugwort"), // Beifuß
                                     "../icons/beifuss.svg"))
    pollenList.push(createPollenItem(BIRCH_ID, qsTr("Birch"), // Birke
                                     "../icons/birke.svg"))
    pollenList.push(createPollenItem(ALDER_ID, qsTr("Alder"), // Erle
                                     "../icons/erle.svg"))
    pollenList.push(createPollenItem(ASH_TREE_ID, qsTr("Ash Tree"), // Esche
                                     "../icons/esche.svg"))
    pollenList.push(createPollenItem(GRASS_ID, qsTr("Grass"), // Gräser
                                     "../icons/graeser.svg"))
    pollenList.push(createPollenItem(HAZEL_ID, qsTr("Hazel"), // Hasel
                                     "../icons/hasel.svg"))
    pollenList.push(createPollenItem(AMBROSIA_ID, qsTr("Ambrosia"), // Ambrosia
                                     "../icons/ambrosia.svg"))
    pollenList.push(createPollenItem(RYE_ID, qsTr("Rye"), // Roggen
                                     "../icons/roggen.svg"))
    return pollenList
}

function buildPollenMap(pollenList) {
    var pollenMap = []
    for (var i = 0; i < pollenList.length; i++) {
        pollenMap[pollenList[i].id] = pollenList[i]
    }
    return pollenMap
}

var POLLEN_DATA_LIST = buildPollenList()
var POLLEN_DATA_MAP = buildPollenMap(POLLEN_DATA_LIST)

function buildGermanRegionIdToPartRegions() {
    var partRegionIdMap = []
    partRegionIdMap[10] = [qsTr("Inseln und Marschen"), qsTr(
                               "Geest, Schleswig-Holstein und Hamburg")]
    partRegionIdMap[30] = [qsTr("Westl. Niedersachsen/Bremen"), qsTr(
                               "Östl. Niedersachsen")]
    partRegionIdMap[40] = [qsTr("Rhein.-Westfäl. Tiefland"), qsTr(
                               "Ostwestfalen"), qsTr("Mittelgebirge NRW")]
    partRegionIdMap[60] = [qsTr("Tiefland Sachsen-Anhalt"), qsTr("Harz")]
    partRegionIdMap[70] = [qsTr("Tiefland Thüringen"), qsTr(
                               "Mittelgebirge Thüringen")]
    partRegionIdMap[80] = [qsTr("Tiefland Sachsen"), qsTr(
                               "Mittelgebirge Sachsen")]
    partRegionIdMap[90] = [qsTr("Nordhessen und hess. Mittelgebirge"), qsTr(
                               "Rhein-Main")]
    partRegionIdMap[100] = [qsTr("Rhein, Pfalz, Nahe und Mosel"), qsTr(
                                "Mittelgebirgsbereich Rheinland-Pfalz"), qsTr(
                                "Saarland")]
    partRegionIdMap[110] = [qsTr("Oberrhein und unteres Neckartal"), qsTr(
                                "Hohenlohe/mittlerer Neckar/Oberschwaben"), qsTr(
                                "Mittelgebirge Baden-Württemberg")]
    partRegionIdMap[120] = [qsTr("Allgäu/Oberbayern/Bay. Wald"), qsTr(
                                "Donauniederungen"), qsTr(
                                "Bayern n. der Donau, o. Bayr. Wald, o. Mainfranken"), qsTr(
                                "Mainfranken")]
    return partRegionIdMap
}

var GERMAN_REGION_ID_TO_PART_REGIONS = buildGermanRegionIdToPartRegions()

function isDataUpToDate(jsonResponse) {
    var nextUpdate = jsonResponse.next_update.replace(" Uhr", "")
    var now = new Date()
    return (now < nextUpdate)
}
