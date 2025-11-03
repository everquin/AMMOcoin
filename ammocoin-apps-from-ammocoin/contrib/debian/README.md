
Debian
====================
This directory contains files used to package ammocoind/ammocoin-qt
for Debian-based Linux systems. If you compile ammocoind/ammocoin-qt yourself, there are some useful files here.

## ammocoin: URI support ##


ammocoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install ammocoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your ammocoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/ammocoin128.png` to `/usr/share/pixmaps`

ammocoin-qt.protocol (KDE)

