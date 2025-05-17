import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import "../js/functions.js" as Functions
import "../js/constants.js" as Constants

Column {
    id: settingsColumn
    height: childrenRect.height

    function updateConfiguration() {
        if (stationNameMenu.children[stationNameSwitzerlandComboBox.currentIndex]) {
            pollenflugSettings.stationName = stationNameMenu.children[stationNameSwitzerlandComboBox.currentIndex].value;
            console.log("[CH] stationName : " + pollenflugSettings.stationName)
        }
    }

    ComboBox {
        id: stationNameSwitzerlandComboBox
        //: SettingsPage measuring station
        label: qsTr("Measuring Station")
        currentIndex: pollenflugSettings.stationName
        //: SettingsPage measuring station description
        description: qsTr("Select the nearest measuring station")
        menu: ContextMenu {
            id: stationNameMenu
            Repeater {
                width: parent.width
                model: stationNameModel
                delegate: MenuItem {
                    readonly property string value : model.value
                    text: model.label
                }
            }
        }

        Component.onCompleted: {
            console.log("[CH] read config value stationName : " + pollenflugSettings.stationName);
            Functions.updateComboBoxSelection(stationNameSwitzerlandComboBox, pollenflugSettings.stationName);
        }
    }

    ListModel {
        id: stationNameModel
        ListElement { value: "PBS"; label: qsTr("Basel") }
        ListElement { value: "PBE"; label: qsTr("Bern") }
        ListElement { value: "PBU"; label: qsTr("Buchs SG") }
        ListElement { value: "PCF"; label: qsTr("La Chaux-de-Fonds") }
        ListElement { value: "PDS"; label: qsTr("Davos") }
        ListElement { value: "PGE"; label: qsTr("Genf") }
        ListElement { value: "PLS"; label: qsTr("Lausanne") }
        ListElement { value: "PLO"; label: qsTr("Locarno") }
        ListElement { value: "PLU"; label: qsTr("Lugano") }
        ListElement { value: "PLZ"; label: qsTr("Luzern") }
        ListElement { value: "PMU"; label: qsTr("Münsterlingen") }
        ListElement { value: "PNE"; label: qsTr("Neuenburg") }
        ListElement { value: "PSN"; label: qsTr("Sion") }
        ListElement { value: "PZH"; label: qsTr("Zürich") }
    }

    Component.onCompleted: {
        console.log("[CH] read config value : " + pollenflugSettings.stationName);
        for (var si = 0; si < stationNameMenu.children.length; si++) {
            if (stationNameMenu.children[si].value === pollenflugSettings.stationName) {
                console.log("[CH] stationName index : " + si);
                stationNameSwitzerlandComboBox.currentIndex = si;
            }
        }
    }

}
