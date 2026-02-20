#!/bin/sh
set -ex

# shellcheck disable=SC2046
# shellcheck disable=SC2312
g++ main.cc -o main $(pkg-config --cflags --libs allegro-5 allegro_primitives-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5 allegro_dialog-5)
