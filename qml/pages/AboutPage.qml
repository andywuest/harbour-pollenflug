/*
 * harbour-pollenflug - Sailfish OS Version
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
import QtQuick 2.2
import QtQuick.LocalStorage 2.0
import Sailfish.Silica 1.0

import "../components/thirdparty"

Page {
    id: aboutPage

    SilicaFlickable {
        id: aboutPageFlickable
        anchors.fill: parent
        contentHeight: aboutColumn.height

        Column {
            PageHeader {
                //: AboutPage title - header
                title: qsTr("About Pollenflug")
            }

            id: aboutColumn
            anchors {
                left: parent.left
                right: parent.right
            }
            height: childrenRect.height

            LabelText {
                anchors {
                    left: parent.left
                    margins: Theme.paddingLarge
                }
                //: AboutPage title - about text title
                label: qsTr("About Pollenflug")
                //: AboutPage text - about text
                // TODO fixme
                text: qsTr("If you have an allergy you can watch the pollen situtation in your area for various allergenes. Pollenflug is open source and licensed under the GPL v3.")
                separator: true
            }

            LabelText {
                anchors {
                    left: parent.left
                    margins: Theme.paddingLarge
                }
                //: AboutPage version label
                label: qsTr("Version")
                text: applicationVersion
                separator: true
            }

            BackgroundItem {
                id: clickableUrlAuthor
                contentHeight: labelAuthor.height
                height: contentHeight
                width: aboutPageFlickable.width
                anchors {
                    left: parent.left
                }

                LabelText {
                    id: labelAuthor
                    anchors {
                        left: parent.left
                        margins: Theme.paddingLarge
                    }
                    //: AboutPage author label
                    label: qsTr("Author")
                    text: "Andreas Wüst"
                    separator: true
                    color: clickableUrlAuthor.highlighted ? Theme.highlightColor : Theme.primaryColor
                }
            }

//            LabelText {
//                anchors {
//                    left: parent.left
//                    margins: Theme.paddingLarge
//                }
//                //: AboutPage translators label
//                label: qsTr("Translators")
//                text: qsTr("Viacheslav Dikonov (ru)") + "\n" +
//                      "Åke Engelbrektson (sv)\n" +
//                      "@KhanPuking (zh_CN)"
//                separator: true
//            }

            BackgroundItem {
                id: clickableUrlSourceCode
                contentHeight: labelUrl.height
                height: contentHeight
                width: aboutPageFlickable.width
                anchors {
                    left: parent.left
                }

                LabelText {
                    id: labelUrl
                    anchors {
                        left: parent.left
                        margins: Theme.paddingLarge
                    }
                    //: AboutPage about source label
                    label: qsTr("Source code")
                    text: "https://github.com/andywuest/harbour-pollenflug"
                    color: clickableUrlSourceCode.highlighted ? Theme.highlightColor : Theme.primaryColor
                }
                onClicked: Qt.openUrlExternally(labelUrl.text)
            }
        }
    }

    VerticalScrollDecorator {
        flickable: aboutPageFlickable
    }
}
