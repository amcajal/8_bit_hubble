/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: canvas.h
*
*   Description: Header file for canvas module. Canvas module contains both
*               the data structure representing the canvas (where the galaxy
*               will be painted), and related management operations.
*               The core concept of a canvas is its dimensions, width and height
*               that define at the same time the size of the output image.
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

#ifndef _8BH_CANVAS_H
#define _8BH_CANVAS_H

struct canvas {
	int dim_x; /* Width. */
	int dim_y; /* heigth. */
    int total_pixels; /* Width x Heigth. This data is redundant, but it is
                        considered better to store it rather than calculate
                        it everytime it is needed. */
	int *data; /* Each int represents a pixel and its RGB color. */
};

void set_canvas_dimensions(int dim_x, int dim_y, struct canvas *ptr_c);
void initialize_canvas_to_black(struct canvas *ptr_c);
void delete_canvas(struct canvas *ptr_c);

#endif
