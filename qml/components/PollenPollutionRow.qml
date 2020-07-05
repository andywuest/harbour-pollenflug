import QtQuick 2.0
import Sailfish.Silica 1.0

Row {
    id: tilesRow
    width: parent.width

    property alias pollutionLabelToday: todayLabel.text
    property alias pollutionLabelTomorrow: tomorrowLabel.text
    property alias pollutionLabelDayAfterTomorrow: dayAfterTomorrowLabel.text

    PollenLabel {
        id: todayLabel
        font.pixelSize: Theme.fontSizeExtraSmall
        font.bold: false;
        wrapMode: Label.WordWrap
    }

    PollenLabel {
        id: tomorrowLabel
        font.pixelSize: Theme.fontSizeExtraSmall
        font.bold: false;
        wrapMode: Label.WordWrap
    }

    PollenLabel {
        id: dayAfterTomorrowLabel
        font.pixelSize: Theme.fontSizeExtraSmall
        font.bold: false;
        wrapMode: Label.WordWrap
    }

}
