import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    id: pollenTile

    property int iconSize: 70
    property int pollutionIndex: -1

    property alias dateLabel: dateLabel.text
    property alias pollutionLabel: pollutionLabel.text
    //property alias tileImage: pollenImage.source
    property var colors: ["#006400", "#228b22", "#7cfc00", "#ffff00", "#ee9a00", "#cd0000", "#8b3a62"]
    property var borderColors: ["", "", "", "", "", "", ""]
    // https://cssgenerator.org/rgba-and-hex-color-generator.html

    width: parent.width
    spacing: Theme.paddingLarge

    Label {
        id: dateLabel
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Theme.fontSizeSmall
        text: pollenTile.label
        font.bold: true
        visible: true
    }

    Label {
        id: pollutionLabel
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Theme.fontSizeExtraSmall
        wrapMode: Label.WordWrap
    }

//    Image {
//        id: pollenImage
//        visible: false // TODO
//        width: iconSize
//        height: iconSize
//        anchors.horizontalCenter: parent.horizontalCenter
//    }

    Row {
        id: indicatorRow
        width: parent.width - (2 * Theme.paddingMedium) - (6 * Theme.paddingSmall)
        x: Theme.paddingMedium
        spacing: Theme.paddingSmall

        Repeater {
            id: indicatorRepeater
            model: 7
            Rectangle {
                width: parent.width / 7
                height: parent.width / 7
                border.color: Theme.highlightColor
                color: (index <= pollutionIndex ? colors[index] : "transparent")
                border.width: 1
            }
        }
    }
}
