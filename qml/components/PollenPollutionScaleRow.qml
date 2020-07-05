import QtQuick 2.0
import Sailfish.Silica 1.0

Row {
    id: tilesRow
    width: parent.width

    property alias pollutionScaleToday: todayScale.pollution
    property alias pollutionScaleTomorrow: tomorrowScale.pollution
    property alias pollutionScaleDayAfterTomorrow: dayAfterTomorrowScale.pollution

    PollenScale {
        id: todayScale
        width: parent.width / 3
    }

    PollenScale {
        id: tomorrowScale
        width: parent.width / 3

    }

    PollenScale {
        id: dayAfterTomorrowScale
        width: parent.width / 3
    }
}
