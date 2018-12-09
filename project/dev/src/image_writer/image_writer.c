/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: image_writer.c
*
*   Description: Source file for image_writer module. Image writer
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <png.h>
#include "../status_reporter/status_reporter.h"
#include "../canvas/canvas.h"
#include "../app_info/app_info.h"
#include "../rng/rng.h"

#define IMAGE_TITLE "8bitHubbleImage"
/*
* This takes the int value 'val', converts it to red, green & blue values, then 
* sets those values into the image memory buffer location pointed to by 'ptr'.
*/
inline void setRGB(png_byte *ptr, int val);

/*
* This function actually writes out the PNG image file. The string 'title' is
* also written into the image file.
*/
int write_png(char* filename, int width, int height, int *buffer);


enum status write_image(struct canvas *ptr_c, 
	char *file_path, char *file_name)
{
	enum status stat = NO_ERROR;
	
	/* Add 5 extra chars: 4 for ".png" and the termination char. */
	char *abs_path = malloc(
		(strlen(file_path) + strlen(file_name) + 5) 
		* sizeof(char));
	strcpy(abs_path, file_path);
	strcat(abs_path, file_name);
	strcat(abs_path, ".png");
	
	int result = write_png(abs_path, 
		ptr_c->dim_x, ptr_c->dim_y, ptr_c->data);
	free(abs_path);
	if (result != 0)
		return CANNOT_WRITE_IMAGE;
	return stat;
}

inline void setRGB(png_byte *ptr, int val)
{
    ptr[0] = (val >> 16) & 0xFF; 
    ptr[1] = (val >> 8) & 0xFF; 
    ptr[2] = val & 0xFF; 
}

int write_png(char* filename, int width, int height, int *buffer)
{
	int code = 0;
	FILE *fp = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row = NULL;
	
	// Open file for writing (binary mode)
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file %s for writing\n", filename);
		code = 1;
		goto finalise;
	}

	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fprintf(stderr, "Could not allocate write struct\n");
		code = 1;
		goto finalise;
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fprintf(stderr, "Could not allocate info struct\n");
		code = 1;
		goto finalise;
	}

	png_init_io(png_ptr, fp);

	// Write header (8 bit colour depth)
	png_set_IHDR(png_ptr, info_ptr, width, height,
			8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	// Set title
    png_text title_text;
    title_text.compression = PNG_TEXT_COMPRESSION_NONE;
    title_text.key = "Title";
    title_text.text = IMAGE_TITLE;
    png_set_text(png_ptr, info_ptr, &title_text, 1);
    
    // Set description
    png_text description_text;
    description_text.compression = PNG_TEXT_COMPRESSION_NONE;
    description_text.key = "Description";
    description_text.text = get_project_repo();
    png_set_text(png_ptr, info_ptr, &description_text, 1);
    
    // Set Copyright
    png_text cr_text;
    cr_text.compression = PNG_TEXT_COMPRESSION_NONE;
    cr_text.key = "Copyright";
    cr_text.text = get_project_copyright();
    png_set_text(png_ptr, info_ptr, &cr_text, 1);
    
    // Set comment (seed used in this image)
    png_text comment_text;
    comment_text.compression = PNG_TEXT_COMPRESSION_NONE;
    comment_text.key = "Comment";
    /* itoa is not standard, so we need to use snprintf */
    int seed_string_len = snprintf(NULL, 0, "%d", get_seed()) + 1;
    comment_text.text = malloc(seed_string_len * sizeof(char));
    sprintf(comment_text.text, "%d", get_seed());
    png_set_text(png_ptr, info_ptr, &comment_text, 1);

	png_write_info(png_ptr, info_ptr);

	// Allocate memory for one row (3 bytes per pixel - RGB)
	row = (png_bytep) malloc(3 * width * sizeof(png_byte));

	// Write image data
	int x, y;
	for (y=0 ; y<height ; y++) {
		for (x=0 ; x<width ; x++) {
			setRGB(&(row[x*3]), buffer[y*width + x]);
		}
		png_write_row(png_ptr, row);
	}

	// End write
	png_write_end(png_ptr, NULL);

	finalise:
	if (fp != NULL) fclose(fp);
	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	if (row != NULL) free(row);

	return code;
}
