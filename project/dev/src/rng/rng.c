/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: rng.c
*
*   Description: Source file of RNG module. RNG module provides a clean
* 				interface to deal with Random Number Generator methods.
* 				It basically generates random numbers on demmand. 
* 				Generation can be configured through a seed.
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
#include <time.h>

static int rng_seed = -1;

void load_seed(int seed)
{
	rng_seed = seed;
    if (rng_seed == -1) { /* User dont provide a custom seed.*/
        time_t current_time;
        rng_seed = time(&current_time);
    }
    srand((unsigned) rng_seed);
}

int generate_rn_up_to(int max_number)
{
	if (max_number <= 0)
		return 0;
	else
		/* Return a number from 0 to max_number - 1. */
		return rand() % max_number;
}

int generate_rn_within(int min, int max)
{
    /* Return a number from min to max. */
    return generate_rn_up_to((max - min) + 1) + min;
}

int get_seed(void)
{
    return rng_seed;
}
