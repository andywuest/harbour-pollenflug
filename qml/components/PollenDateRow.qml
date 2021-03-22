import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/functions.js" as Functions

Row {
    id: tilesRow
    width: parent.width

    property int scaleElements: 1

    PollenLabel {
        id: todayLabel
        text: qsTr("Today")
        visible: scaleElements >= 1
    }

    PollenLabel {
        id: tomorrowLabel
        text: qsTr("Tomorrow")
        visible: scaleElements >= 2
    }

    PollenLabel {
        id: dayAfterTomorrowLabel
        text: {
            var date = Functions.addDays(new Date(), 2);
            return date.toLocaleDateString(Qt.locale(), "dd.MM.yyyy");
        }
        visible: scaleElements >= 3
    }

    Component.onCompleted: {
        tilesRow.x = Functions.calculateScaleXOffset(parent.width, scaleElements);
    }

}
