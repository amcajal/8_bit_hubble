/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: cli.c
*
*   Description: Source file of CLI module. CLI module (Command Line
* 				Interface) implements the ENTRY POINT of the application
* 				in its CLI version. It parses the input arguments
* 				provided by the user, and performs the required
* 				operations (i.e: print version, help message, generate
* 				image, or print error message).
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
#include <getopt.h>
#include <stdlib.h>
#include "../big_bang_core/big_bang_core.h"
#include "../user_config_checker/user_config_checker.h"
#include "../app_info/app_info.h"

int main (int argc, char **argv)
{
    if (argc == 1) {
        print_usage();
        return 1;
    }
    
    int parsed_options;

    while(1)
    {
        static struct option long_options[] =
        {
            {"output", required_argument, 0, 'o'},
            {"name", required_argument, 0, 'n'},
            {"seed", required_argument, 0, 's'},
            {"help", no_argument, 0, 'h'},
            {"version", no_argument, 0, 'v'},
            {0, 0, 0}
        };

        int option_index = 0;

        parsed_options = getopt_long (argc, argv, "o:n:s:hv", 
                long_options, &option_index);

        if (parsed_options == -1)
            break;

        switch (parsed_options)
        {
            case 'o':
                store_output_path(optarg);
                break;

            case 'n':
                store_file_name(optarg);
                break;

            case 's':
                store_seed(optarg);
                break;

            case 'h':
                print_help();
                return 0;

            case 'v':
                print_version();
                return 0;

            default:
                abort();
        }
    }
    return start_big_bang();
}
