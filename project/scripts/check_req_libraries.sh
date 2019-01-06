#!/bin/bash
################################################################################
#   Project: 8-Bit Hubble.
#
#   File: check_req_libraries.sh
#
#   Description: Script to check if required libraries to build
#				8-Bit Hubble are available in the system.
#				A library is available if it can be found in the sytem,
#				and its version is the proper one.
#
#   Notes: N/A
#
#   Contact: Alberto Martin Cajal, amartin.glimpse23<AT>gmail.com
#
#   URL: https://github.com/amcajal/8_bit_hubble
#
#   License: GNU GPL v3.0
#
#   Copyright (C) 2018 Alberto Martin Cajal
#
#   This file is part of 8-Bit Hubble.
#
#   8-Bit Hubble is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   8-Bit Hubble is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#################################################################################

print_info_message()
{
	echo "##############################"
	echo "	$1"
	echo "##############################"
}

print_error_message()
{
	echo "##############################"
	echo "	A COMMAND HAS FAILED --->"
	echo "			$1"
	echo "##############################"
}


print_success_message()
{
	echo "##############################"
	echo "	ALL REQUIRED LIBRARIES ARE AVAILABLE"
	echo "##############################"
}

################################################################################
# CHECK FOR REQUIRED LIBRARIES
################################################################################
# Initially, no errors are found.
error=0

print_info_message "Checking for required libraries..."

# LIBPNG
print_info_message "Checking for libPNG version 1.2.50 ..."
ldconfig -p | grep libpng12
if [ $? -ne 0 ]; then
    print_error_message "ldconfig -p | grep libpng12"
    echo "libPNG v1.2.50 not found in the system."
    echo "libPNG v1.2.50 is required in order to build all versions of 8-bit Hubble."
    error=1
fi

# LIBGTK
print_info_message "Checking for GTK version 3..."
ldconfig -p | grep libgtk-3
if [ $? -ne 0 ]; then
    print_error_message "ldconfig -p | grep libgtk-3"
    echo "GTK v3 not found in the system."
    echo "GTK v3 is required in order to build GUI versions of 8-bit Hubble."
    error=1
fi



if [ $error -ne 0 ]; then
    print_info_message "ONE OR MORE REQUIRED LIBRARIES COULD NOT BE FOUND.\n \
						8-Bit Hubble cannot be build."
    exit 1
fi
#################################################################################

print_success_message
