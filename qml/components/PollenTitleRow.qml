import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    id: columnRow
    width: parent.width
    spacing: Theme.paddingMedium

    property int iconSize: 70

    property alias headerLabel: iconLabelRowLabel.text
    property alias titleImage: iconLabelRowImage.source

    Row {
        id: iconLabelRow
        width: parent.width
        spacing: Theme.paddingLarge

        Column {
            width: parent.width * 7 / 20

            Image {
                id: iconLabelRowImage
                width: iconSize
                height: iconSize
                anchors.right: parent.right
            }
        }

        Label {
            id: iconLabelRowLabel
            width: parent.width * 13 / 20
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: Theme.fontSizeExtraLarge
            font.bold: true
        }
    }
}
