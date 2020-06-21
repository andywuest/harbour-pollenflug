import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import "pages"


ApplicationWindow {

    // Global Settings Storage
    ConfigurationGroup {
        id: pollenflugSettings
        path: "/apps/harbour-pollenflug/settings"

        property int state: 1 // TODO fix
        property int region: 2 // TODO fix

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
