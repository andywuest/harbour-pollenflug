import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/functions.js" as Functions

Row {
    id: tilesRow
    width: parent.width

    property int maxScaleElements: 3
    property int scaleElements: 1
    property alias pollutionScaleToday: todayScale.pollution
    property alias pollutionScaleTomorrow: tomorrowScale.pollution
    property alias pollutionScaleDayAfterTomorrow: dayAfterTomorrowScale.pollution

    PollenScale {
        id: todayScale
        width: parent.width / 3
        visible: scaleElements >= 1
    }

    PollenScale {
        id: tomorrowScale
        width: parent.width / 3
        visible: scaleElements >= 2
    }

    PollenScale {
        id: dayAfterTomorrowScale
        width: parent.width / 3
        visible: scaleElements >= 3
    }

    Component.onCompleted: {
        tilesRow.x = Functions.calculateScaleXOffset(parent.width, scaleElements);
    }

}
