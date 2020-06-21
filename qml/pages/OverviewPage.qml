import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components"

import "../js/constants.js" as Constants
import "../js/functions.js" as Functions

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    property int iconSize: 92

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        width: parent.width
        height: parent.height
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                //: OverviewPage about menu item
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
            MenuItem {
                //: OverviewPage about menu item
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
            }
        }


        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            //height: 800
            spacing: Theme.paddingLarge
            // y: Theme.paddingLarge

//            PageHeader {
//                title: qsTr("UI Template")
//            }

            SilicaListView {
                id: pollenListView
                width: parent.width
                height: page.height

                model: ListModel {
                    id: pollenModel
                }

                delegate: ListItem {
                    contentHeight: pollenColumn.height + (2 * Theme.paddingMedium)
                    contentWidth: parent.width

                    Column {
                        id: pollenColumn
                        width: parent.width
                        y: Theme.paddingLarge
                        spacing: Theme.paddingMedium

                        PollenRow {
                            id: pollenRow
                            width: parent.width
                            tileImage: imageSource
                            headerLabel: label
                        }

                        Separator {
                            id: pollenRowSeparator
                            width: parent.width
                            color: Theme.primaryColor
                            horizontalAlignment: Qt.AlignHCenter
                        }
                    }
                }



//                delegate: ListItem {
//                    width: parent.width

//                    PollenRow {

//                    tileImage: imageSource
//                    headerLabel: label
//                }
            }




//            Label {
//                x: Theme.horizontalPageMargin
//                text: qsTr("Hello Sailors")
//                color: Theme.secondaryHighlightColor
//                font.pixelSize: Theme.fontSizeExtraLarge
//            }


//            Column {
//                width: parent.width
//                height: 800
//                Label {
//                    text: qsTr("Gräser")
//                }

//            PollenRow {
//                width: parent.width
//                tileImage: "../icons/erle.svg"
//                headerLabel: qsTr("Erle")
//            }

//            Separator {
//                width: parent.width
//                color: Theme.primaryColor
//                horizontalAlignment: Qt.AlignHCenter
//            }

//            PollenRow {
//                width: parent.width
//                tileImage: "../icons/ambrosia.svg"
//                headerLabel: qsTr("Ambrosia")
//            }

//            Separator {
//                width: parent.width
//                color: Theme.primaryColor
//                horizontalAlignment: Qt.AlignHCenter
//            }

//            PollenRow {
//                width: parent.width
//                tileImage: "../icons/graeser.svg"
//                headerLabel: qsTr("Gräser")
//            }

//            Separator {
//                width: parent.width
//                color: Theme.primaryColor
//                horizontalAlignment: Qt.AlignHCenter
//            }


//            PollenRow {
//                width: parent.width
//                tileImage: "../icons/birke.svg"
//                headerLabel: qsTr("Birke")
//            }

//            Separator {
//                width: parent.width
//                color: Theme.primaryColor
//                horizontalAlignment: Qt.AlignHCenter
//            }




//                Row {
//                    width: parent.width
//                    Label {
//                        width: parent.width
//                        horizontalAlignment: Text.AlignHCenter
//                        font.pixelSize: Theme.fontSizeLarge
//                        font.bold: true
//                        text: qsTr("Gräser")
//                    }
//                }

//                Row {
//                    width: parent.width
//                    height: parent.height

//                    PollenTile {
//                        width: parent.width / 3
//                        label: qsTr("Heute")
//                        tileImage: "../icons/erle.svg"
//                    }

//                    PollenTile {
//                        width: parent.width / 3
//                        label: qsTr("Morgen")
//                        tileImage: "../icons/erle.svg"
//                    }

//                    PollenTile {
//                        width: parent.width / 3
//                        label: qsTr("01.07.2020")
//                        tileImage: "../icons/erle.svg"
//                    }
//                }



            }







 //       }
    }

    Component.onCompleted: {
        Functions.addPollenToModel(pollenModel, pollenflugSettings)
        console.log(pollenModel.count)
    }

}
