# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-pollenflug

CONFIG += sailfishapp

SOURCES += src/harbour-pollenflug.cpp \
    src/pollenflug.cpp

HEADERS += \
    src/pollenflug.h

DEFINES += VERSION_NUMBER=\\\"$$(VERSION_NUMBER)\\\"

DISTFILES += qml/harbour-pollenflug.qml \
    qml/components/PollenDateRow.qml \
    qml/components/PollenIconTextSwitch.qml \
    qml/components/PollenLabel.qml \
    qml/components/PollenPollutionNotUpToDateRow.qml \
    qml/components/PollenPollutionRow.qml \
    qml/components/PollenPollutionScaleRow.qml \
    qml/components/PollenRow.qml \
    qml/components/PollenScale.qml \
    qml/components/PollenTile.qml \
    qml/components/PollenTitleRow.qml \
    qml/components/SettingsFrance.qml \
    qml/components/SettingsGermany.qml \
    qml/components/thirdparty/LabelText.qml \
    qml/components/thirdparty/LoadingIndicator.qml \
    qml/components/thirdparty/AppNotification.qml \
    qml/components/thirdparty/AppNotificationItem.qml \
    qml/cover/CoverPage.qml \
    qml/js/constants.js \
    qml/js/functions.js \
    qml/pages/MapPage.qml \
    qml/pages/OverviewPage.qml \
    qml/pages/AboutPage.qml \
    qml/pages/SettingsPage.qml \
    rpm/harbour-pollenflug.changes.in \
    rpm/harbour-pollenflug.spec \
    rpm/harbour-pollenflug.yaml \
    translations/*.ts \
    qml/pages/icons/github.svg \
    qml/pages/icons/paypal.svg \
    qml/pages/icons/flaticon-color-negative.svg \
    qml/pages/icons/ambrosia.svg \
    qml/pages/icons/mugwort.svg \
    qml/pages/icons/birch.svg \
    qml/pages/icons/alder.svg \
    qml/pages/icons/ashtree.svg \
    qml/pages/icons/grass.svg \
    qml/pages/icons/hazel.svg \
    qml/pages/icons/rye.svg \
    qml/pages/icons/background.png \
    qml/pages/icons/background-black.png \
    harbour-pollenflug.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-pollenflug-de.ts \
    translations/harbour-pollenflug-fr.ts

include(harbour-pollenflug.pri)

