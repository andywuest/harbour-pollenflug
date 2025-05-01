
// supported countries - order of countries in settings comboBox
var COUNTRY_GERMANY = 1;
var COUNTRY_FRANCE = 2;
var COUNTRY_SWITZERLAND = 3;

var COUNTRY_MAP = [];
COUNTRY_MAP[1] = "Germany";
COUNTRY_MAP[2] = "France";
COUNTRY_MAP[3] = "Switzerland";

var MUGWORT_ID = 1;
var BIRCH_ID = 2;
var ALDER_ID = 3;
var ASH_TREE_ID = 4;
var GRASS_ID = 5;
var HAZEL_ID = 6;
var AMBROSIA_ID = 7;
var RYE_ID = 8;
var HORNBEAM_ID = 9;
var CHESTNUT_ID = 10;
var OAK_ID = 11;
var CYPRESS_ID = 12;
var OLIVE_ID = 13;
var SORREL_ID = 14;
var POPLAR_ID = 15;
var PLANTAIN_ID = 16;
var PLANE_ID = 17;
var WILLOW_ID = 18;
var LIME_ID = 19;
var NETTLE_ID = 20;

var MAX_SCALE_ELEMENTS = 3;

function createPollenItem(id, label, imageSource) {
    var entry = {

    }
    entry.id = id
    // entry.label = label
    // entry.imageSource = imageSource
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
    pollenList.push(createPollenItem(HORNBEAM_ID, qsTr("Hornbeam"), // Buche
        "../icons/xxx.svg"))
    pollenList.push(createPollenItem(CHESTNUT_ID, qsTr("Chestnut"), // Kastanie
        "../icons/xxx.svg"))
    pollenList.push(createPollenItem(OAK_ID, qsTr("Hornbeam"), // Eiche
        "../icons/xxx.svg"))
    pollenList.push(createPollenItem(CYPRESS_ID, qsTr("Hornbeam"), // Zypresse
        "../icons/xxx.svg"))
    pollenList.push(createPollenItem(OLIVE_ID, qsTr("Olive"), // Olive
        "../icons/xxx.svg"))
    pollenList.push(createPollenItem(SORREL_ID, qsTr("Sorrel"), // Sauerampfer
        "../icons/xxx.svg"))
    pollenList.push(createPollenItem(POPLAR_ID, qsTr("Poplar"), // Pappel
        "../icons/xxx.svg"))
    pollenList.push(createPollenItem(PLANTAIN_ID, qsTr("Plantain"), // Wegerich
        "../icons/xxx.svg"))
    pollenList.push(createPollenItem(PLANE_ID, qsTr("Plane"), // Platane
        "../icons/xxx.svg"))
    pollenList.push(createPollenItem(WILLOW_ID, qsTr("Willow"), // Weide
        "../icons/xxx.svg"))
    pollenList.push(createPollenItem(LIME_ID, qsTr("Lime"), // Linde
        "../icons/xxx.svg"))
    pollenList.push(createPollenItem(NETTLE_ID, qsTr("Nettle"), // Brennnessel
        "../icons/oak.svg")) // TODO fix icon

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

var DEPARTEMENT_AIN = '01';
var DEPARTEMENT_AISNE = '02';
var DEPARTEMENT_ALLIER = '03';
var DEPARTEMENT_ALPES_DE_HAUTE_PROVENCE = '04';
var DEPARTEMENT_HAUTES_ALPES = '05';
var DEPARTEMENT_ALPES_MARITIME = '06';
var DEPARTEMENT_ARDECHE = '07';
var DEPARTEMENT_ARDENNES = '08';
var DEPARTEMENT_ARIEGE = '09';
var DEPARTEMENT_AUBE = '10';
var DEPARTEMENT_AUDE = '11';
var DEPARTEMENT_AVEYRON = '12';
var DEPARTEMENT_BOUCHES_DE_RHONE = '13';
var DEPARTEMENT_CALVADOS = '14';
var DEPARTEMENT_CANTAL = '15';
var DEPARTEMENT_CHARENTE = '16';
var DEPARTEMENT_CHARENTE_MARITIME = '17';
var DEPARTEMENT_CHER ='18';
var DEPARTEMENT_CORREZE = '19';
var DEPARTEMENT_CORSE = '20';
var DEPARTEMENT_COTE_DOR = '21';
var DEPARTEMENT_COTES_DAMOR = '22';
var DEPARTEMENT_CREUSE = '23';
var DEPARTEMENT_DORDOGNE = '24';
var DEPARTEMENT_DOUBS = '25';
var DEPARTEMENT_DROME = '26';
var DEPARTEMENT_EURE = '27';
var DEPARTEMENT_EURE_ET_LOIR = '28';
var DEPARTEMENT_FINISTERE = '29';
var DEPARTEMENT_GARD = '30';
var DEPARTEMENT_HAUTE_GARONNE = '31';
var DEPARTEMENT_GERS = '32';
var DEPARTEMENT_GIRONDE = '33';
var DEPARTEMENT_HERAULT = '34';
var DEPARTEMENT_ILLE_ET_VILAINE = '35';
var DEPARTEMENT_INDRE = '36';
var DEPARTEMENT_INDRE_ET_LOIRE = '37';
var DEPARTEMENT_ISERE = '38';
var DEPARTEMENT_JURA = '39';
var DEPARTEMENT_LANDES = '40';
var DEPARTEMENT_LOIR_ET_CHER = '41';
var DEPARTEMENT_LOIRE = '42';
var DEPARTEMENT_HAUTE_LOIRE = '43';
var DEPARTEMENT_LOIRE_ATLANTIQUE = '44';
var DEPARTEMENT_LOIRET = '45';
var DEPARTEMENT_LOT = '46';
var DEPARTEMENT_LOT_ET_GARONNE = '47';
var DEPARTEMENT_LOZERE = '48';
var DEPARTEMENT_MAINE_ET_LOIRE = '49';
var DEPARTEMENT_MANCHE = '50';
var DEPARTEMENT_MARNE = '51';
var DEPARTEMENT_HAUTE_MARNE = '52';

//<option value="49"> Maine-et-Loire </option>
//                                                            <option value="50"> Manche </option>
//                                                            <option value="51"> Marne </option>
//                                                            <option value="52"> Haute-Marne </option>
//                                                            <option value="53"> Mayenne </option>
//                                                            <option value="54"> Meurthe-et-Moselle </option>
//                                                            <option value="55"> Meuse </option>
//                                                            <option value="56"> Morbihan </option>
//                                                            <option value="57"> Moselle </option>
//                                                            <option value="58"> Nièvre </option>
//                                                            <option value="59"> Nord </option>
//                                                            <option value="60"> Oise </option>
//                                                            <option value="61"> Orne </option>
//                                                            <option value="62"> Pas-de-Calais </option>
//                                                            <option value="63"> Puy-de-Dôme </option>
//                                                            <option value="64"> Pyrénées-Atlantiques </option>
//                                                            <option value="65"> Hautes-Pyrénées </option>
//                                                            <option value="66"> Pyrénées-Orientales </option>
//                                                            <option value="67"> Bas-Rhin </option>
//                                                            <option value="68"> Haut-Rhin </option>
//                                                            <option value="69"> Rhône </option>
//                                                            <option value="70"> Haute-Saône </option>
//                                                            <option value="71"> Saône-et-Loire </option>
//                                                            <option value="72"> Sarthe </option>
//                                                            <option value="73"> Savoie </option>
//                                                            <option value="74"> Haute-Savoie </option>
//                                                            <option value="75"> Paris </option>
//                                                            <option value="76"> Seine-Maritime </option>
//                                                            <option value="77"> Seine-et-Marne </option>
//                                                            <option value="78"> Yvelines </option>
//                                                            <option value="79"> Deux-Sèvres </option>
//                                                            <option value="80"> Somme </option>
//                                                            <option value="81"> Tarn </option>
//                                                            <option value="82"> Tarn-et-Garonne </option>
//                                                            <option value="83"> Var </option>
//                                                            <option value="84"> Vaucluse </option>
//                                                            <option value="85"> Vendée </option>
//                                                            <option value="86"> Vienne </option>
//                                                            <option value="87"> Haute-Vienne </option>
//                                                            <option value="88"> Vosges </option>
//                                                            <option value="89"> Yonne </option>
//                                                            <option value="90"> Territoire de Belfort </option>
//                                                            <option value="91"> Essonne </option>
//                                                            <option value="92"> Hauts-de-Seine </option>
//                                                            <option value="93"> Seine-Saint-Denis </option>
//                                                            <option value="94"> Val-de-Marne </option>
//                                                            <option value="95"> Val-d&#039;Oise </option>
//                                                            <option value="99"> Andorra </option>

