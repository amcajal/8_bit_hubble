#!/bin/bash
################################################################################
#   Project: 8-Bit Hubble.
#
#   File: setup.sh
#
#   Description: Setup script for 8-bit Hubble project. The scripts performs
#       the following operations:
#           - Check if required libraries are installed
#           - Check if required software is installed
#           - Attempts to execute the Continuous Integration (CI) script to
#           perform a complete build of the project.
#
#       To some extent, this script performs the operations that will be carried
#       out by the GNU Build System. However, due to the scope of the project,
#       it is considered cleaner and easier to use these "hard-coded" scripts.
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
	echo "	8-bit Hubble build process is complete! Enjoy!"
	echo "##############################"
}

################################################################################
print_info_message "8-bit Hubble SETUP script"

CURRENT_DIR=$(pwd)
SCRIPTS_DIR="./project/scripts"
LOG_ABSPATH=$(pwd)/setup_log.txt
rm setup_log.txt

cd $SCRIPTS_DIR

#CHECK FOR REQUIRED LIBRARIES
sh check_req_libraries.sh 2>&1 | tee -ai $LOG_ABSPATH

#CHECK FOR REQUIRED SOFTWARE
sh check_req_software.sh 2>&1 | tee -ai $LOG_ABSPATH

################################################################################
# ATTEMPT CONTINUOUS INTEGRATION (CI) EXECUTION
################################################################################
print_info_message "Running Continuous Integration (CI) script of 8-bit Hubble..."

sh CI.sh 2>&1 | tee -ai $LOG_ABSPATH

if [ $? -ne 0 ]; then
    print_error_message "sh $SCRIPTS_DIR/CI.sh"
    exit 1
fi

################################################################################
print_success_message
exit 0
