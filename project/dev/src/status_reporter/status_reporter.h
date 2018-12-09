/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: status_reporter.h
*
*   Description: Header file of Status_reporter module. Status reporter
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
#ifndef _8BH_STATUS_REPORTER_H
#define _8BH_STATUS_REPORTER_H

/* This enumeration contains all possible error codes of the application. 
    Each module increases the error ID by 1000 units, to give plenty of room
    to future errors in the same module to appear.
*/
enum status {
    /* All modules. */
        NO_ERROR = 0,
        UNKNOWN_ERROR = 1,
    
    /* user_config_checker module. */
        OUTPUT_PATH_MISSING = 1000,
        IMAGE_NAME_MISSING = 1001,
        OUTPUT_PATH_DOES_NOT_EXIST = 1002,
        OUTPUT_PATH_NO_WRITE_PERM = 1003,
        IMAGE_NAME_INVALID_LENGTH = 1004,
        IMAGE_NAME_INVALID_CHARS = 1005,
        SEED_INVALID_VALUE = 1006,
    
    /* galaxy_generator module. */
        CANNOT_RESERVE_MEM = 2000,
    
    /* image_writer module. */
        CANNOT_WRITE_IMAGE = 3000,
    
    /* palette module. */
        PALETTE_NOT_INITIALIZED = 4000,
        INVALID_PALETTE = 4001
};
    
char* report_status(enum status stat); 
#endif
