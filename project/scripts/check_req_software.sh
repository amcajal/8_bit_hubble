#!/bin/bash
################################################################################
#   Project: 8-Bit Hubble.
#
#   File: check_req_software.sh
#
#   Description: Script to check if the required applications, tools,
#				utilities, software, etc, to build 8-Bit Hubble are
#				available in the system.
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
	echo "\n\n##############################"
	echo "	$1"
	echo "##############################\n\n"
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
	echo "	ALL REQUIRED SOFTWARE IS AVAILABLE"
	echo "##############################"
}

################################################################################
# CHECK FOR REQUIRED SOFTWARE
################################################################################

# Initially, no errors are found.
error=0

print_info_message "Checking for required software..."

#GNU Make
make --version
if [ $? -ne 0 ]; then
    print_error_message "make --version"
    echo "GNU Make is required to perform a complete build of 8-bit Hubble."
    error=1
fi

#GNU GCC
gcc --version
if [ $? -ne 0 ]; then
    print_error_message "gcc --version"
    echo "GNU GCC is required to perform a complete build of 8-bit Hubble"
    error=1
fi

#GNU GDB
gdb --version
if [ $? -ne 0 ]; then
    print_error_message "gdb --version"
    echo "GNU GDB is required to perform a complete build of 8-bit Hubble"
    error=1
fi

#GNU GPROF
gprof --version
if [ $? -ne 0 ]; then
    print_error_message "gprof --version"
    echo "GNU Gprof is required to perform a complete build of 8-bit Hubble"
    error=1
fi

#GNU GCOV
gcov --version
if [ $? -ne 0 ]; then
    print_error_message "gcov --version"
    echo "GNU Gcov is required to perform a complete build of 8-bit Hubble"
    error=1
fi

#Pkg-config
pkg-config --version
if [ $? -ne 0 ]; then
    print_error_message "pkg-config --version"
    echo "pkg-config is required to perform a complete build of 8-bit Hubble"
    error=1
fi

#LCOV
lcov --version
if [ $? -ne 0 ]; then
    print_error_message "lcov --version"
    echo "LCOV is required to perform a complete build of 8-bit Hubble"
    error=1
fi

#Flawfinder
flawfinder --version
if [ $? -ne 0 ]; then
    print_error_message "flawfinder --version"
    echo "Flawfinder is required to perform a complete build of 8-bit Hubble"
    error=1
fi

#Cppcheck
cppcheck --version
if [ $? -ne 0 ]; then
    print_error_message "cppcheck --version"
    echo "Cppcheck is required to perform a complete build of 8-bit Hubble"
    error=1
fi

#Python
python --version
if [ $? -ne 0 ]; then
    print_error_message "python --version"
    echo "Python 2.7 is required to perform a complete build of 8-bit Hubble"
    error=1
fi



if [ $error -ne 0 ]; then
    print_info_message "ONE OR MORE REQUIRED TOOLS COULD NOT BE FOUND.\n \
						8-Bit Hubble cannot be build."
    exit 1
fi
#################################################################################

print_success_message
