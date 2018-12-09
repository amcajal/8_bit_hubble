/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: user_config_checker.c
*
*   Description: Source file of User_config_checker module. As it name
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
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "../status_reporter/status_reporter.h"

#define HAS_CLOSING_SLASH(x) x[strlen(x) - 1] == '/'

struct user_configuration_copy {
	char *image_name;
	char *output_path;
	int seed;
    int custom_seed_flag;
} user_config = {
		NULL, 
		NULL, 
		-1, /* Default value.*/
        0 /* By default, no custom seed is stored. */
};

void replace_backslash_with_slash(char * path)
{
    char *string_index = path;
    while (*string_index != '\0')
    {
        if ((*string_index) == '\\')
        {
            (*string_index) = '/';
        }
        string_index++;
    }
}

int does_path_exist(char *path)
{
    if (access(path, F_OK) == 0)
        return 0;
    else
        return 1;
}

int has_path_write_perm(char *path)
{
    if(access(path, W_OK) == 0) 
    {
        return 0;
    } 
    else 
    {
        return 1;   
    }
}

int is_file_name_length_correct(char *file_name)
{
    int length = strlen(file_name);
    if ((length >= 1) && (length <= 20))
        return 0;
    else
        return 1;
}

int are_all_chars_allowed(char *file_name)
{
    int result = 0;
	char *char_index = file_name;
	while (*char_index != '\0') {
		if (!isalnum(*char_index) && (*char_index != 95))
		{
			result = 1;
			break;
		}
		char_index++;
	}
	return result;
}

int is_seed_valid(int seed)
{
    if (seed <= 0)
        return 1;
    else
        return 0;
}


void store_output_path(char *output_path)
{
	int add = 1; /* At least, add the \0 char. */
	
	int r = HAS_CLOSING_SLASH(output_path);
	if (r == 0)
		add++;
		
	user_config.output_path = 
		malloc((strlen(output_path) + add) * sizeof(char));
	strcpy(user_config.output_path, output_path);
	
	if (r == 0)
		strcat(user_config.output_path, "/");
	
	replace_backslash_with_slash(user_config.output_path);
}
 
void store_file_name(char *file_name)
{
	user_config.image_name = malloc((strlen(file_name) + 1) * sizeof(char));
    strcpy(user_config.image_name, file_name);
}

void store_seed(char *seed)
{
    /* Either if the seed is valid or not, value -1 is overrided. */
	user_config.seed = atoi(seed); 
    user_config.custom_seed_flag = 1;
}

enum status check_user_configuration(void)
{
	/* Check output directory has been provided. */
	if (!user_config.output_path)
		return OUTPUT_PATH_MISSING;
		
	/* Check image name has been provided. */
	if (!user_config.image_name)
		return IMAGE_NAME_MISSING;
		
    /* Check output directoy is valid. */    
    if (does_path_exist(user_config.output_path) != 0)
        return OUTPUT_PATH_DOES_NOT_EXIST;
        
    if (has_path_write_perm(user_config.output_path) != 0)
        return OUTPUT_PATH_NO_WRITE_PERM;
    
    /* Check file name is valid */    
    if (is_file_name_length_correct(user_config.image_name) != 0)
        return IMAGE_NAME_INVALID_LENGTH;
        
    if (are_all_chars_allowed(user_config.image_name) != 0)
        return IMAGE_NAME_INVALID_CHARS;
    
    /* Check seed is valid */
    if (user_config.custom_seed_flag == 1)
        if (is_seed_valid(user_config.seed) != 0)
            return SEED_INVALID_VALUE;
    
    return NO_ERROR;
}

void delete_user_configuration(void)
{
	if (user_config.output_path != NULL) {
        free(user_config.output_path);
        user_config.output_path = NULL;
    }
		
		
	if (user_config.image_name != NULL) {
        free(user_config.image_name);
        user_config.image_name = NULL;
    }
		
    user_config.custom_seed_flag = 0;
	user_config.seed = -1;
}

char *get_valid_image_name(void)
{
	return user_config.image_name;
}

char *get_valid_output_path(void)
{
	return user_config.output_path;
}

int get_valid_seed(void)
{
	return user_config.seed;
}
