/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: user_config_checker.h
*
*   Description: Header file of User_config_checker module. As it name
* 				implies, the module checks that the configuration
* 				provided by the user to generate the galaxy is correct
* 				in terms of: valid image name, valid output directory,
* 				valid seed (if provided), etc.
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
#ifndef _8BH_USER_CONFIG_CHECKER_H
#define _8BH_USER_CONFIG_CHECKER_H

#include "../status_reporter/status_reporter.h"

void store_output_path(char *output_path); 
void store_file_name(char *file_name);
void store_seed(char *seed);
enum status check_user_configuration(void);
void delete_user_configuration(void);
char *get_valid_image_name(void);
char *get_valid_output_path(void);
int get_valid_seed(void);
char *get_valid_image_abs_path(void);

#endif
