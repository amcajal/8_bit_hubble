/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: image_writer.h
*
*   Description: Header file for image_writer module. Image writer
* 				generates ("writes") the final PNG image with the
* 				created galaxy. Its core is the PNG library to create
* 				the PNG image with the required data (magic number,
* 				header data, etc).
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
#ifndef _8BH_IMAGE_WRITER_H
#define _8BH_IMAGE_WRITER_H

#include "../status_reporter/status_reporter.h"
#include "../canvas/canvas.h"

enum status write_image(struct canvas *ptr_c, char *file_path, 
	 char *file_name);

#endif


