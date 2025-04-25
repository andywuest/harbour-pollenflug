/*
 * harbour-pollenflug - Sailfish OS Version
 * Copyright © 2025 Andreas Wüst (andreas.wuest.freelancer@gmail.com)
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
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        id: aboutPageFlickable
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width:parent.width
            spacing: Theme.paddingLarge

            PageHeader {
                //: AboutPage - Header
                title: qsTr("About")
            }

            Image {
                id: logo
                source: "/usr/share/icons/hicolor/172x172/apps/harbour-pollenflug.png"
                smooth: true
                height: width
                width: parent.width / 2
                sourceSize.width: 512
                sourceSize.height: 512
                anchors.horizontalCenter: parent.horizontalCenter
                opacity: 0.7
            }

            Label {
                width: parent.width
                x : Theme.horizontalPageMargin
                font.pixelSize: Theme.fontSizeExtraLarge
                color: Theme.secondaryHighlightColor

                //: AboutPage - Name
                text: qsTr("Pollenflug")
            }

            Label {
                width: parent.width
                x : Theme.horizontalPageMargin
                text: applicationVersion
            }

            Item {
                height: Theme.paddingMedium
                width: 1
            }

            AboutDescription {
                //: AboutPage text - about text
                description: qsTr("If you suffer from an allergy you can watch the pollen situation in your area for various allergenes. Pollenflug is open source and licensed under the GPL v3.")
            }

            SectionHeader {
                //: AboutPage - Translations
                text: qsTr("Translations")
            }

            AboutDescription {
                //: AboutPage - translations
                description: "monkeyisland1992 (de)\n" +
                             "Quentin Pagès (fr)"
            }

            SectionHeader{
                id: sectionHeaderSources
                //: AboutPage - sources
                text: qsTr("Sources")
            }

            AboutIconLabel {
                iconSource: "icons/github.svg"
                label: "https://github.com/andywuest/harbour-pollenflug"
                targetUrl: "https://github.com/andywuest/harbour-pollenflug"
            }

            SectionHeader {
                //: AboutPage - Donations
                text: qsTr("Donations")
            }

            AboutDescription {
                //: AboutPage - donations info
                description: qsTr("If you like my work why not buy me a beer?")
            }

            SectionHeader {
                //: AboutPage - Icons
                text: qsTr("Icons")
            }

            AboutDescription {
                //: AboutPage - icons info
                description: qsTr("Icons made by Freepik from Free vector icons - SVG, PSD, PNG, EPS & Icon Font - Thousands of free icons")
            }

            AboutIconLabel {
                iconSource: "icons/flaticon.svg"
                label: qsTr("Flaticon")
                targetUrl: "http://www.flaticon.com"
            }

            Item {
                width: 1
                height: Theme.paddingSmall
            }
        }
    }

    VerticalScrollDecorator {
        flickable: aboutPageFlickable
    }
}
