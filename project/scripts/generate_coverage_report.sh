#!/bin/bash
################################################################################
#   Project: 8-Bit Hubble.
#
#   File: generate_coverage_report.sh
#
#   Description: Script to generate coverage reports from 8-Bit Hubble
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
	echo "	COVERAGE REPORTS OF 8-BIT HUBBLE SUCCESSFULLY GENERATED"
	echo "##############################"
}

################################################################################

cd ../dev/test/coverage

################################################################################
# 			DELETE PREVIOUS GCOV AND LCOV FILES
################################################################################
print_info_message "Deleting previous gcov and lcov files..."

rm ./*.gcda
rm ./*.gcno
rm ./*.gcov
rm ./*.info
rm -r ./lcov_htlm_results # This is the folder where the LCOV html is stored

################################################################################
# 			GENERATE GCOV AND LCOV RESULTS
################################################################################
cd ../../integration/

print_info_message "Generating gcov and lcov results..."

gcov *.o
if [ $? -ne 0 ]; then
	print_error_message "gcov *.o"
	exit 1
fi

lcov -c -t "8bH_cli_coverage" -o 8bH_cli_coverage.info -d ./
if [ $? -ne 0 ]; then
	print_error_message "lcov -c -t \"8bH_cli_coverage\" -o 8bH_cli_coverage.info -d ./"
	exit 1
fi

cd ../test/coverage

################################################################################
# 			RETRIEVE GCOV FILES
################################################################################
print_info_message "Retrieving gcov files..."

mv ../../integration/*.gcda ./
mv ../../integration/*.gcno ./
mv ../../integration/*.gcov ./
mv ../../integration/*.info ./

################################################################################
# 			GENERATE LCOV REPORTS
################################################################################
print_info_message "Generating lcov reports..."

genhtml -o ./lcov_htlm_results *.info
if [ $? -ne 0 ]; then
	print_error_message "genhtml -o ./lcov_htlm_results *.info"
fi

################################################################################
print_success_message
