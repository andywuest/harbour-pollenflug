import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Notifications 1.0

import "../components"
import "../components/thirdparty"

import "../js/constants.js" as Constants
import "../js/functions.js" as Functions

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    property bool networkError: false
    property bool loaded : false
    property int iconSize: 92

    function connectSlots() {
        console.log("connect - slots");
        var dataBackend = Functions.getDataBackend();
        dataBackend.pollenDataAvailable.connect(pollenDataAvailable);
        dataBackend.requestError.connect(errorResultHandler);
    }

    function updatePollenData() {
        loaded = false;

        var region = Functions.calculateRegion(pollenflugSettings.region);
        var partRegion = Functions.calculatePartRegion(region, pollenflugSettings.partRegion);

        Functions.getDataBackend().fetchPollenData(Functions.getSelectedPollenList(pollenflugSettings), region, partRegion);
    }

    function pollenDataAvailable(result) {
        //console.log(result);
        lastestPollenData = JSON.parse(result);

        if (pollenModel) {
            pollenModel.clear();

            for (var i = 0; i < lastestPollenData.pollenData.length; i++) {
                pollenModel.append(lastestPollenData.pollenData[i]);
            }
        }

        networkError = false;
        loaded = true;
    }

    function errorResultHandler(result) {
        pollenUpdateProblemNotification.show(result)
        networkError = true;
        loaded = true;
    }

    function isPollenDatePresent() {
        return (lastestPollenData && lastestPollenData.pollenData && lastestPollenData.pollenData.length > 0);
    }

    AppNotification {
        id: pollenUpdateProblemNotification
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
                onClicked: updatePollenData();
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // TODO create component from it
        Column {
            id: noPollenDataConfiguredColumn

            x: Theme.horizontalPageMargin
            width: parent.width - 2 * x
            spacing: Theme.paddingSmall

            visible: (!isPollenDatePresent() && loaded && !networkError)

            Label {
                topPadding: Theme.paddingLarge
                horizontalAlignment: Text.AlignHCenter
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * x

                wrapMode: Text.Wrap
                textFormat: Text.RichText
                text: qsTr("No data available - please configure your state and region properly.")
            }
        }

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
                visible: isPollenDatePresent()
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
                            //tileImage: imageSource
                            headerLabel: label

                            Component.onCompleted: {
                                // TODO find better way to update values in component
                                var currentModelItem = pollenModel.get(index);
                                dataToday = currentModelItem.today;
                                dataTomorrow = currentModelItem.tomorrow;
                                dataDayAfterTomorrow = currentModelItem.dayAfterTomorrow;
                                tileImage = Constants.POLLEN_DATA_LIST[currentModelItem.id - 1].imageSource;
                                pollenNextUpdate = (lastestPollenData.nextUpdate ? lastestPollenData.nextUpdate : "");
                                pollenLastUpdate = (lastestPollenData.lastUpdate ? lastestPollenData.nextUpdate : "");

                                updateUI();
                            }
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
