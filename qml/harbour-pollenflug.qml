import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0
import "pages"

import "js/constants.js" as Constants

ApplicationWindow {

    property var lastestPollenData: ({})

    // Global Settings Storage
    ConfigurationGroup {
        id: pollenflugSettings
        path: "/apps/harbour-pollenflug/settings"

        property int country: Constants.COUNTRY_GERMANY;

        // germany
        property int region: 10 // TODO fix
        property int partRegion: 1 // TODO fix

        // france
        property string departement: ""

        property bool isMugwortSelected: false // Beifuß
        property bool isBirchSelected: false // Birke
        property bool isAlderSelected: false // Erle
        property bool isAshTreeSelected: false // Esche
        property bool isGrassPollenSelected: false // Gräser
        property bool isHazelSelected: false // Hasel
        property bool isAmbrosiaSelected: false // Ambrosia
        property bool isRyeSelected: false // Roggen
        property bool isNettleSelected: false // Brennnessel
    }

    initialPage: Component {
        OverviewPage {
        }
    }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
}
