# Texed
Texed is a lightweight text editor developed entirely in C. With it, you can edit any text file. Below, you can see screenshots as well as the available features and those that will be coming soon.

Thank you for using Texed.

## Screenshots
<br> <img src="https://github.com/xdanep/texed/blob/master/screenshots/texed.png"/> <br>

## Installation
- Install dependencies
```
Debian based:
$ sudo apt install build-essential libncurses-dev libncursesw6

Fedora/RHEL:
$ sudo dnf install gcc ncurses ncurses-devel

Arch based:
$ sudo pacman -Sy gcc ncurses
```
- `# make install` move files to properly dirs and include them to PATH
- `# make uninstall` remove files 
- Run `$ texed "filedir"`

### Available features
- Writing, reading and editing text
- Status bar (Taskit "Version" "File")
- Shortcuts in the bottom
- Vertical and horizontal scrolling

### Features to be added

### Issues

# Dependencies
### - `ncurses`
### - `gcc`

## Contributing
You can use Texed as a foundation to develop your own editor, or you can also contribute to the project in one of the following ways:
- Submit bugs and feature requests, and help us verify as they are checked in
- Review source code changes

## Licence
Licensed under the GPL-3.0 license.

Code from https://github.com/snaptoken/kilo-src licensed under BSD-2-Clause license
Copyright (c) 2016, Salvatore Sanfilippo <antirez at gmail dot com>

All rights reserved.