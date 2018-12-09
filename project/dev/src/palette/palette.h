/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: palette.h
*
*   Description: Header file for palette module. Palette implements
* 				the data structure that represents the real "palette"
* 				of colors. It also implements the required methods
* 				to obtain a color from it, and generate tints and
* 				shadows, like a real painter would do.
*
*   Notes: N/A
*
*   Contact: Alberto Martin Cajal, amartin.glimpse23<AT>gmail.com
*
*   URL: https://github.com/amcajal/8_bit_hubble
*
*   License: GNU GPL v3.0
*
*   Copyright (C) 2018 Alberto Martin Cajal
*
*   This file is part of 8-Bit Hubble.
*
*   8-Bit Hubble is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   8-Bit Hubble is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/
#ifndef _8BH_PALETTE_H
#define _8BH_PALETTE_H

#include "../status_reporter/status_reporter.h"
#include "../brush/brush.h"

enum palette_type {
    ANSI_216_COLORS = 0
};

enum status initialize_palette(enum palette_type pal_type);
int get_number_available_colors(void);
int get_color_from_index(int index);
void generate_tints_and_shades(int input_color, struct brush *p_b);

#endif
