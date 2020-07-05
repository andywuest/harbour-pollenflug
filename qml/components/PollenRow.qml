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
    property var pollenData: ({})
    property string pollenDataDate: "" // TODO needs to be set to calculate the 3rd day.

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

    Component.onCompleted: {
        titleRowImage.titleImage = tileImage
        console.log("given pollenId : " + columnRow.pollenId)

        console.log("pollution : " + JSON.toString(pollenData))

        var pollution = Constants.getPollution(columnRow.pollenId, pollenData)
        if (pollution) {
            if (pollution.today) {
                console.log("pollution.today : " + pollution.today)
                //tileToday.pollutionLabel = Constants.POLLUTION_ID_TO_LABEL[pollution.today];
                pollenPollutionRow.pollutionLabelToday
                        = Constants.POLLUTION_ID_TO_LABEL[pollution.today]
                pollenPollutionScaleRow.pollutionScaleToday
                        = Constants.POLLUTION_ID_TO_INDEX[pollution.today]
                //tileToday.pollutionIndex = Constants.POLLUTION_ID_TO_INDEX[pollution.today];
            }
            if (pollution.tomorrow) {
                console.log("pollution.tomorrow : " + pollution.tomorrow)
                //tileTomorrow.pollutionLabel = Constants.POLLUTION_ID_TO_LABEL[pollution.tomorrow];
                pollenPollutionRow.pollutionLabelTomorrow
                        = Constants.POLLUTION_ID_TO_LABEL[pollution.tomorrow]
                pollenPollutionScaleRow.pollutionScaleTomorrow
                        = Constants.POLLUTION_ID_TO_INDEX[pollution.tomorrow]
                //tileTomorrow.pollutionIndex = Constants.POLLUTION_ID_TO_INDEX[pollution.tomorrow];
            }
            if (pollution.dayafter_to && pollution.dayafter_to !== "-1") {
                console.log("pollution.dayafter_to : " + pollution.dayafter_to)
                //tileDayAfterTomorrow.pollutionLabel = Constants.POLLUTION_ID_TO_LABEL[pollution.dayafter_to];
                pollenPollutionRow.pollutionLabelDayAfterTomorrow
                        = Constants.POLLUTION_ID_TO_LABEL[pollution.dayafter_to]
                pollenPollutionScaleRow.pollutionScaleDayAfterTomorrow
                        = Constants.POLLUTION_ID_TO_LABEL[pollution.dayafter_to]
                //tileDayAfterTomorrow.pollutionIndex = Constants.POLLUTION_ID_TO_INDEX[pollution.dayafter_to];
            }

            console.log("pollution : " + pollution)
            console.log("Pollution : " + pollution.today)
            console.log("Pollution : " + pollution.tomorrow)
            console.log("Pollution : " + pollution.dayafter_to)

            console.log("label: " + Constants.POLLUTION_ID_TO_LABEL[pollution.today])
            console.log("index: " + Constants.POLLUTION_ID_TO_INDEX[pollution.today])
        }
    }
}
