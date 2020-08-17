#!/bin/bash

for x in 86 108 128 172
do
  inkscape --export-png icons/${x}x${x}/harbour-pollenflug_original.png -w ${x} mediasrc/pollenflug_icon_normal.svg
  pngcrush -brute icons/${x}x${x}/harbour-pollenflug_original.png icons/${x}x${x}/harbour-pollenflug.png
done
