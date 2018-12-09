/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: big_bang_core.h
*
*   Description: Header file for big_bang_core module. This module represents
*               the "core" algorithm of the application (not the entry point).
*               It checks the user configuration, generates the random galaxy
*               and writes it in the png file, alongside with related cleanup
*               and error handling operations. It is called "big_bang" because,
*               as the homonymous theory, its the "origin" of the data.
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

#ifndef _8BH_BIG_BANG_CORE_H
#define _8BH_BIG_BANG_CORE_H
int start_big_bang (void); /* Core function of the application. */
#endif /* _BIG_BANG_CORE_H */
