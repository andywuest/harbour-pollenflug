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
    signal reloadOverviewPollens()

    function switchToCountrySettings(countryValue) {
        pollenflugSettings.country = countryValue;
        var country = Constants.COUNTRY_MAP[countryValue];
        console.log("_" + countryValue + ", " + country);
        countrySpecificLoader.source = "../components/Settings" + country + ".qml";
    }

    onStatusChanged: {
        if (status === PageStatus.Deactivating) {
            console.log("storing settings!")
            countrySpecificLoader.item.updateConfiguration();
            // pollenflugSettings.country = countryComboBox.currentIndex;
            console.log("country : " + pollenflugSettings.country)
            pollenflugSettings.sync()
            reloadOverviewPollens()
        }
    }

    SilicaFlickable {
        id: settingsFlickable
        anchors.fill: parent

        // Tell SilicaFlickable the height of its content.
        width: parent.width
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
                text: qsTr("Location")
            }

            ComboBox {
                id: countryComboBox
                //: SettingsPage state
                label: qsTr("Country")
                currentIndex: pollenflugSettings.region
                //: SettingsPage region description
                description: qsTr("Select the country where you live")
                menu: ContextMenu {
                    id: countryMenu
                    MenuItem {
                        readonly property int value: Constants.COUNTRY_GERMANY
                        text: qsTr("Germany");
                    }
                    MenuItem {
                        readonly property int value: Constants.COUNTRY_FRANCE
                        text: qsTr("France")
                    }
                }

                onCurrentIndexChanged: {
                    onClicked: countryMenu.children[currentIndex] && switchToCountrySettings(countryMenu.children[currentIndex].value);
                }              

                Component.onCompleted: {
                    console.log("read config value country : " + pollenflugSettings.country);
                    switchToCountrySettings(pollenflugSettings.country)
                    Functions.updateComboBoxSelection(countryComboBox, pollenflugSettings.country);
                }
            }

            Loader {
                id: countrySpecificLoader
                width: parent.width
                opacity: status === Loader.Ready ? 1.0 : 0.0
                Behavior on opacity { FadeAnimator {} }
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

        VerticalScrollDecorator {
        }

    }

}
