/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: sprites_tests.h
*
*   Description: Header file of sprites tests module. It verifies that all
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

#ifndef _8BH_SPRITES_TESTS_H
#define _8BH_SPRITES_TESTS_H
void run_sprites_tests(void);
#endif // _8BH_SPRITES_TESTS_H
