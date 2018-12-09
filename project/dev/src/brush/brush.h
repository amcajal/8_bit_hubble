/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: brush.h
*
*   Description: Header file for brush module. Brush module contains the data
*               structure that represents a painting brush, characterized by
*               the color loaded on it, its position on the canvas, and the
*               "density" of the brushstrokes (more or less objects being
*               painted in the canvas).
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
#ifndef _8BH_BRUSH_H
#define _8BH_BRUSH_H

struct brush {
    int color[5]; /* 5 different tones from the chosen palette color:
                    color[0] = shade big factor color
                    color[1] = shade small factor color
                    color[2] = base color (color chosen from the palette)
                    color[3] = tint small factor color
                    color[4] = tint big factor color */
                    
	int position; /* Top-left pixel of the sprite to be painted -initial position. */
    int density; /* Depending on how the brush is loaded, more or less sprites will be painted. */
};

#endif 
