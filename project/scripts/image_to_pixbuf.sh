#!/bin/bash
################################################################################
#   Project: 8-Bit Hubble.
#
#   File: image_to_pixbuf.sh
#
#   Description: Convert png image into "C source code" using the GTK
#		utility "gdk-pixbuf-csource".
#
#   Notes: N/A
#
#   Contact: Alberto Martin Cajal, amartin.glimpse23<AT>gmail.com
#
#   URL: https://github.com/amcajal/8_bit_hubble
#
#   License: GNU GPL v3.0
#
#   Copyright (C) 2018 Alberto Martin Cajal
#
#   This file is part of 8-Bit Hubble.
#
#   8-Bit Hubble is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   8-Bit Hubble is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
################################################################################

if [ "$#" -ne 1 ]; then
	echo "Usage: image_to_pixbuf.sh <image_to_convert>"
	echo "I.e: image_to_pixbuf /home/luckystar/img/venus.png"
	echo "Output file is by default called 8bH_logo.h"
	echo "More information at https://dustri.org/b/embed-image-into-a-gtk-application.html"
	exit 1
fi

gdk-pixbuf-csource --raw --name=app_logo $1 > ./8bH_logo.h
