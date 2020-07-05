import QtQuick 2.0
import Sailfish.Silica 1.0

import "../components"
import "../components/thirdparty"

import "../js/constants.js" as Constants
import "../js/functions.js" as Functions

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    property bool loaded : false
    property int iconSize: 92
    property var nodeData: ({})
    property var resultData: ""

    function connectSlots() {
        console.log("connect - slots");
        var dataBackend = Functions.getDataBackend();
        dataBackend.pollenDataAvailable.connect(pollenDataAvailable);
        dataBackend.requestError.connect(errorResultHandler);
    }

    function updatePollenData() {
        loaded = false;
        Functions.getDataBackend().fetchPollenData();
    }

    function pollenDataAvailable(result) {
//        console.log(result);

        lastestPollenData = JSON.parse(result);
        //page.resultData = JSON.parse(result);

        //Constants.jsonData = JSON.parse(result);

        if (pollenflugSettings) {
            console.log("set..reg " + pollenflugSettings)
            console.log("reg " + pollenflugSettings.region)
            if (pollenflugSettings.region) {
                var region = (pollenflugSettings.region + 1) * 10;
                var partRegion = region + (pollenflugSettings.partRegion + 1);

                var node = Constants.findPollenNode(region, partRegion, lastestPollenData.content);
                nodeData = node;

                pollenModel.clear();
                Functions.addPollenToModel(pollenModel, pollenflugSettings);
            }
        }

        loaded = true;
    }

    function errorResultHandler(result) {
        // TODO
//        stockUpdateProblemNotification.show(result)
        loaded = true;
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
            opacity: visible ? 1 : 0
            visible: true

            Behavior on opacity {
                NumberAnimation {
                }
            }

            PageHeader {
                id: pollenHeader
                //: OverviewPage header
                title: qsTr("Allergen")
            }

            SilicaListView {
                id: pollenListView
                width: parent.width
                height: page.height - pollenHeader.height

                // magic to prevent overscrolling with header
                clip: true

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
                            pollenNextUpdate: lastestPollenData.next_update
                            pollenLastUpdate: lastestPollenData.last_update
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

    LoadingIndicator {
        id: pollenLoadingIndicator
        visible: !loaded
        Behavior on opacity {
            NumberAnimation {
            }
        }
        opacity: loaded ? 0 : 1
        height: parent.height
        width: parent.width
    }

    onStatusChanged: {
        if (status === PageStatus.Active) {
            console.log("status changed -> active now")
            updatePollenData();
        }
    }

    Component.onCompleted: {
        Functions.addPollenToModel(pollenModel, pollenflugSettings)
        connectSlots();
        updatePollenData();
    }
}
