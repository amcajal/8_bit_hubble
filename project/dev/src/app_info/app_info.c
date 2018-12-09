/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: app_info.c
*
*   Description: Source code for app_info module. It provides textual data
*               of the application, like HELP and VERSION messages, as well
*               as the functions to print them.
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

#define PROG_REPO "Project URL: https:\\\\github.com/amcajal/8_bit_hubble"

#define PROG_NAME "8-Bit Hubble"

#define PROG_VERSION "Version 1.0.0"

#define PROG_SUMM "Generate random pixel-art galaxy images!"

#define PROG_LICENSE PROG_NAME " Copyright (C) 2018 Alberto Martin Cajal\n\
This program comes with ABSOLUTELY NO WARRANTY;\n\
This is free software distributed under GNU GPL v3.0 License.\n\
For more details, visit https:\\\\www.gnu.org\\licenses\\gpl-3.0.en.html"

#define USAGE "Launch `8_bit_Hubble_cli.exe -h` or `8_bit_Hubble_cli.exe --help` for help"

#define HELP "8_bit_Hubble_cli.exe  GENERATION_OPT | HELP | VERSION\n\n\
generation_opt:\n\
    -o <output path> -n <file name> [-s <seed>]\n\
        -o, --output: Output path where generated image will be stored\n\
        -n, --name: Name of the image to be generated\n\
        -s, --seed: Seed (positive non-zero number) for the Random Number Generator\n\
    Example: 8_bit_Hubble_cli.exe -o /user/images/ -n my_image\n\
    Example: 8_bit_Hubble_cli.exe -o /user/images/ -n my_image -s 1664735\n\n\
help:\n\
    -h, --help: Print this message and exit\n\n\
version:\n\
    -v, --version: Print app information"
    
#define GUI_ABOUT PROG_NAME "\n" PROG_SUMM "\n" PROG_VERSION "\n" PROG_REPO "\n" PROG_LICENSE

/* OS specific GUI help. */
#if defined(_WIN32)

    #define GUI_HELP "To generate a galaxy, select:\n\
        - Name of the image to be generated\n\
        - Optional Seed (positive non-zero number) for the Random Number Generator\n\
    Example:\n\
		- Output image name: Maturin_Galaxy\n\
		- Seed (optional): 34567\n\
    And then, press the \"Generate Galaxy!\" button"
        
#elif defined(unix) || defined(__unix__) || defined(__unix)

    #define GUI_HELP "To generate a galaxy, select:\n\
        - Output path where generated image will be stored\n\
        - Name of the image to be generated\n\
        - Optional Seed (positive non-zero number) for the Random Number Generator\n\
    Example:\n\
		- Output path: /user/images/\n\
		- Output image name: galaxy_n42\n\
		- Seed (optional): 34567\n\
    And then, press the \"Generate Galaxy!\" button"
        
#endif /* OS specific GUI help. */

    
void print_usage(void)
{
    printf("\n%s\n", USAGE);
}

void print_help(void)
{
    printf("\n%s\n%s\n", HELP, PROG_REPO);
}

void print_version(void)
{
    printf("\n%s\n%s\n%s\n%s\n%s\n%s\n", 
            PROG_NAME, PROG_SUMM, PROG_VERSION, USAGE, PROG_REPO, PROG_LICENSE);
}

char *get_project_repo(void)
{
    return PROG_REPO;
}

char *get_project_copyright(void)
{
    return PROG_LICENSE;
}

char *get_gui_about(void)
{
	return GUI_ABOUT;
}

char *get_gui_help(void)
{
	return GUI_HELP;
}
