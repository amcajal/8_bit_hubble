/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: palette.c
*
*   Description: Source file for palette module. Palette implements
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
#include <stdio.h>
#include <stdlib.h>
#include "./palette.h"
#include "../status_reporter/status_reporter.h"
#include "../brush/brush.h"

#define RGB_COMPONENT_MAX_VAL 255

#define TINT_SMALL_FACTOR 0.5
#define TINT_BIG_FACTOR 0.75

#define SHADE_SMALL_FACTOR 0.5
#define SHADE_BIG_FACTOR 0.25

static int *palette;
static int total_colors = 0;
static int basic_colors[8];

/* Generate a palette of 216 colors, based on the ANSI escape codes. */
int generate_ansi_216_color_palette(void)
{
    total_colors = 216;
    if (palette)
        free(palette);
    palette = (int*)calloc(total_colors, sizeof(int));
    if (!palette) return 1;
    
    int red, green, blue;
    int i, j, k, index;
    
    red = green = blue = 0x00000000;
    i = j = k = 0;
    
    /* Red component generation. */
    for (i = 0; i < 6; i++)
    {
        if (i == 0)
            red = 0x000000;
        else if (i == 1)
            red += 0x5F0000;
        else
            red += 0x280000;
        
        /* Green component generation. */
        for (j = 0; j < 6; j++)
        {
            if (j == 0)
                green = 0x0000;
            else if (j == 1)
                green += 0x5F00;
            else
                green += 0x2800;
              
            /* Blue component generation. */
            for (k = 0; k < 6; k++)
            {
                if (k == 0)
                    blue = 0x00;
                else if (k == 1)
                    blue += 0x5F;
                else
                    blue += 0x28;
                
                index = (i * 36) + (j*6) + k;
                palette[index] = red + green + blue;
            }
        }
    }
    
    /* 
    * In order: red, orange, yellow, green, blue, indigo, violet, white. 
    * RGB of the indexes doesn't perfectly match the "standard" RGB values
    * for the mentioned colors.
    */
    basic_colors[0] = 180;
    basic_colors[1] = 192;
    basic_colors[2] = 210;
    basic_colors[3] = 30;
    basic_colors[4] = 5;
    basic_colors[5] = 38;
    basic_colors[6] = 75;
    basic_colors[7] = 215;
    return 0;
}

int get_color_from_index(int index)
{    
    if (index > (total_colors - 1)) 
        index = total_colors - 1;
    else if (index <= 0)
        index = 0;
        
    return palette[index];
}

enum status initialize_palette(enum palette_type pal_type)
{
    enum status stat = NO_ERROR;
    int result = 0;
    
    switch(pal_type) {
        case ANSI_216_COLORS:
            result = generate_ansi_216_color_palette();
            break;
        default:
            result = 2;
            break;
    }
    
    if (result == 1) 
        stat = PALETTE_NOT_INITIALIZED;
    else if (result == 2)
        stat = INVALID_PALETTE;
        
    return stat;    
}

int get_number_available_colors(void)
{
    return total_colors;
}

int get_tint_from_color(int input_color, double tint_factor)
{
    int red_component = (input_color >> 16) & 0xFF;
    int green_component = (input_color >> 8) & 0xFF;
    int blue_component = input_color & 0xFF;
    
    int new_red_component = red_component + (int)((RGB_COMPONENT_MAX_VAL - red_component)*tint_factor);
    int new_green_component = green_component + (int)((RGB_COMPONENT_MAX_VAL - green_component)*tint_factor);
    int new_blue_component = blue_component + (int)((RGB_COMPONENT_MAX_VAL - blue_component)*tint_factor);
    
    int tint_color = new_red_component;
    tint_color = (tint_color << 8) + new_green_component;
    tint_color = (tint_color << 8) + new_blue_component;
    return tint_color;
}

int get_shade_from_color(int input_color, double shade_factor)
{
    int new_red_component = (int)(
            (float)((input_color >> 16) & 0xFF) * shade_factor
        );
    int new_green_component = (int)(
            (float)((input_color >> 8) & 0xFF) * shade_factor
        );
    int new_blue_component = (int)(
            (float)(input_color & 0xFF) * shade_factor
        );
    
    int shadowed_color = new_red_component;
    shadowed_color = (shadowed_color << 8) + new_green_component;
    shadowed_color = (shadowed_color << 8) + new_blue_component;
    return shadowed_color;
}

void generate_tints_and_shades(int input_color, struct brush *p_b)
{
    /* The base color is not generated in this method, to allow the user give
    * as parameter either a color retrived from index, or a basic color. */
    
    /* Base color. */
    p_b->color[2] = input_color;
    
    /* Generate tints. */
    p_b->color[0] = get_shade_from_color(input_color, SHADE_BIG_FACTOR);
    p_b->color[1] = get_shade_from_color(input_color, SHADE_SMALL_FACTOR);
    
    /* Generate shades. */
    p_b->color[3] = get_tint_from_color(input_color, TINT_SMALL_FACTOR);
    p_b->color[4] = get_tint_from_color(input_color, TINT_BIG_FACTOR);
}
