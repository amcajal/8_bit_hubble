/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: big_bang_core.c
*
*   Description: Source code for big_bang_core module. This module represents
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

#ifdef GUI_MODE
    #define PRINT_MESSAGE(x) asm("nop")
#else
    #define PRINT_MESSAGE(x) printf("%s", x)
#endif

#include <stdio.h>
#include "../status_reporter/status_reporter.h"
#include "../user_config_checker/user_config_checker.h"
#include "../image_writer/image_writer.h"
#include "../rng/rng.h"
#include "../canvas/canvas.h"
#include "../galaxy_generator/galaxy_generator.h"
#include "../app_info/app_info.h"

/* This function uses goto statements. Even when they are considered
a bad practice, the flow of the entry point is small and simple enough
to not cause problems. In this particular case, goto statements reduce the code
lenght and make it more readable.*/

int start_big_bang (void)
{   
    enum status stat = NO_ERROR;
	
    PRINT_MESSAGE("Checking user configuration...\n");
    stat = check_user_configuration();
    if (stat != NO_ERROR)
    {
        PRINT_MESSAGE(report_status(stat));
        goto release_user_config;
    }
    
    /* Initialize Random Number Generator. */
    load_seed(get_valid_seed());
    
    struct canvas galaxy_canvas;
    
    PRINT_MESSAGE("Start generation of galaxy...\n");
    stat = generate_galaxy(&galaxy_canvas);
    if (stat != NO_ERROR)
    {
        PRINT_MESSAGE(report_status(stat));
        goto release_canvas;
    }
    
    PRINT_MESSAGE("Saving galaxy...\n");
    stat = write_image(&galaxy_canvas, get_valid_output_path(), 
		get_valid_image_name());
        
    if (stat != NO_ERROR)
    {
        PRINT_MESSAGE(report_status(stat));
        goto release_canvas;
    }    

    PRINT_MESSAGE("Galaxy created successfully.\n");
    
    release_canvas:
        delete_canvas(&galaxy_canvas);
        
    release_user_config:
        delete_user_configuration();
	
    return stat;
}
