
/*
 * harbour-pollenflug - Sailfish OS Version
 * Copyright © 2020 Andreas Wüst (andreas.wuest.freelancer@gmail.com)
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
import QtQuick 2.2
import QtQuick.LocalStorage 2.0
import Sailfish.Silica 1.0

import "../components/thirdparty"

Page {
    id: mapPage

    property string mapUrl
    property string pollenName

    property int imageWidth;
    property int imageHeight;

    property real imageSizeFactor : imageWidth / imageHeight;
    property real screenSizeFactor: mapPage.width / mapPage.height;
    property real sizingFactor    : imageSizeFactor >= screenSizeFactor ? mapPage.width / imageWidth : mapPage.height / imageHeight;

    PageHeader {
        id: pageHeader
        title: qsTr("Pollen map")
        description: pollenName
        leftMargin: Theme.itemSizeMedium
        visible: true
    }

    Image {
        id: mapImage
        width: parent.width
        anchors.margins: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
        source: mapUrl
        onStatusChanged: {
            if (mapImage.status === Image.Ready) {
                console.log("[MapPage] painted width: " + mapImage.paintedWidth);
                console.log("[MapPage] painted height: " + mapImage.paintedHeight);
                mapPage.imageWidth = mapImage.paintedWidth;
                mapPage.imageHeight = mapImage.paintedHeight;

                mapImage.width = mapPage.imageWidth * mapPage.sizingFactor
                mapImage.height = mapPage.imageHeight * mapPage.sizingFactor
            }
        }
    }

    ImageProgressIndicator {
        image: mapImage
        withPercentage: true
    }

    Component.onCompleted: {
        console.log("[MapPage] page width: " + mapPage.width);
        console.log("[MapPage] image width: " + mapImage.width);
        console.log("[MapPage] painted width: " + mapImage.paintedWidth);
        console.log("[MapPage] image url: " + mapUrl);
    }

}
