/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: app_info.h
*
*   Description: Header file for app_info module. It provides textual data
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

#ifndef _8BH_APP_INFO_H
#define _8BH_APP_INFO_H

void print_usage(void);
void print_help(void);
void print_version(void);
char *get_project_repo(void);
char *get_project_copyright(void);
char *get_gui_about(void);
char *get_gui_help(void);

#endif
