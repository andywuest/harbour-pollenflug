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
    property var nodeData: ({})

    function connectSlots() {
        console.log("connect - slots");
        var dataBackend = Functions.getDataBackend();
        dataBackend.pollenDataAvailable.connect(pollenDataAvailable);
        dataBackend.requestError.connect(errorResultHandler);
    }

    function disconnectSlots() {
        console.log("disconnect - slots");
        var dataBackend = Functions.getDataBackend();
        dataBackend.pollenDataAvailable.disconnect(pollenDataAvailable);
        dataBackend.requestError.disconnect(errorResultHandler);
    }

    function pollenDataAvailable(result) {
        console.log(result);
        var jsonResult = JSON.parse(result);

        if (pollenflugSettings.region) {
            var region = (pollenflugSettings.region + 1) * 10;
            var partRegion = region + (pollenflugSettings.partRegion + 1);

            var node = Constants.findPollenNode(region, partRegion, jsonResult.content);
            nodeData = node;

            pollenModel.clear();
            Functions.addPollenToModel(pollenModel, pollenflugSettings);
        }


//        var pullution = Constants.getPollution(Constants.GRASS_ID, node);
//        console.log("Pollution : " + pullution.today)
//        console.log("Pollution : " + pullution.tomorrow)
//        console.log("Pollution : " + pullution.dayafter_to)

    }

    function errorResultHandler(result) {
//        stockUpdateProblemNotification.show(result)
//        loaded = true;
    }

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
                //: OverviewPage settings menu item
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
            }
            MenuItem {
                //: OverviewPage refrehs menu item
                text: qsTr("Refresh")
                onClicked: germanPollenBackend.fetchPollenData();
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge

//            PageHeader {
//                id: stockQuotesHeader
//                //: OverviewPage header
//                title: qsTr("Allergene")
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
                            pollenId: id
                            pollenData: nodeData
                        }

                        Separator {
                            id: pollenRowSeparator
                            width: parent.width
                            color: Theme.primaryColor
                            horizontalAlignment: Qt.AlignHCenter
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        Functions.addPollenToModel(pollenModel, pollenflugSettings)
        // console.log(pollenModel.count)
        connectSlots();
        // germanPollenBackend.fetchPollenData();
    }
}
