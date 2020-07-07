import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    id: scaleColumn
    width: parent.width

    property int pollution: -1
    property int boxes: 7 // TODO sollte vom client kommen
    property var colors: ["#006400", "#228b22", "#7cfc00", "#ffff00", "#ee9a00", "#cd0000", "#8b3a62"]

    Row {
        id: scaleRow
        width: parent.width - (2 * Theme.paddingMedium) - (6 * Theme.paddingSmall)
        x: Theme.paddingMedium
        spacing: Theme.paddingSmall

        Repeater {
            id: indicatorRepeater
            width: parent.width
            model: scaleColumn.boxes

            Rectangle {
                width: parent.width / scaleColumn.boxes
                height: parent.width / scaleColumn.boxes
                border.color: Theme.highlightColor
                color: (index < scaleColumn.pollution ? scaleColumn.colors[index] : "transparent")
                border.width: 1
            }
        }
    }

}

