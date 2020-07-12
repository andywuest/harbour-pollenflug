import QtQuick 2.0
import Sailfish.Silica 1.0

Row {
    id: tilesRow
    width: parent.width
     y: Theme.paddingLarge
     height: todayLabel.height + Theme.paddingLarge

    property string outOfDateLabel: qsTr("Nicht aktuell")
    property int rotationDegree: 0

    PollenLabel {
        id: todayLabel
        font.pixelSize: Theme.fontSizeExtraSmall
        font.bold: false;
        wrapMode: Label.WordWrap
        text: outOfDateLabel
        rotation: rotationDegree
    }

    PollenLabel {
        id: tomorrowLabel
        font.pixelSize: Theme.fontSizeExtraSmall
        font.bold: false;
        wrapMode: Label.WordWrap
        text: outOfDateLabel
        rotation: rotationDegree
    }

    PollenLabel {
        id: dayAfterTomorrowLabel
        font.pixelSize: Theme.fontSizeExtraSmall
        font.bold: false;
        wrapMode: Label.WordWrap
        text: outOfDateLabel
        rotation: rotationDegree
    }

}
