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
    readonly property int iconSize: 92

    function connectSlots() {
        console.log("[OverviewPage] connect - slots");
        var dataBackend = Functions.getDataBackend();
        dataBackend.pollenDataAvailable.connect(pollenDataHandler);
        dataBackend.requestError.connect(errorResultHandler);
    }

    function disconnectSlots() {
        console.log("[OverviewPage] disconnect - slots");
        var dataBackend = Functions.getDataBackend();
        dataBackend.pollenDataAvailable.disconnect(pollenDataHandler);
        dataBackend.requestError.disconnect(errorResultHandler);
    }

    function updatePollenData() {
        loaded = false;
        disconnectSlots(); // reconnect the slots - in case the backend has changed
        connectSlots();

        var pageHeaderDescription;
        var region, partRegion;
        if (Constants.COUNTRY_GERMANY === pollenflugSettings.country) {
            region = Functions.calculateRegion(pollenflugSettings.region);
            partRegion = Functions.calculatePartRegion(region, pollenflugSettings.partRegion);
            pageHeaderDescription = Constants.COUNTRY_MAP[pollenflugSettings.country];
            pageHeaderDescription += " - " + Constants.GERMAN_REGION_ID_TO_PART_REGIONS[region][pollenflugSettings.partRegion];
        } else if (Constants.COUNTRY_FRANCE === pollenflugSettings.country) {
            region = pollenflugSettings.departement;
            pageHeaderDescription = Constants.COUNTRY_MAP[pollenflugSettings.country];
            // TODO determine departement
            // pageHeaderDescription += " " + Constants.GERMAN_REGION_ID_TO_PART_REGIONS[region][pollenflugSettings.partRegion];
        } else if (Constants.COUNTRY_SWITZERLAND === pollenflugSettings.country) {
            region = pollenflugSettings.stationName;
            pageHeaderDescription = pollenflugSettings.stationName; // TODO fixme
        }

        pollenHeader.description = pageHeaderDescription;

        Functions.getDataBackend().fetchPollenData(Functions.getSelectedPollenList(pollenflugSettings), region, partRegion);
    }

    function pollenDataHandler(result) {
        console.log(result);
        lastestPollenData = JSON.parse(result);

        if (pollenModel) {
            pollenModel.clear();

            for (var i = 0; i < lastestPollenData.pollenData.length; i++) {
                pollenModel.append(lastestPollenData.pollenData[i]);
            }

            pollenHeader.visible = true;
        }

        networkError = false;
        loaded = true;
    }

    function errorResultHandler(result) {
        pollenUpdateProblemNotification.show(result)
        pollenHeader.visible = false;
        networkError = true;
        loaded = true;
    }

    function isPollenDatePresent() {
        return (lastestPollenData && lastestPollenData.pollenData && lastestPollenData.pollenData.length > 0);
    }

    function reloadOverviewPollens() {
        console.log("[OverviewPage] reloading pollens");
        updatePollenData(); // reload the pollen data
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
                onClicked: {
                    var settingsPage = pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
                    settingsPage.reloadOverviewPollens.connect(reloadOverviewPollens)
                }
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
                visible: true
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
                            headerLabel: ""
                                // label ---- TODO kann headerLabel hier entfernt

                            Component.onCompleted: {
                                // TODO find better way to update values in component
                                var currentModelItem = pollenModel.get(index);
                                dataToday = currentModelItem.today;
                                dataTomorrow = currentModelItem.tomorrow;
                                dataDayAfterTomorrow = currentModelItem.dayAfterTomorrow;
                                tileImage = "../icons/" + Functions.getDataBackend().getPollenImageName(currentModelItem.id);
                                pollenRow.headerLabel = Functions.getDataBackend().getPollenName(currentModelItem.id)
                                        // Constants.POLLEN_DATA_LIST[currentModelItem.id - 1].imageSource;
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

                    onClicked: {
                        if (pollenModel.get(index).todayMapUrl) {
                            pageStack.push(Qt.resolvedUrl("MapPage.qml"), { mapUrl: pollenModel.get(index).todayMapUrl,
                                           pollenName: pollenModel.get(index).label });
                        } else {
                            console.log("No mapUrl found for index " + index);
                        }
                    }
                }
            }
        }

        VerticalScrollDecorator {
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

    Component.onCompleted: {
        Functions.addPollenToModel(pollenModel, pollenflugSettings)
        updatePollenData();
    }
}
