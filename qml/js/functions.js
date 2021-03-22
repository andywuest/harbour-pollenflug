
Qt.include('constants.js');

function calculateScaleXOffset(parentWidth, scaleElements) {
    var offset = (parentWidth - (parentWidth * scaleElements / MAX_SCALE_ELEMENTS)) / 2;
    console.log("Parent width: " + parentWidth + ", offset : " + offset);
    return offset;
}

function addPollenToModel(model, settings) {
    for (var i = 0; i < POLLEN_DATA_LIST.length; i++) {
        addIfActive(POLLEN_DATA_LIST, i, MUGWORT_ID, settings.isMugwortSelected, model)
        addIfActive(POLLEN_DATA_LIST, i, BIRCH_ID, settings.isBirchSelected, model)
        addIfActive(POLLEN_DATA_LIST, i, ALDER_ID, settings.isAlderSelected, model)
        addIfActive(POLLEN_DATA_LIST, i, ASH_TREE_ID, settings.isAshTreeSelected, model)
        addIfActive(POLLEN_DATA_LIST, i, GRASS_ID, settings.isGrassPollenSelected, model)
        addIfActive(POLLEN_DATA_LIST, i, HAZEL_ID, settings.isHazelSelected, model)
        addIfActive(POLLEN_DATA_LIST, i, AMBROSIA_ID, settings.isAmbrosiaSelected, model)
        addIfActive(POLLEN_DATA_LIST, i, RYE_ID, settings.isRyeSelected, model)
    }
}

function addIfActive(list, index, currentId, active, model) {
    if (list[index].id === currentId && active) {
        model.append(list[index]);
        console.log("added pollen : " + list[index].label);
    }
}

function addPollenIdIfActive(selection, currentId, active) {
    if (active) {
        selection.push(currentId);
    }
}

function getSelectedPollenList(settings) {
    var selection = [];
    addPollenIdIfActive(selection, MUGWORT_ID, settings.isMugwortSelected)
    addPollenIdIfActive(selection, BIRCH_ID, settings.isBirchSelected)
    addPollenIdIfActive(selection, ALDER_ID, settings.isAlderSelected)
    addPollenIdIfActive(selection, ASH_TREE_ID, settings.isAshTreeSelected)
    addPollenIdIfActive(selection, GRASS_ID, settings.isGrassPollenSelected)
    addPollenIdIfActive(selection, HAZEL_ID, settings.isHazelSelected)
    addPollenIdIfActive(selection, AMBROSIA_ID, settings.isAmbrosiaSelected)
    addPollenIdIfActive(selection, RYE_ID, settings.isRyeSelected)
    return selection;
}

function getDataBackend() {
    if (COUNTRY_GERMANY === pollenflugSettings.country) {
        return germanPollenBackend;
    } else if (COUNTRY_FRANCE === pollenflugSettings.country) {
        return frenchPollenBackend;
    }
    console.error("pollen backend not found !");
}

function addDays(date, days) {
  var copy = new Date(Number(date))
  copy.setDate(date.getDate() + days)
  return copy;
}

// TODO germany specific functions
function calculateRegion(storedRegion) {
    return (storedRegion + 1) * 10;
}

function calculatePartRegion(calculatedRegion, storedPartRegion) {
    if (storedPartRegion !== -1) {
        return calculatedRegion + (storedPartRegion + 1)
    }
    return storedPartRegion;
}


