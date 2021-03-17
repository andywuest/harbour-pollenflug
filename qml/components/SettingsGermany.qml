import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import "../js/functions.js" as Functions
import "../js/constants.js" as Constants

Column {
    id: settingsColumn
    height: childrenRect.height

    property var partRegionNames: []

    function updateConfiguration() {
        pollenflugSettings.region = stateGermanyComboBox.currentIndex;
        pollenflugSettings.partRegion = partRegionGermanyComboBox.currentIndex;
        console.log("[DE] region : " + pollenflugSettings.region)
        console.log("[DE] partRegion : " + pollenflugSettings.partRegion)
    }

    function populatePartRegions(partRegionId) {
        var partRegionList = Constants.GERMAN_REGION_ID_TO_PART_REGIONS[partRegionId]
        partRegionGermanyComboBox.currentIndex = -1;
        if (partRegionList && partRegionList.length > 0) {
            partRegionsGermanyModel.clear()

            for (var j = 0; j < partRegionList.length; j++) {
                var item = {

                }
                item.label = partRegionList[j];
                partRegionsGermanyModel.append(item);
            }

            partRegionGermanyComboBox.currentIndex = -1;
            partRegionGermanyComboBox.currentItem = null;
            partRegionGermanyComboBox.visible = true;
        } else {
            partRegionsGermanyModel.clear();
            partRegionGermanyComboBox.visible = false;
        }
    }

    ComboBox {
        id: stateGermanyComboBox
        //: SettingsPage state
        label: qsTr("State")
        currentIndex: pollenflugSettings.region
        //: SettingsPage region description
        description: qsTr("Select the state where you live")
        menu: ContextMenu {
            MenuItem {
                text: qsTr("Schleswig-Holstein und Hamburg") // 10
            }
            MenuItem {
                text: qsTr("Mecklenburg-Vorpommern") // 20
            }
            MenuItem {
                text: qsTr("Niedersachsen und Bremen") // 30
            }
            MenuItem {
                text: qsTr("Nordrhein-Westfalen") // 40
            }
            MenuItem {
                text: qsTr("Brandenburg und Berlin") // 50
            }
            MenuItem {
                text: qsTr("Sachsen-Anhalt") // 60
            }
            MenuItem {
                text: qsTr("Thüringen") // 70
            }
            MenuItem {
                text: qsTr("Sachsen") // 80
            }
            MenuItem {
                text: qsTr("Hessen") // 90
            }
            MenuItem {
                text: qsTr("Rheinland-Pfalz und Saarland") // 100
            }
            MenuItem {
                text: qsTr("Baden-Württemberg") // 110
            }
            MenuItem {
                text: qsTr("Bayern") // 120
            }
        }
        onCurrentIndexChanged: {
            onClicked: populatePartRegions(Functions.calculateRegion(
                                               currentIndex), true)
        }
    }

    ListModel {
        id: partRegionsGermanyModel
        ListElement {
            label: ""
        }
    }

    ComboBox {
        id: partRegionGermanyComboBox
        //: SettingsPage part region
        label: qsTr("Region")
        currentIndex: pollenflugSettings.partRegion
        //: SettingsPage part region description
        description: qsTr("Select the region where you live")
        menu: ContextMenu {
            Repeater {
                id: partRegionRepeater
                model: partRegionsGermanyModel
                delegate: MenuItem {
                    text: label
                }
            }
        }
    }

    Component.onCompleted: {
        console.log("[DE] read config value : " + pollenflugSettings.region + "/"
                    + pollenflugSettings.partRegion);
        stateGermanyComboBox.currentIndex = pollenflugSettings.region;
        populatePartRegions((pollenflugSettings.region + 1) * 10, false);
        if (pollenflugSettings.partRegion >= 0) {
            partRegionGermanyComboBox.currentIndex = pollenflugSettings.partRegion;
        }
    }
}
