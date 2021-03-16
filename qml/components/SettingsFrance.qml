import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

Column {
    id: settingsColumn
    width: parent.width
    height: childrenRect.height

    ComboBox {
        id: departementFranceComboBox
        //: SettingsPage state
        label: qsTr("Departement")
        currentIndex: pollenflugSettings.region
        //: SettingsPage region description
        description: qsTr("Select the departement where you live")
        menu: ContextMenu {
            MenuItem {
                text: qsTr("Ain") // 10
            }
            MenuItem {
                text: qsTr("Aisne") // 20
            }
            MenuItem {
                text: qsTr("Allier") // 30
            }
            MenuItem {
                text: qsTr("Alpes-de-Haute-Provence") // 40
            }
            MenuItem {
                text: qsTr("Hautes-Alpes") // 50
            }
            MenuItem {
                text: qsTr("Alpes-Maritimes") // 60
            }
            MenuItem {
                text: qsTr("Ardèche") // 70
            }
            MenuItem {
                text: qsTr("Ardennes") // 80
            }
        }
        onCurrentIndexChanged: {
            onClicked: console.log("selected index : " + currentIndex);
        }
    }

}

