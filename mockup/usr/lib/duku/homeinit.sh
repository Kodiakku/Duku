#!/bin/bash

cd $HOME
mkdir code

#IN CODE
cd code
mkdir scripts
mkdir sources
mkdir libs
mkdir executables
cd $HOME

mkdir Desktop
mkdir Documents

#IN DOCUMENTS
cd Documents
mkdir shcolar
mkdir work
cd $HOME

mkdir Media
mkdir Images

#IN IMAGES
cd Images
mkdir wallpaper
mkdir screenshots
mkdir internet
mkdir res
cd $HOME

mkdir Resources

#IN RESOURCES
cd Resources
mkdir config
cd config
touch naiConfig
cd ..
touch learn
touch langdefines.ldf
cd $HOME

mkdir Templates

#COPY TEMPLATES OVER
mv /usr/lib/duku/cppTemplate.cpp $HOME/Templates/
mv /usr/lib/duku/bashTemplate.sh $HOME/Tempaltes/
mv /usr/lib/duku/javaTemplate.java $HOME/Templates/

mv /usr/share/awesome/lib/themes/background.png $HOME/Pictures/wallpaper
