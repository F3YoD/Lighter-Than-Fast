#!/usr/bin/env bash
# Download custom fonts

# Look for wget
if [[ "$(which wget)" == "" ]]; then
    echo "wget not found in PATH. Please install it."
    exit 1
fi

INTER_UI_URL="https://github.com/rsms/inter/releases/download/v2.1/Inter-UI-2.1.zip"
FONTS_FOLDER=ressources/fonts

# Create necessary folders, download, extract, and remove temp files
if [ ! -f $FONTS_FOLDER/Inter-UI-Regular.ttf ]; then
    mkdir -p $FONTS_FOLDER
    cd $FONTS_FOLDER
    wget -O inter.zip $INTER_UI_URL
    tar xvf inter.zip "Inter UI (TTF)/*"
    mv "Inter UI (TTF)/*" .
    rm -r "Inter UI (TTF)/" inter.zip
fi

echo "Fonts successfully downloaded."
