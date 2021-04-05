import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import "../js/constants.js" as Constants
import "../js/functions.js" as Functions

Column {
    id: settingsColumn
    height: childrenRect.height

    function updateConfiguration() {
        if (departementsMenu.children[departementFranceComboBox.currentIndex]) {
            pollenflugSettings.departement = departementsMenu.children[departementFranceComboBox.currentIndex].value;
            console.log("[FR] departement : " + pollenflugSettings.departement)
        }
    }

    ComboBox {
        id: departementFranceComboBox
        //: SettingsPage state
        label: qsTr("Departement")
        currentIndex: pollenflugSettings.region
        //: SettingsPage region description
        description: qsTr("Select the departement where you live")
        menu: ContextMenu {
            id: departementsMenu
            Repeater {
                width: parent.width
                model: departementsModel
                delegate: MenuItem {
                    readonly property string value : model.value
                    text: model.label
                }
            }
        }

        Component.onCompleted: {
            console.log("read config value departement : " + pollenflugSettings.departement);
            Functions.updateComboBoxSelection(departementFranceComboBox, pollenflugSettings.departement);
        }
    }

    ListModel {
        id: departementsModel
        ListElement { value: "01"; label: qsTr("Ain") }
        ListElement { value: "02"; label: qsTr("Aisne") }
        ListElement { value: "03"; label: qsTr("Allier") }
        ListElement { value: "04"; label: qsTr("Alpes-de-Haute-Provence") }
        ListElement { value: "05"; label: qsTr("Hautes-Alpes") }
        ListElement { value: "06"; label: qsTr("Alpes-Maritimes") }
        ListElement { value: "07"; label: qsTr("Ardèche") }
        ListElement { value: "08"; label: qsTr("Ardennes") }
        ListElement { value: "09"; label: qsTr("Ariège") }
        ListElement { value: "10"; label: qsTr("Aube") }
        ListElement { value: "11"; label: qsTr("Aude") }
        ListElement { value: "12"; label: qsTr("Aveyron") }
        ListElement { value: "13"; label: qsTr("Bouches-du-Rhône") }
        ListElement { value: "14"; label: qsTr("Calvados") }
        ListElement { value: "15"; label: qsTr("Cantal") }
        ListElement { value: "16"; label: qsTr("Charente") }
        ListElement { value: "17"; label: qsTr("Charente-Maritime") }
        ListElement { value: "18"; label: qsTr("Cher") }
        ListElement { value: "19"; label: qsTr("Corrèze") }
        ListElement { value: "20"; label: qsTr("Corse") }
        ListElement { value: "21"; label: qsTr("Côte-d'Or") }
        ListElement { value: "22"; label: qsTr("Côtes-d'Armor") }
        ListElement { value: "23"; label: qsTr("Creuse") }
        ListElement { value: "24"; label: qsTr("Dordogne") }
        ListElement { value: "25"; label: qsTr("Doubs") }
        ListElement { value: "26"; label: qsTr("Drôme") }
        ListElement { value: "27"; label: qsTr("Eure") }
        ListElement { value: "28"; label: qsTr("Eure-et-Loir") }
        ListElement { value: "29"; label: qsTr("Finistère") }
        ListElement { value: "30"; label: qsTr("Gard") }
        ListElement { value: "31"; label: qsTr("Haute-Garonne") }
        ListElement { value: "32"; label: qsTr("Gers") }
        ListElement { value: "33"; label: qsTr("Gironde") }
        ListElement { value: "34"; label: qsTr("Hérault") }
        ListElement { value: "35"; label: qsTr("Ille-et-Vilaine") }
        ListElement { value: "36"; label: qsTr("Indre") }
        ListElement { value: "37"; label: qsTr("Indre-et-Loire") }
        ListElement { value: "38"; label: qsTr("Isère") }
        ListElement { value: "39"; label: qsTr("Jura") }
        ListElement { value: "40"; label: qsTr("Landes") }
        ListElement { value: "41"; label: qsTr("Loir-et-Cher") }
        ListElement { value: "42"; label: qsTr("Loire") }
        ListElement { value: "43"; label: qsTr("Haute-Loire") }
        ListElement { value: "44"; label: qsTr("Loire-Atlantique") }
        ListElement { value: "45"; label: qsTr("Loiret") }
        ListElement { value: "46"; label: qsTr("Lot") }
        ListElement { value: "47"; label: qsTr("Lot-et-Garonne") }
        ListElement { value: "48"; label: qsTr("Lozère") }
        ListElement { value: "49"; label: qsTr("Maine-et-Loire") }
        ListElement { value: "50"; label: qsTr("Manche") }
        ListElement { value: "51"; label: qsTr("Marne") }
        ListElement { value: "52"; label: qsTr("Haute-Marne") }
        ListElement { value: "53"; label: qsTr("Mayenne") }
        ListElement { value: "54"; label: qsTr("Meurthe-et-Moselle") }
        ListElement { value: "55"; label: qsTr("Meuse") }
        ListElement { value: "56"; label: qsTr("Morbihan") }
        ListElement { value: "57"; label: qsTr("Moselle") }
        ListElement { value: "58"; label: qsTr("Nièvre") }
        ListElement { value: "59"; label: qsTr("Nord") }
        ListElement { value: "60"; label: qsTr("Oise") }
        ListElement { value: "61"; label: qsTr("Orne") }
        ListElement { value: "62"; label: qsTr("Pas-de-Calais") }
        ListElement { value: "63"; label: qsTr("Puy-de-Dôme") }
        ListElement { value: "64"; label: qsTr("Pyrénées-Atlantiques") }
        ListElement { value: "65"; label: qsTr("Hautes-Pyrénées") }
        ListElement { value: "66"; label: qsTr("Pyrénées-Orientales") }
        ListElement { value: "67"; label: qsTr("Bas-Rhin") }
        ListElement { value: "68"; label: qsTr("Haut-Rhin") }
        ListElement { value: "69"; label: qsTr("Rhône") }
        ListElement { value: "70"; label: qsTr("Haute-Saône") }
        ListElement { value: "71"; label: qsTr("Saône-et-Loire") }
        ListElement { value: "72"; label: qsTr("Sarthe") }
        ListElement { value: "73"; label: qsTr("Savoie") }
        ListElement { value: "74"; label: qsTr("Haute-Savoie") }
        ListElement { value: "75"; label: qsTr("Paris") }
        ListElement { value: "76"; label: qsTr("Seine-Maritime") }
        ListElement { value: "77"; label: qsTr("Seine-et-Marne") }
        ListElement { value: "78"; label: qsTr("Yvelines") }
        ListElement { value: "79"; label: qsTr("Deux-Sèvres") }
        ListElement { value: "80"; label: qsTr("Somme") }
        ListElement { value: "81"; label: qsTr("Tarn") }
        ListElement { value: "82"; label: qsTr("Tarn-et-Garonne") }
        ListElement { value: "83"; label: qsTr("Var") }
        ListElement { value: "84"; label: qsTr("Vaucluse") }
        ListElement { value: "85"; label: qsTr("Vendée") }
        ListElement { value: "86"; label: qsTr("Vienne") }
        ListElement { value: "87"; label: qsTr("Haute-Vienne") }
        ListElement { value: "88"; label: qsTr("Vosges") }
        ListElement { value: "89"; label: qsTr("Yonne") }
        ListElement { value: "90"; label: qsTr("Territoire de Belfort") }
        ListElement { value: "91"; label: qsTr("Essonne") }
        ListElement { value: "92"; label: qsTr("Hauts-de-Seine") }
        ListElement { value: "93"; label: qsTr("Seine-Saint-Denis") }
        ListElement { value: "94"; label: qsTr("Val-de-Marne") }
        ListElement { value: "95"; label: qsTr("Val-d'Oise") }
        ListElement { value: "99"; label: qsTr("Andorra") }
    }

    Component.onCompleted: {
        console.log("[FR] read config value : " + pollenflugSettings.departement);
        departementFranceComboBox.currentIndex = pollenflugSettings.departement;
    }

}

