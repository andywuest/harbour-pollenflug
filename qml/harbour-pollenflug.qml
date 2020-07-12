import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0
import "pages"

ApplicationWindow {

    property var lastestPollenData: ({})

    // Global Settings Storage
    ConfigurationGroup {
        id: pollenflugSettings
        path: "/apps/harbour-pollenflug/settings"

        property int region: 10 // TODO fix
        property int partRegion: 1 // TODO fix

        property bool isMugwortSelected: false // Beifuß
        property bool isBirchSelected: false // Birke
        property bool isAlderSelected: false // Erle
        property bool isAshTreeSelected: false // Esche
        property bool isGrassPollenSelected: false // Gräser
        property bool isHazelSelected: false // Hasel
        property bool isAmbrosiaSelected: false // Ambrosia
        property bool isRyeSelected: false // Roggen
    }

    initialPage: Component {
        OverviewPage {
        }
    }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
}
