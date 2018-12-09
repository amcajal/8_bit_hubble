/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: galaxy_generator.c
*
*   Description: Source file of galaxy_generator module. Galaxy_generator
* 				module implementes the CORE algorithm of the application.
* 				It initializes the canvas and the palette, and then,
* 				by layers, print the sprites on it, in a random fashion
* 				(ubication, size, color).
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
#include "../status_reporter/status_reporter.h"
#include "../canvas/canvas.h"
#include "../palette/palette.h"
#include "../rng/rng.h"
#include "../sprites/sprites.h"
#include "../brush/brush.h"

#define LAYERS_PER_SECTION 3

/* Density for the sprites according to its size. */
#define SMALL_SPRITE_MIN_D 500
#define SMALL_SPRITE_MAX_D 1000

#define MEDIUM_SPRITE_MIN_D 5000
#define MEDIUM_SPRITE_MAX_D 10000

#define BIG_SPRITE_MIN_D 10000
#define BIG_SPRITE_MAX_D 25000

static int total_available_colors = 0;
static p_sprite sprite_to_paint;
static struct brush old_brush = {{-1, -1, -1, -1, -1}, /* No color loaded. */
                                -1, /* No position loaded. */ 
                                -1}; /* No density loaded. */
static struct canvas *l_p_gc; /* local_pointer_galaxycanvas. */

// @TODO put this in sprites sizes
enum star_type {
	SMALL = 0,
	MEDIUM = 1,
	BIG = 2
};
				
void paint_sprite(void)
{
	int index_pixel;
	for (index_pixel = 0; index_pixel < l_p_gc->total_pixels; index_pixel+=old_brush.density) {
		old_brush.position = generate_rn_up_to(old_brush.density) + index_pixel;
        
        /* The following comparisson is to avoid a SIGSEGV 
        * due to old_brush.position bigger than 250_000.
        * With the safety margin, such error should not appear. However,
        * it is added as a safety mechanism.
        */
        if (old_brush.position > l_p_gc->total_pixels)
            old_brush.position = l_p_gc->total_pixels-1;
		sprite_to_paint(l_p_gc, &old_brush);
	}	
}

void paint_cosmic_background(void)
{
	/* Choose color. */
    generate_tints_and_shades(
        get_color_from_index(generate_rn_up_to(total_available_colors)),
        &old_brush);
	
	int index_pixel;
	for (index_pixel = 0; index_pixel < l_p_gc->total_pixels; index_pixel++) {
		l_p_gc->data[index_pixel] = old_brush.color[0]; /* Shade big factor color.*/
	}
}

void paint_stars(int layers, enum star_type star_t)
{
	int layer_index;
	for (layer_index = 0; layer_index < layers; layer_index++) {
		
		switch (star_t) {
			case SMALL:
                // @TODO just ask for a sprite, and sprite module will be on charge to return a type
                // do something like: sprite_to_paint = get_sprite(SMALL);
                sprite_to_paint = get_small_sprite(generate_rn_up_to(NUMBER_SMALL_SPRITES));
				old_brush.density = generate_rn_within(SMALL_SPRITE_MIN_D, SMALL_SPRITE_MAX_D);
				break;
				
			case MEDIUM:
				sprite_to_paint = get_medium_sprite(generate_rn_up_to(NUMBER_MEDIUM_SPRITES));
				old_brush.density = generate_rn_within(MEDIUM_SPRITE_MIN_D, MEDIUM_SPRITE_MAX_D);
				break;
				
			case BIG:
				sprite_to_paint = get_big_sprite(generate_rn_up_to(NUMBER_BIG_SPRITES));
				old_brush.density = generate_rn_within(BIG_SPRITE_MIN_D, BIG_SPRITE_MAX_D);
				break;
		}
        generate_tints_and_shades(
            get_color_from_index(generate_rn_up_to(total_available_colors)),
            &old_brush);
            
		/* Paint. */
		paint_sprite();
	}
}

enum status generate_galaxy(struct canvas *gc)
{
	enum status stat = NO_ERROR;
	l_p_gc = gc;
    
	/* Init canvas with whole background in black color. */
    set_canvas_dimensions(500, 500, l_p_gc);
    initialize_canvas_to_black(l_p_gc);
	
	if (!l_p_gc->data) {
		return CANNOT_RESERVE_MEM;
	}
	
	/* Init palette of colors. */
	stat = initialize_palette(ANSI_216_COLORS);
	if (stat != NO_ERROR)
		return stat;
	total_available_colors = get_number_available_colors();
	
	/*** Start painting. ***/
	int layers_for_current_phase;
	
	/* Apply cosmic background color. */
	layers_for_current_phase = generate_rn_up_to(2); 
	if (layers_for_current_phase != 0)
		paint_cosmic_background();
	
	/* Paint small stars. */
	layers_for_current_phase = generate_rn_up_to(3) + 1;
	paint_stars(layers_for_current_phase, SMALL);
	
	/* Paint medium stars. */
	layers_for_current_phase = generate_rn_up_to(4);
	if (layers_for_current_phase != 0)
		paint_stars(layers_for_current_phase, MEDIUM);
	
	/* Paint big stars. */
	layers_for_current_phase = generate_rn_up_to(4);
	if (layers_for_current_phase != 0)
		paint_stars(layers_for_current_phase, BIG);
    
	return stat;
}
