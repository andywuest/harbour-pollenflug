/*
 * harbour-watchlist - Sailfish OS Version
 * Copyright © 2017 Andreas Wüst (andreas.wuest.freelancer@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
import QtQuick 2.6
import QtQuick.LocalStorage 2.0
import Sailfish.Silica 1.0

import "../components"

import "../js/constants.js" as Constants
import "../js/functions.js" as Functions

CoverBackground {
    id: coverPage
    property bool loading : false

    function connectSlots() {
        console.log("connect - slots");
        var dataBackend = Functions.getDataBackend();
        dataBackend.pollenDataAvailable.connect(pollenDataAvailable);
        dataBackend.requestError.connect(errorResultHandler);
    }

    function updatePollenData() {
        loading = true;

        var region = Functions.calculateRegion(pollenflugSettings.region);
        var partRegion = Functions.calculatePartRegion(region, pollenflugSettings.partRegion);

        Functions.getDataBackend().fetchPollenData(Functions.getSelectedPollenList(pollenflugSettings), region, partRegion);
    }

    function pollenDataAvailable(result) {
        console.log(result);
        lastestPollenData = JSON.parse(result);

        if (coverModel) {
            coverModel.clear();
            for (var i = 0; i < lastestPollenData.pollenData.length; i++) {
                coverModel.append(lastestPollenData.pollenData[i]);
            }
        }

        loading = false;
    }

    function errorResultHandler(result) {
        loading = false;
    }

    Column {
        id: loadingColumn
        width: parent.width - 2 * Theme.horizontalPageMargin
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: Theme.paddingMedium
        visible: coverPage.loading
        Behavior on opacity {
            NumberAnimation {
            }
        }
        opacity: coverPage.loading ? 1 : 0
        InfoLabel {
            id: loadingLabel
            text: qsTr("Loading...")
            font.pixelSize: Theme.fontSizeMedium
        }
    }

    CoverActionList {
        id: coverActionPrevious
        enabled: true

        CoverAction {
            id: actionPreviousPrevious
            iconSource: "image://theme/icon-cover-previous"
            onTriggered: {
                coverActionPrevious.enabled = false
                coverActionNext.enabled = true
            }
        }

        CoverAction {
            iconSource: "image://theme/icon-cover-refresh"
            onTriggered: updatePollenData()
        }
    }

    CoverActionList {
        id: coverActionNext
        enabled: false

        CoverAction {
            id: actionNext
            iconSource: "image://theme/icon-cover-next"
            onTriggered: {
                console.log("previous clicked")
                coverActionNext.enabled = false
                coverActionPrevious.enabled = true
            }
        }

        CoverAction {
            iconSource: "image://theme/icon-cover-refresh"
            onTriggered: updatePollenData()
        }
    }

    SilicaListView {
        id: coverListView

        visible: !coverPage.loading
        Behavior on opacity { NumberAnimation {} }
        opacity: coverPage.loading ? 0 : 1

        anchors.fill: parent

        model: ListModel {
            id: coverModel
        }

        header: Text {
            id: labelTitle
            width: parent.width
            topPadding: Theme.paddingLarge
            bottomPadding: Theme.paddingMedium
            text: coverActionPrevious.enabled ? qsTr("Today") : qsTr("Tomorrow")
            color: Theme.primaryColor
            font.bold: true
            font.pixelSize: Theme.fontSizeSmall
            textFormat: Text.StyledText
            horizontalAlignment: Text.AlignHCenter
        }

        delegate: ListItem {

            // height: resultLabelTitle.height + resultLabelContent.height + Theme.paddingSmall
            contentHeight: stockQuoteColumn.height + Theme.paddingSmall

            // TODO custom - hier noch pruefen, was an margins noch machbar, sinnvoll ist
            Column {
                id: stockQuoteColumn
                x: Theme.paddingLarge
                width: parent.width - 2 * Theme.paddingLarge
                anchors.verticalCenter: parent.verticalCenter

                Row {
                    id: firstRow
                    width: parent.width
                    height: Theme.fontSizeExtraSmall + Theme.paddingSmall

                    Label {
                        id: stockQuoteName
                        width: parent.width
                        height: parent.height
                        text: label
                        color: Theme.primaryColor
                        font.pixelSize: Theme.fontSizeExtraSmall
                        font.bold: true
                        horizontalAlignment: Text.AlignLeft
                        truncationMode: TruncationMode.Fade
                    }
                }

                Row {
                    id: thirdRow
                    width: parent.width
                    height: Theme.fontSizeTiny + Theme.paddingSmall

                    Label {
                        id: pollutionLabel
                        width: parent.width
                        height: parent.height
                        color: Theme.primaryColor
                        font.pixelSize: Theme.fontSizeExtraSmallBase
                        font.bold: false
                        horizontalAlignment: Text.AlignLeft
                        truncationMode: TruncationMode.Fade

                        Component.onCompleted: {
                            pollutionLabel.text = (coverActionPrevious.enabled ? coverModel.get(index).today.pollutionLabel : coverModel.get(index).tomorrow.pollutionLabel);
                        }
                    }
                }
            }
        }
    }

    OpacityRampEffect {
        sourceItem: coverListView
        direction: OpacityRamp.TopToBottom
        offset: 0.6
        slope: 3.75
    }

    Component.onCompleted: {
        connectSlots();
        updatePollenData()
    }

}
