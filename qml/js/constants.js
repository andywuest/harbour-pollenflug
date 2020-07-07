
var MUGWORT_ID = 1
var BIRCH_ID = 2
var ALDER_ID = 3
var ASH_TREE_ID = 4
var GRASS_ID = 5
var HAZEL_ID = 6
var AMBROSIA_ID = 7
var RYE_ID = 8

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
    pollenList.push(createPollenItem(MUGWORT_ID, qsTr("Beifuß"),
                                     "../icons/beifuss.svg"))
    pollenList.push(createPollenItem(BIRCH_ID, qsTr("Birke"),
                                     "../icons/birke.svg"))
    pollenList.push(createPollenItem(ALDER_ID, qsTr("Erle"),
                                     "../icons/erle.svg"))
    pollenList.push(createPollenItem(ASH_TREE_ID, qsTr("Esche"),
                                     "../icons/esche.svg"))
    pollenList.push(createPollenItem(GRASS_ID, qsTr("Gräser"),
                                     "../icons/graeser.svg"))
    pollenList.push(createPollenItem(HAZEL_ID, qsTr("Hasel"),
                                     "../icons/hasel.svg"))
    pollenList.push(createPollenItem(AMBROSIA_ID, qsTr("Ambrosia"),
                                     "../icons/ambrosia.svg"))
    pollenList.push(createPollenItem(RYE_ID, qsTr("Roggen"),
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

function findPollenNodeXXXXXXX(regionId, partRegionId, contentArray) {
    if (contentArray.length > 0) {
        for (var i = 0; i < contentArray.length; i++) {
            var node = contentArray[i]
            if (regionId === node.region_id) {
                if (node.partregion_id === -1) {
                    return node.Pollen
                } else if (partRegionId === node.partregion_id) {
                    return node.Pollen
                }
            }
        }
    }
}

function isDataUpToDate(jsonResponse) {
    var nextUpdate = jsonResponse.next_update.replace(" Uhr", "")
    var now = new Date()
    return (now < nextUpdate)
}

function buildPollutionIndexMap() {
    var map = [];
    map["0"] = 0;
    map["0-1"] = 1;
    map["1"] = 2;
    map["1-2"] = 3;
    map["2"] = 4;
    map["2-3"] = 5;
    map["3"] = 6;
    return map;
}

function buildPollutionLabelMap() {
    var map = [];
    map["0"] = qsTr("keine Belastung");
    map["0-1"] = qsTr("keine bis geringe Belastung");
    map["1"] = qsTr("geringe Belastung");
    map["1-2"] = qsTr("geringe bis mittlere Belastung");
    map["2"] = qsTr("mittlere Belastung");
    map["2-3"] = qsTr("mittlere bis hohe Belastung");
    map["3"] = qsTr("hohe Belastung");
    return map;
}


function buildPollenIdToNameMap() {
    var map = [];
    // not to be translated
    map[MUGWORT_ID] = "Beifuss"
    map[BIRCH_ID] = "Birke"
    map[ALDER_ID] = "Erle"
    map[ASH_TREE_ID] = "Esche"
    map[GRASS_ID] = "Graeser"
    map[HAZEL_ID] = "Hasel"
    map[AMBROSIA_ID] = "Ambrosia"
    map[RYE_ID] = "Roggen"

    return map;
}

var POLLEN_ID_TO_NAME_MAP = buildPollenIdToNameMap();
var POLLUTION_ID_TO_LABEL = buildPollutionLabelMap();
var POLLUTION_ID_TO_INDEX = buildPollutionIndexMap();

function getPollution(pollenId, pollenNode) {
    var pollenKey = POLLEN_ID_TO_NAME_MAP['' + pollenId];
    var result = pollenNode[pollenKey];
    return pollenNode[pollenKey];
}
