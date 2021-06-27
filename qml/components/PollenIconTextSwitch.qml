import QtQuick 2.2
import QtQuick.LocalStorage 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0

import "../js/constants.js" as Constants
import "../js/functions.js" as Functions

IconTextSwitch {
    id: pollenIconTextSwitch

    property int pollenId
    readonly property int iconSize: 64

    icon.width: iconSize
    icon.height: iconSize

    visible: Functions.getDataBackend().isPollenDataProvided(pollenId);

    function isPollenChecked() {
        var ps = pollenflugSettings;
        switch(pollenId) {
        case Constants.MUGWORT_ID : return ps.isMugwortSelected;
        case Constants.BIRCH_ID: return ps.isBirchSelected;
        case Constants.ALDER_ID: return ps.isAlderSelected;
        case Constants.ASH_TREE_ID: return ps.isAshTreeSelected;
        case Constants.GRASS_ID: return ps.isGrassPollenSelected;
        case Constants.HAZEL_ID: return ps.isHazelSelected;
        case Constants.AMBROSIA_ID: return ps.isAmbrosiaSelected;
        case Constants.RYE_ID: return ps.isRyeSelected;
        case Constants.NETTLE_ID: return ps.isNettleSelected;
        }
    }

    function checkPollen(checked) {
        var ps = pollenflugSettings;
        switch(pollenId) {
        case Constants.MUGWORT_ID : ps.isMugwortSelected = checked; break;
        case Constants.BIRCH_ID: ps.isBirchSelected = checked; break;
        case Constants.ALDER_ID: ps.isAlderSelected = checked; break;
        case Constants.ASH_TREE_ID: ps.isAshTreeSelected = checked; break;
        case Constants.GRASS_ID: ps.isGrassPollenSelected = checked; break;
        case Constants.HAZEL_ID: ps.isHazelSelected = checked; break;
        case Constants.AMBROSIA_ID: ps.isAmbrosiaSelected = checked; break;
        case Constants.RYE_ID: ps.isRyeSelected = checked; break;
        case Constants.NETTLE_ID: ps.isNettleSelected = checked; break;
        }
    }

    checked: isPollenChecked();
    onCheckedChanged: checkPollen(checked);

    Component.onCompleted: {
        pollenIconTextSwitch.text = Functions.getDataBackend().getPollenName(pollenId);
        pollenIconTextSwitch.icon.source = "../icons/" + Functions.getDataBackend().getPollenImageName(pollenId);
    }

}
