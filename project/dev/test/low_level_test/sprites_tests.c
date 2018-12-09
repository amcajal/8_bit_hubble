/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: sprites_tests.c
*
*   Description: Source file of sprites tests module. It verifies that all
*               sprites can be "printed" in a PNG image, although the validation
*               of the sprite itself must be done manually (correctness of
*               the sprite must be decided by the user).
*
*   Notes: Given the number of dependencies of this module, it can be used
*           as the verification module for:
*           - image_writer module
*           - brush module
*           - canvas module
*           - app_info module
*           - rng and palette module already tested in dedicated tests modules.
*
*           
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
#include "../../src/sprites/sprites.h"
#include "../../src/image_writer/image_writer.h"
#include "../../src/brush/brush.h"
#include "../../src/canvas/canvas.h"
#include "../../src/palette/palette.h"
#include "../../src/app_info/app_info.h"
#include "../../src/rng/rng.h"
#include <stdio.h>

struct canvas test_canvas;
struct brush test_brush;
static int blue_color_index = 180;
p_sprite selected_sprite;
char png_name[30];

void set_png_name(int index)
{
    switch(index)
    {
        case 0:
            sprintf(png_name, "square_star_2x2");
            break;
        case 1:
            sprintf(png_name, "square_star_4x4");
            break;
        case 2:
            sprintf(png_name, "cross_star_5x5");
            break;
        case 3:
            sprintf(png_name, "square_star_6x6");
            break;
        case 4:
            sprintf(png_name, "cross_star_10x10");
            break;
        case 5:
            sprintf(png_name, "cross_star_12x12");
            break;
        case 6:
            sprintf(png_name, "cross_star_16x16");
            break;
        case 7:
            sprintf(png_name, "cross_star_20x20");
            break;
        case 8:
            sprintf(png_name, "cross_star_30x30");
            break;
        case 9:
            sprintf(png_name, "combined_star_48x48");
            break;
    }
}

void generate_all_sprites (void) 
{
	set_canvas_dimensions(SPRITE_MAX_DIM_X, SPRITE_MAX_DIM_Y, &test_canvas);
	initialize_palette(ANSI_216_COLORS);
	generate_tints_and_shades(blue_color_index, &test_brush);
	test_brush.position = 0;
	
    int sprite_index;
    
    for (sprite_index = 0; sprite_index < NUMBER_SMALL_SPRITES; sprite_index++)
    {
		initialize_canvas_to_black(&test_canvas);
		selected_sprite = get_small_sprite(sprite_index);
		selected_sprite(&test_canvas, &test_brush);
        set_png_name(sprite_index);
		write_image(&test_canvas, "./", png_name);
    }
    
    for (sprite_index = 0; sprite_index < NUMBER_MEDIUM_SPRITES; sprite_index++)
    {
		initialize_canvas_to_black(&test_canvas);
		selected_sprite = get_medium_sprite(sprite_index);
		selected_sprite(&test_canvas, &test_brush);
        set_png_name(sprite_index+NUMBER_SMALL_SPRITES);
		write_image(&test_canvas, "./", png_name);
    }
    
    for (sprite_index = 0; sprite_index < NUMBER_BIG_SPRITES; sprite_index++)
    {
		initialize_canvas_to_black(&test_canvas);
		selected_sprite = get_big_sprite(sprite_index);
		selected_sprite(&test_canvas, &test_brush);
        set_png_name(
            sprite_index + NUMBER_MEDIUM_SPRITES + NUMBER_SMALL_SPRITES);
		write_image(&test_canvas, "./", png_name);
    }

	delete_canvas(&test_canvas);
}

void run_sprites_tests(void)
{
	generate_all_sprites();
	printf("sprites_tests: All sprites successfully generated.\n");
}
