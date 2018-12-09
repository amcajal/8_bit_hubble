/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: status_reporter.c
*
*   Description: Source file of Status_reporter module. Status reporter
* 				module is the "Error handler" module of the application.
* 				It defines all possible error codes, used to check
* 				if operations are being executed as expected. It
* 				provides a feedback or "debug" functionality too,
* 				to warn about encountered problems.
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
#include "./status_reporter.h"

char* report_status(enum status stat)
{
    char *status_message;
    
    switch(stat)
    {
        case OUTPUT_PATH_DOES_NOT_EXIST:
            status_message = "Output path does not exist.";
            break;
        case OUTPUT_PATH_NO_WRITE_PERM:
            status_message = "Output path does not have write permissions.";
            break;
        case IMAGE_NAME_INVALID_LENGTH:
            status_message = "Image name length shall be 1 to 20 characters.";
            break;
        case IMAGE_NAME_INVALID_CHARS:
            status_message = "Image name shall contain only digits, letters and underscores. Do not put file extension.";
            break;
        case SEED_INVALID_VALUE:
            /* The upper limit is just an indication, because LONG_MAX value is machine dependant. */
            status_message = "Invalid seed value. It shall be a positive non-zero value. Avoid seeds bigger than 2147483647.";
            break;
        case CANNOT_RESERVE_MEM:
            status_message = "Application failed to store memory for image generation.";
            break;
        case CANNOT_WRITE_IMAGE:
            status_message = "Application failed to write image data into output file.";
            break;
        case PALETTE_NOT_INITIALIZED:
            status_message = "Application failed to initialize the palette of colors.";
            break;
        case INVALID_PALETTE:
            status_message = "Application loaded and invalid palette.";
            break;
        case OUTPUT_PATH_MISSING:
            status_message = "Output path is mandatory. Please provide one.";
            break;
        case IMAGE_NAME_MISSING:
            status_message = "File name is mandatory. Please provide one.";
            break;
        case UNKNOWN_ERROR:
            status_message = "Application ended due to an unexpected error.";
            break;
        default:
			status_message = "All Ok!\n";
            break;
    }
    return status_message;
}
