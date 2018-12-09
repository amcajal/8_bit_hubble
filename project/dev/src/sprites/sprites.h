/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: sprites.h
*
*   Description: Header file of Sprites module. As it names implies,
* 				Sprites module contains the sprites that can be generated
* 				in the galaxy. A sprite is characterized by its size,
* 				and the pixels where it shall be painted. The module
* 				provides a clean interface to "stamp" or "print"
* 				a sprite into the canvas.
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
#ifndef _8BH_SPRITES_H
#define _8BH_SPRITES_H

#include "../canvas/canvas.h"
#include "../brush/brush.h"

//@TODO always match number of different sprites with this macro
#define NUMBER_SMALL_SPRITES 3
#define NUMBER_MEDIUM_SPRITES 4
#define NUMBER_BIG_SPRITES 3

/* A sprite, at max, is 50x50 pixels. */
#define SPRITE_MAX_DIM_X 50
#define SPRITE_MAX_DIM_Y 50

typedef void (*p_sprite)(struct canvas *p_c, struct brush *p_b);
 
p_sprite get_small_sprite(int sprite_id);
p_sprite get_medium_sprite(int sprite_id);
p_sprite get_big_sprite(int sprite_id);

#endif
