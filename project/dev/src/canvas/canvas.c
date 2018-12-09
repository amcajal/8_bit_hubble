/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: canvas.c
*
*   Description: Source code for canvas module. Canvas module contains both
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

#include <stdlib.h>
#include "./canvas.h"
#include "../sprites/sprites.h"

/*
* Initially, reserved memory was equal to the total pixels of the canvas.
* Problem was that, in some ocasiones (galaxy generation is random), an overflow
* took place due to painting a big sprite in the last pixels of the canvas
* (that is, the remaining pixels wasn't enough to hold the sprite). To avoid
* this (and avoid bound checking instructions that slow the program a lot)
* it was decided to add a SAFETY MARGIN (additional memory or pixels).
* This additional memory is big enough to hold the biggest sprite in the
* program, starting at the very last pixel of the original dimensions
* of the canvas.
* This additional memory is later discarded (png image is the same size than
* the original dimensions). Benefit is that is faster (less instructions
* executed) than check bounds continuosly.
*/
static int safety_margin;

void set_canvas_dimensions(int dim_x, int dim_y, struct canvas *ptr_c)
{
	ptr_c->dim_x = dim_x;
	ptr_c->dim_y = dim_y;
    ptr_c->total_pixels = ptr_c->dim_x * ptr_c->dim_y;
}

void initialize_canvas_to_black(struct canvas *ptr_c)
{
    safety_margin = SPRITE_MAX_DIM_Y * ptr_c->dim_x;
	ptr_c->data = calloc(ptr_c->total_pixels + safety_margin, sizeof(int));
}

void delete_canvas(struct canvas *ptr_c)
{
	if (ptr_c->data)
		free(ptr_c->data);
}
