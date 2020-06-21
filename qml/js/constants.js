.pragma library

var MUGWORT_ID = 1
var BIRCH_ID = 2
var ALDER_ID = 3
var ASH_TREE_ID = 4
var GRASS_ID = 5
var HAZEL_ID = 6
var AMBROSIA_ID = 7
var RYE_ID = 8

function createPollenItem(id, label, imageSource) {
    var entry = {}
    entry.id = id
    entry.label = label
    entry.imageSource = imageSource
    return entry
}

function buildPollenList() {
    var pollenList = []
    pollenList.push(createPollenItem(MUGWORT_ID, qsTr("Beifuß"), "../icons/beifuss.svg"))
    pollenList.push(createPollenItem(BIRCH_ID, qsTr("Birke"), "../icons/birke.svg"))
    pollenList.push(createPollenItem(ALDER_ID, qsTr("Erle"), "../icons/erle.svg"))
    pollenList.push(createPollenItem(ASH_TREE_ID, qsTr("Esche"), "../icons/esche.svg"))
    pollenList.push(createPollenItem(GRASS_ID, qsTr("Gräser"), "../icons/graeser.svg"))
    pollenList.push(createPollenItem(HAZEL_ID, qsTr("Hasel"), "../icons/hasel.svg"))
    pollenList.push(createPollenItem(AMBROSIA_ID, qsTr("Ambrosia"), "../icons/ambrosia.svg"))
    pollenList.push(createPollenItem(RYE_ID, qsTr("Roggen"), "../icons/roggen.svg"))
    return pollenList;
}

function buildPollenMap(pollenList) {
    var pollenMap = [];
    for (var i = 0; i < pollenList.length; i++) {
        pollenMap[pollenList[i].id] = pollenList[i];
    }
    return pollenMap;
}

var POLLEN_DATA_LIST = buildPollenList();
var POLLEN_DATA_MAP = buildPollenMap(POLLEN_DATA_LIST);
