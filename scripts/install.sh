#!/bin/sh
set -e

if command -v apt-get >/dev/null 2>&1; then
	echo "Detected apt-get"
	sudo apt-get update && sudo apt-get install -y build-essential liballegro5-dev liballegro-image5-dev liballegro-audio5-dev liballegro-acodec5-dev liballegro-ttf5-dev liballegro-dialog5-dev pkg-config
elif command -v dnf >/dev/null 2>&1; then
	echo "Detected dnf"
	sudo dnf install -y allegro5-devel allegro5-addon-image-devel allegro5-addon-audio-devel allegro5-addon-acodec-devel allegro5-addon-ttf-devel allegro5-addon-dialog-devel pkgconf-pkg-config
elif command -v pacman >/dev/null 2>&1; then
	echo "Detected pacman"
	sudo pacman -S --noconfirm allegro pkgconf
elif command -v brew >/dev/null 2>&1; then
	echo "Detected brew"
	brew install allegro pkg-config
else
	echo "Unsupported package manager. Please install dependencies manually."
	exit 1
fi
