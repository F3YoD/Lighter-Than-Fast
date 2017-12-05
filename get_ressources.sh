#!/usr/bin/env bash
# Download custom fonts and music

# Ressources URLs
# Fonts
FIRAMONO_URL="https://github.com/mozilla/Fira/raw/master/ttf/FiraMono-Regular.ttf"
FA_URL="https://github.com/FortAwesome/Font-Awesome/raw/master/fonts/fontawesome-webfont.ttf"
# MIDI
MIDI_URL="https://www.dropbox.com/sh/l28n6wzh9l4guvr/AADJipJ9WZv6PWnQXW8N78T9a?dl=1"

# Ressources folders
FONTS_FOLDER=../assets/fonts
MIDI_FOLDER=../assets/midi

# Initialisation
# Look for wget
if [ "$(which wget)" != "" ]; then
    download="wget -q --show-progress -O"
elif [ "$(which curl)" != "" ]; then
    download="curl -o"
else
    echo "wget and curl not found in PATH. Please install one of them."
    exit 1
fi


# Create folders in case they don't exist
mkdir -p $FONTS_FOLDER $MIDI_FOLDER

( # Subshell to ease use of `cd`
# Download & extract fonts, and remove temp files
if [ ! -e $FONTS_FOLDER/Inter-UI-Regular.ttf ]; then
    cd $FONTS_FOLDER
    echo "Downloading font Fira Mono..."
    $download firamono.ttf $FIRAMONO_URL
fi
)

(
if [ ! -e $FONTS_FOLDER/fontawesome.ttf ]; then
    cd $FONTS_FOLDER
    echo "Downloading font FontAwesome..."
    $download fontawesome.ttf $FA_URL
fi
)

(
if [[ "$(ls $MIDI_FOLDER)" == "" ]]; then
    cd $MIDI_FOLDER
    echo "Downloading MIDI files..."
    $download midi.zip $MIDI_URL
    unzip midi.zip
    rm -r midi.zip
fi
)
