import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/functions.js" as Functions

Row {
    id: tilesRow
    width: parent.width

    property int scaleElements: 1
    property alias pollutionLabelToday: todayLabel.text
    property alias pollutionLabelTomorrow: tomorrowLabel.text
    property alias pollutionLabelDayAfterTomorrow: dayAfterTomorrowLabel.text

    PollenLabel {
        id: todayLabel
        font.pixelSize: Theme.fontSizeExtraSmall
        font.bold: false;
        visible: scaleElements >= 1
        wrapMode: Label.WordWrap
    }

    PollenLabel {
        id: tomorrowLabel
        font.pixelSize: Theme.fontSizeExtraSmall
        font.bold: false;
        visible: scaleElements >= 2
        wrapMode: Label.WordWrap
    }

    PollenLabel {
        id: dayAfterTomorrowLabel
        font.pixelSize: Theme.fontSizeExtraSmall
        font.bold: false;
        visible: scaleElements >= 3
        wrapMode: Label.WordWrap
    }

    Component.onCompleted: {
        tilesRow.x = Functions.calculateScaleXOffset(parent.width, scaleElements);
    }

}
