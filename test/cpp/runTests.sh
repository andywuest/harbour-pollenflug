#/bin/bash

set -x

find . -name "*.o" -exec rm  {} \;
find . -name "*.tap" -exec rm  {} \;
find . -name "moc_*" -exec rm  {} \;
find . -name "Makefile" -exec rm  {} \;

qmake -o Makefile harbour-pollenflug-tests.pro
make VERBOSE=1

cat Makefile
ls -l Pollen*

env LC_ALL=de_DE.UTF-8 LC_NUMERIC=de_DE.utf8 ./PollenBackendTest -junitxml -o junit.xml


