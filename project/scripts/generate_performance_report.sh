#!/bin/bash
################################################################################
#   Project: 8-Bit Hubble.
#
#   File: generate_performance_report.sh
#
#   Description: Script to generate GPROF reports from 8-Bit Hubble
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
	echo "	PERFORMANCE REPORTS OF 8-BIT HUBBLE SUCCESSFULLY GENERATED"
	echo "##############################"
}

################################################################################

CURRENT_DIR=$(pwd)

cd ../dev/integration

################################################################################
# Remove previous png images and gmon.out files, if any
################################################################################
rm *.out
rm *.png
rm *.stats

################################################################################
# First iteration outside the loop, in order to create the gmon.sum file
################################################################################
print_info_message "Generating first GPROF report..."

./8bh_cli_pfm.exe -o ./ -n name -s 1984 # Why 1984? Because Orwell
if [ $? -ne 0 ]; then
	print_error_message "./8bh_cli_pfm.exe -o ./ -n name -s 1984"
	exit 1
fi

cp gmon.out gmon_iter0.out
mv gmon.out gmon.sum

################################################################################
# Perform required iterations, merging the gmon.out files in each one
################################################################################
print_info_message "Running and merging additional GPROF reports..."

iterations=9
for i in `seq 1 $iterations`
do
	./8bh_cli_pfm.exe -o ./ -n name -s 1984
	cp gmon.out gmon_iter$i.out
	gprof -s 8bh_cli_pfm.exe gmon.out gmon.sum
done;

################################################################################
# Generate final gprof report and move files to proper directory
################################################################################
print_info_message "Generating total GPROF report..."

gprof -C -i -q --function-ordering 8bh_cli_pfm.exe gmon.sum > 8bh_cli_pfm.stats

if [ $? -ne 0 ]; then
	print_error_message "gprof -C -i -q --function-ordering 8bh_cli_pfm.exe gmon.sum > 8bh_cli_pfm.stats"
	exit 1
fi

mv *.out *.sum *.stats ../test/performance/

################################################################################
print_success_message
