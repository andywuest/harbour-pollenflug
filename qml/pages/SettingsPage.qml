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

// TODO import

// QTBUG-34418
import "."

import "../components"

// import "../js/database.js" as Database
import "../js/constants.js" as Constants

Page {
    id: settingsPage
    property int iconSize: 64
    property bool isAshTreeSelected: false
    property bool isAlderSelected: false
    property bool isGrassPollenSelected: false

    onStatusChanged: {
        if (status === PageStatus.Deactivating) {
            console.log("store settings!");
//            if (settingsPage.currentDataBackend !== pollenflugSettings.dataBackend) {
//                console.log("reset application database");
//                Database.resetApplication()
//                Database.initApplicationTables()
//            }
            console.log("isAshTreeSelected : " + pollenflugSettings.isAshTreeSelected);
            console.log("isAlderSelected : " + pollenflugSettings.isAlderSelected);
            pollenflugSettings.sync();
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
                //: SettingsPage download news data
                label: qsTr("Region")
                currentIndex: watchlistSettings.newsDataDownloadStrategy
                //: SettingsPage download strategy explanation
                description: qsTr("Defines strategy to download the news data")
                menu: ContextMenu {
                    MenuItem {
                        //: SettingsPage news download strategy always
                        text: qsTr("Schleswig-Holstein und Hamburg")
                    }
                    MenuItem {
                        //: SettingsPage news download strategy only on wifi
                        text: qsTr("Mecklenburg-Vorpommern")
                    }
                    MenuItem {
                        //: SettingsPage news download strategy only on wifi
                        text: qsTr("Niedersachsen und Bremen")
                    }

                    // so far - there is no manually - maybe a button in the future
                    onActivated: {
                        watchlistSettings.newsDataDownloadStrategy = index
                    }
                }
            }

            ComboBox {
                id: partRegionComboBox
                //: SettingsPage download news data
                label: qsTr("Region")
                currentIndex: watchlistSettings.newsDataDownloadStrategy
                //: SettingsPage download strategy explanation
                description: qsTr("Defines strategy to download the news data")
                menu: ContextMenu {
                    MenuItem {
                        //: SettingsPage news download strategy always
                        text: qsTr("Westl. Niedersachsen/Bremen")
                    }
                    MenuItem {
                        //: SettingsPage news download strategy only on wifi
                        text: qsTr("Östl. Niedersachsen")
                    }

                    // so far - there is no manually - maybe a button in the future
                    onActivated: {
                        watchlistSettings.newsDataDownloadStrategy = index
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



/*

            IconTextSwitch {
                text: Constants.POLLEN_DATA_MAP[Constants.ASH_TREE_ID].label
                icon.source: Constants.POLLEN_DATA_MAP[Constants.ASH_TREE_ID].imageSource
                checked: pollenflugSettings.isAshTreeSelected
                icon.width: iconSize
                icon.height: iconSize
                onCheckedChanged: {
                    pollenflugSettings.isAshTreeSelected = checked
                }
            }

            IconTextSwitch {
                text: qsTr("Erle")
                icon.source: "../icons/erle.svg"
                description: "Description for Erle"
                checked: pollenflugSettings.isAlderSelected
                icon.width: iconSize
                icon.height: iconSize
                onCheckedChanged: {
                    pollenflugSettings.isAlderSelected = checked
                }
            }

            IconTextSwitch {
                text: qsTr("Gräser")
                icon.source: "../icons/erle.svg"
                description: "Description for Gräser"
                checked: pollenflugSettings.isGrassPollenSelected
                icon.width: iconSize
                icon.height: iconSize
                onCheckedChanged: {
                    pollenflugSettings.isGrassPollenSelected = checked
                }
            }
            */

            ComboBox {
                id: chartDataDownloadComboBox
                //: SettingsPage download chart data
                label: qsTr("Download chart data")
                currentIndex: watchlistSettings.chartDataDownloadStrategy
                //: SettingsPage download strategy explanation
                description: qsTr("Defines strategy to download the chart data")
                menu: ContextMenu {
                    MenuItem {
                        //: SettingsPage download strategy always
                        text: qsTr("Always")
                    }
                    MenuItem {
                        //: SettingsPage download strategy only on wifi
                        text: qsTr("Only on WiFi")
                    }
                    MenuItem {
                        //: SettingsPage download strategy only manually
                        text: qsTr("Only manually")
                    }
                    onActivated: {
                        watchlistSettings.chartDataDownloadStrategy = index
                    }
                }
            }

            ComboBox {
                id: sortingOrderComboBox
                //: SettingsPage sorting order watchlist page
                label: qsTr("Sorting order")
                currentIndex: watchlistSettings.sortingOrder
                //: SettingsPage sorting order description
                description: qsTr("Defines sorting order of watchlist entries")
                menu: ContextMenu {
                    MenuItem {
                        //: SettingsPage sorting order by change
                        text: qsTr("By change")
                    }
                    MenuItem {
                        //: SettingsPage sorting order by name
                        text: qsTr("By name")
                    }
                    onActivated: {
                        watchlistSettings.sortingOrder = index
                    }
                }
            }

            ComboBox {
                id: dataBackendComboBox
                //: SettingsPage data backend for watchlist
                label: qsTr("Data Backend")
                currentIndex: watchlistSettings.dataBackend
                //: SettingsPage data backend for watchlist description
                description: qsTr("Data backend to be used for the watchlist")
                menu: ContextMenu {
                    MenuItem {
                        //: SettingsPage data backend Euroinvestor (default)
                        text: qsTr("Euroinvestor")
                    }
                    MenuItem {
                        //: SettingsPage data backend Moscow Exchange
                        text: qsTr("Moscow Exchange")
                    }
                    onActivated: {
                        watchlistSettings.dataBackend = index
                    }
                }
            }

            Label {
                id: dataBackendLabel
                text: qsTr("NOTE: Changing the data backend will reset the database. This means that the current watchlist will be reset and the stocks have to be added again!")
                font.pixelSize: Theme.fontSizeSmall
                padding: Theme.paddingLarge
                width: parent.width - 2 * Theme.paddingLarge
                wrapMode: Text.Wrap
            }

            ComboBox {
                id: newsDataDownloadComboBox
                //: SettingsPage download news data
                label: qsTr("Download news data")
                currentIndex: watchlistSettings.newsDataDownloadStrategy
                //: SettingsPage download strategy explanation
                description: qsTr("Defines strategy to download the news data")
                menu: ContextMenu {
                    MenuItem {
                        //: SettingsPage news download strategy always
                        text: qsTr("Always")
                    }
                    MenuItem {
                        //: SettingsPage news download strategy only on wifi
                        text: qsTr("Only on WiFi")
                    }
                    // so far - there is no manually - maybe a button in the future
                    onActivated: {
                        watchlistSettings.newsDataDownloadStrategy = index
                    }
                }
            }

        }

        Component.onCompleted: {
            settingsPage.isAlderSelected = pollenflugSettings.isAlderSelected;
            settingsPage.isAshTreeSelected = pollenflugSettings.isAshTreeSelected;
            settingsPage.isGrassPollenSelected = pollenflugSettings.isGrassPollenSelected;
        }
    }
}
