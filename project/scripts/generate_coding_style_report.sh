#!/bin/bash
################################################################################
#   Project: 8-Bit Hubble.
#
#   File: generate_coding_style_report.sh
#
#   Description: Generate coding style reports using the following tools:
#	- CPPCheck
#	- Flawfinder
#
#	The tools are only applied to the source files of the source directory.
#	Source files of test directory are considered under a different coding
#	standard, and thus, this analysis is not performed on them.
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
################################################################################

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
	echo "	CODING STYLE REPORTS SUCCESSFULLY GENERATED"
	echo "##############################"
}

################################################################################

CURRENT_DIR=$(pwd)
STYLE_DIR=../dev/test/style
SOURCE_DIR=../dev/src
REPORT_FILE_NAME=coding_style_report_results.txt


################################################################################
# Delete previous results
################################################################################
print_info_message "Deleting previous results..."

rm $STYLE_DIR/$REPORT_FILE_NAME
touch $STYLE_DIR/$REPORT_FILE_NAME


################################################################################
# Run Flawfinder
################################################################################
print_info_message "Running flawfinder..."

echo "\n---------- FLAWFINDER RESULTS ----------\n" >> $STYLE_DIR/$REPORT_FILE_NAME
flawfinder --columns --context --error-level=4 $SOURCE_DIR >> $STYLE_DIR/$REPORT_FILE_NAME 2>&1

# Flawfinder returns '0' if no hits are found, and '1' otherwise. A '0' will be returned even if
# an incorrect directory is provided. Thus, there is no simple way to check if the execution of
# flawfinder really fails. 

################################################################################
# Run CppCheck
################################################################################
print_info_message "Running cppcheck..."

echo "\n\n---------- CPPCHECK RESULTS ----------\n" >> $STYLE_DIR/$REPORT_FILE_NAME
for file in $(find $SOURCE_DIR -regex ".*\.[h,c]$"); do
	cppcheck -x c --enable=all --std=posix $file >> $STYLE_DIR/$REPORT_FILE_NAME 2>&1

	if [ $? -ne 0 ]; then
		print_error_message "cppcheck -x c --enable=all --std=posix $file >> $STYLE_DIR/$REPORT_FILE_NAME 2>&1"
		exit 1
	fi
done

################################################################################
print_success_message
