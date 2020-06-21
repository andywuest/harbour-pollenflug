import QtQuick 2.2
import QtQuick.LocalStorage 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import "../js/constants.js" as Constants

IconTextSwitch {
    id: pollenIconTextSwitch

    property int pollenId
    property int iconSize: 64

    icon.width: iconSize
    icon.height: iconSize

    Component.onCompleted: {
        pollenIconTextSwitch.text = Constants.POLLEN_DATA_MAP[pollenId].label
        pollenIconTextSwitch.icon.source = Constants.POLLEN_DATA_MAP[pollenId].imageSource
    }
}
