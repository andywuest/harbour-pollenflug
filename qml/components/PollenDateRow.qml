import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/functions.js" as Functions

Row {
    id: tilesRow
    width: parent.width

    PollenLabel {
        id: todayLabel
        text: qsTr("Today")
    }

    PollenLabel {
        id: tomorrowLabel
        text: qsTr("Tomorrow")
    }

    PollenLabel {
        id: dayAfterTomorrowLabel
        text: {
            var date = Functions.addDays(new Date(), 2);
            return date.toLocaleDateString(Qt.locale(), "dd.MM.yyyy");
        }
    }

}
