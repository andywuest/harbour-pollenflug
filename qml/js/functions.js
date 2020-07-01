
Qt.include('constants.js');

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

function getDataBackend() {
    return germanPollenBackend;
}
