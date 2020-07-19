
/*
 * harbour-watchlist - Sailfish OS Version
 * Copyright © 2017 Andreas Wüst (andreas.wuest.freelancer@gmail.com)
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
import QtQuick 2.2
import QtQuick.LocalStorage 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

// QTBUG-34418
import "."

import "../components"
import "../js/functions.js" as Functions
import "../js/constants.js" as Constants

Page {
    id: settingsPage
    property int iconSize: 64
    property var partRegionNames: []

    onStatusChanged: {
        if (status === PageStatus.Deactivating) {
            console.log("storing settings!")
            pollenflugSettings.region = regionComboBox.currentIndex;
            pollenflugSettings.partRegion = partRegionComboBox.currentIndex;
            console.log("region : " + pollenflugSettings.region)
            console.log("partRegion : " + pollenflugSettings.partRegion)
            pollenflugSettings.sync()
        }
    }

    function populatePartRegions(partRegionId) {
        var partRegionList = Constants.GERMAN_REGION_ID_TO_PART_REGIONS[partRegionId]
        partRegionComboBox.currentIndex = -1
        if (partRegionList && partRegionList.length > 0) {
            partRegionsModel.clear();

            for (var j = 0; j < partRegionList.length; j++) {
                var item = {};
                item.label = partRegionList[j];
                partRegionsModel.append(item);
            }

            partRegionComboBox.currentIndex = -1;
            partRegionComboBox.currentItem = null;
            partRegionComboBox.visible = true
        } else {
            partRegionsModel.clear();
            partRegionComboBox.visible = false
        }
    }

    SilicaFlickable {
        id: settingsFlickable
        anchors.fill: parent

        // Tell SilicaFlickable the height of its content.
        contentHeight: settingsColumn.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: settingsColumn
            width: settingsPage.width
            spacing: Theme.paddingLarge

            PageHeader {
                //: SettingsPage settings title
                title: qsTr("Settings")
            }

            SectionHeader {
                text: qsTr("Ort")
            }

            ComboBox {
                id: regionComboBox
                //: SettingsPage region
                label: qsTr("Bundesland")
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
                    onClicked: populatePartRegions(Functions.calculateRegion(currentIndex), true)
                }
            }

            ListModel {
                        id: partRegionsModel
                        ListElement {
                            label: ""
                        }
                    }

            ComboBox {
                id: partRegionComboBox
                //: SettingsPage part region
                label: qsTr("Gegend")
                currentIndex: pollenflugSettings.partRegion
                //: SettingsPage part region description
                description: qsTr("Select the region where you live")
                menu: ContextMenu {
                    Repeater {
                        id: partRegionRepeater
                        model: partRegionsModel
                        delegate : MenuItem {
                            text: label
                        }
                    }
                }
            }

            SectionHeader {
                text: qsTr("Allergen")
            }

            PollenIconTextSwitch {
                pollenId: Constants.MUGWORT_ID
                checked: pollenflugSettings.isMugwortSelected
                onCheckedChanged: {
                    pollenflugSettings.isMugwortSelected = checked
                }
            }

            PollenIconTextSwitch {
                pollenId: Constants.BIRCH_ID
                checked: pollenflugSettings.isBirchSelected
                onCheckedChanged: {
                    pollenflugSettings.isBirchSelected = checked
                }
            }

            PollenIconTextSwitch {
                pollenId: Constants.ALDER_ID
                checked: pollenflugSettings.isAlderSelected
                onCheckedChanged: {
                    pollenflugSettings.isAlderSelected = checked
                }
            }

            PollenIconTextSwitch {
                pollenId: Constants.ASH_TREE_ID
                checked: pollenflugSettings.isAshTreeSelected
                onCheckedChanged: {
                    pollenflugSettings.isAshTreeSelected = checked
                }
            }

            PollenIconTextSwitch {
                pollenId: Constants.GRASS_ID
                checked: pollenflugSettings.isGrassPollenSelected
                onCheckedChanged: {
                    pollenflugSettings.isGrassPollenSelected = checked
                }
            }

            PollenIconTextSwitch {
                pollenId: Constants.AMBROSIA_ID
                checked: pollenflugSettings.isAmbrosiaSelected
                onCheckedChanged: {
                    pollenflugSettings.isAmbrosiaSelected = checked
                }
            }

            PollenIconTextSwitch {
                pollenId: Constants.RYE_ID
                checked: pollenflugSettings.isRyeSelected
                onCheckedChanged: {
                    pollenflugSettings.isRyeSelected = checked
                }
            }
        }
    }

    Component.onCompleted: {
        console.log("read config value : " + pollenflugSettings.region + "/"
                    + pollenflugSettings.partRegion)
        regionComboBox.currentIndex = pollenflugSettings.region
        populatePartRegions((pollenflugSettings.region + 1) * 10, false)
        if (pollenflugSettings.partRegion >= 0) {
            partRegionComboBox.currentIndex = pollenflugSettings.partRegion
        }
    }
}
