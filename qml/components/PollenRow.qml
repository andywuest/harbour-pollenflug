import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    id: columnRow
    width: parent.width
    spacing: Theme.paddingMedium

    property alias headerLabel: headerLabel.text
    // property string headerLabel: ""
    property string tileImage: ""

    Row {
        id: headerRow
        width: parent.width
        visible: false
        Label {
            id: headerLabel
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: Theme.fontSizeLarge
            font.bold: true
        }
    }

    Row {
        id: iconLabelRow
        width: parent.width

        PollenTitleRow {
            id: titleRowImage
            titleImage: ""
            headerLabel: headerLabel.text
        }

    }

    Row {
        id: tilesRow
        width: parent.width

        PollenTile {
            id: tileToday
            width: parent.width / 3
            label: qsTr("Heute")
            tileImage: ""
        }

        PollenTile {
            id: tileTomorrow
            width: parent.width / 3
            label: qsTr("Morgen")
            tileImage: ""
        }

        PollenTile {
            id: tileDayAfterTomorrow
            width: parent.width / 3
            label: qsTr("01.07.2020")
            tileImage: ""
        }
    }

    Component.onCompleted: {
        tileToday.tileImage = tileImage
        tileTomorrow.tileImage = tileImage
        tileDayAfterTomorrow.tileImage = tileImage
        titleRowImage.titleImage = tileImage
    }
}
