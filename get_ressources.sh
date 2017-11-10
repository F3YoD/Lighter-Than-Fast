#!/usr/bin/env bash
# Download custom fonts

# Ressources URLs
# Fonts
INTER_UI_URL="https://github.com/rsms/inter/releases/download/v2.1/Inter-UI-2.1.zip"
# MIDI
MIDI_URL="https://www.dropbox.com/sh/l28n6wzh9l4guvr/AADJipJ9WZv6PWnQXW8N78T9a?dl=1"

# Ressources folders
FONTS_FOLDER=../assets/fonts
MIDI_FOLDER=../assets/midi

# Initialisation
# Look for wget
if [[ "$(which wget)" == "" ]]; then
    echo "wget not found in PATH. Please install it."
    exit 1
fi

# Create necessary folders, download, extract, and remove temp files
if [ ! -f $FONTS_FOLDER/Inter-UI-Regular.ttf ]; then
    mkdir -p $FONTS_FOLDER
    cd $FONTS_FOLDER
    echo "Downloading fonts..."
    wget --no-verbose -O inter.zip $INTER_UI_URL
    tar xvzf inter.zip "Inter UI (TTF)/*"
    mv ./Inter\ UI\ \(TTF\)/*.ttf .
    rm -r "Inter UI (TTF)/" inter.zip
fi

echo "Fonts successfully downloaded."
