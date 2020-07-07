import QtQuick 2.0
import Sailfish.Silica 1.0

import "../js/constants.js" as Constants

Column {
    id: columnRow
    width: parent.width
    spacing: Theme.paddingMedium

    property alias headerLabel: headerLabel.text

    property bool isUpToDate: true
    property string tileImage: ""
    property int pollenId: -1
    property var dataToday
    property var dataTomorrow
    property var dataDayAfterTomorrow
    property string pollenLastUpdate: ""
    property string pollenNextUpdate: ""

    function checkIsUpToDate() {
        var now = new Date();
        if (pollenNextUpdate) {
            var pollenLastUpdateString = pollenNextUpdate.replace(" Uhr", "");
            var nextUpdate = Date.parse(pollenLastUpdateString);
            isUpToDate = (nextUpdate > now);
        }
    }

    function updateUI() {
        if (dataToday) {
            pollenPollutionRow.pollutionLabelToday = dataToday.pollutionLabel;
            pollenPollutionScaleRow.pollutionScaleToday = dataToday.pollutionIndex;
        }
        if (dataTomorrow) {
            pollenPollutionRow.pollutionLabelTomorrow = dataTomorrow.pollutionLabel;
            pollenPollutionScaleRow.pollutionScaleTomorrow = dataTomorrow.pollutionIndex;
        }
        if (dataDayAfterTomorrow) {
            pollenPollutionRow.pollutionLabelDayAfterTomorrow = dataDayAfterTomorrow.pollutionLabel;
            if (dataDayAfterTomorrow.pollutionIndex >= 0) {
                pollenPollutionScaleRow.pollutionScaleDayAfterTomorrow = dataDayAfterTomorrow.pollutionIndex;
             }
        }
        titleRowImage.titleImage = tileImage;
        checkIsUpToDate();
    }

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

    PollenDateRow {
        id: pollenDateRow
        width: parent.width
    }

    PollenPollutionRow {
        id: pollenPollutionRow
        width: parent.width
        pollutionLabelToday: "-"
        pollutionLabelTomorrow: "-"
        pollutionLabelDayAfterTomorrow: "-"
        visible: isUpToDate
    }

    PollenPollutionNotUpToDateRow {
        id: pollenPollutionNotUpToDateRow
        width: parent.width
        visible: !isUpToDate
    }

    PollenPollutionScaleRow {
        id: pollenPollutionScaleRow
        width: parent.width
        pollutionScaleToday: -1
        pollutionScaleTomorrow: -1
        pollutionScaleDayAfterTomorrow: -1
        visible: isUpToDate
    }

}
