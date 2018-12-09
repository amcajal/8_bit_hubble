#!/bin/bash
################################################################################
#   Project: 8-Bit Hubble.
#
#   File: CI.sh
#
#   Description: Continuous Integration (CI) shell script. It reproduces
#                the operations performed by tools like Travis CI and described
#                in the Yaml files, but in shell script format, so it can be
#                executed in the local computer and manually by the user.
#                The script is divided in "phases", and if any of them fails,
#                the error is printed for further analysis, and then the script
#                exits. 
#
#   Notes: This script must be executed at <project_root>/project/def/sw/scripts
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
	echo "	CONTINUOUS INTEGRATION OF 8-BIT HUBBLE FINISHED SUCCESSFULLY"
	echo "##############################"
}


################################################################################

print_info_message "CONTINUOUS INTEGRATION OF 8-BIT HUBBLE IN PROCESS..."

# Integration directory, where Makefile is located
INT_DIR="../dev/integration/"

# Testing directory, where all test code and other executables are located
TEST_DIR="../dev/test"

# To keep track of scripts directory
SCRIPTS_DIR=$(pwd)

################################################################################
# 			BUILDING ALL VERSIONS
################################################################################

print_info_message "Cleaning Integration directory..."
make clean -C $INT_DIR

print_info_message "Building 8-Bit Hubble RELEASE versions..."
make all -C $INT_DIR
if [ $? -ne 0 ]; then
	print_error_message "make all -C $INT_DIR"
	exit 1
fi


print_info_message "Building 8-Bit Hubble PERFORMANCE versions..."
make del_obj -C $INT_DIR
make all EXEC_TYPE=performance -C $INT_DIR
if [ $? -ne 0 ]; then
	print_error_message "make all EXEC_TYPE=performance -C $INT_DIR"
	exit 1
fi 


# Coverage executable is generated last to keep its object files. Otherwise,
# when generating coverage reports, several errors would arise due to incorrect
# .o files being used as data.
print_info_message "Building 8-Bit Hubble COVERAGE versions..."
make del_obj -C $INT_DIR
make all EXEC_TYPE=coverage -C $INT_DIR
if [ $? -ne 0 ]; then
	print_error_message "make all EXEC_TYPE=coverage -C $INT_DIR"
	exit 1
fi


################################################################################
# 			RUN FUNCTIONAL TESTS AND COVERAGE TESTS
#
#			Functional tests are executed using the coverage
#			executable, so both phases are performed at once	
################################################################################

print_info_message "Building 8-Bit Hubble CLI version tests..."
make test EXEC_TYPE=test_cov -C $INT_DIR
if [ $? -ne 0 ]; then
	print_error_message "make test EXEC_TYPE=test_cov -C $INT_DIR"
	exit 1
fi


print_info_message "Running 8-Bit Hubble CLI version High Level Tests..."
cd $TEST_DIR/high_level_test
python python_uat.py
if [ $? -ne 0 ]; then
	print_error_message "python python_uat.py"
	exit 1
fi
cd ../ # Back to $TEST_DIR


print_info_message "Running 8-Bit Hubble CLI version Low Level Tests..."
cd low_level_test/

# This executable name shall concur with the one in the Makefile of the project
# located at <project_root>/project/dev/integration"
rm ./8bh_cli_test.exe # In case there is a previous version
mv ../../integration/8bh_cli_test.exe ./ # This is done just for convenience.
./8bh_cli_test.exe
if [ $? -ne 0 ]; then
	print_error_message "./8bh_cli_test.exe"
	exit 1
fi


# Batch file are used to force errors in the application.
# With the logging capability active in each batch, the output is
# saved in "gdb.txt" file. If all batchs works properly, the string
# "exited normally]" shall not be found in gdb.txt, meaning the
# application does not end normally when an error takes place.
rm gdb.txt
for gdb_batch in $(ls ./gdb_batch_8bH*); 
do 
	print_info_message "Running Low level test with GDB: now launching $gdb_batch" 
	gdb -x $gdb_batch
	if [ $? -ne 0 ]; then
		print_error_message "gdb -x $gdb_batch"
		exit 1
	fi	
done;

# The string shall NOT appear
grep "exited normally]" gdb.txt
if [ $? -ne 1 ]; then
	print_error_message "grep \"exited normally]\" gdb.txt"
	exit 1
fi

print_info_message "Extracting coverage information..."
cd $SCRIPTS_DIR
sh generate_coverage_report.sh
if [ $? -ne 0 ]; then
	print_error_message "sh generate_coverage_report.sh"
	exit 1
fi

################################################################################
# 			RUN PERFORMANCE TESTS
################################################################################
print_info_message "Running 8-Bit Hubble CLI version Performance tests..."
sh generate_performance_report.sh
if [ $? -ne 0 ]; then
	print_error_message "sh generate_performance_report.sh"
	exit 1
fi

################################################################################
# 			RUN COVERAGE TESTS
################################################################################
# Already done

################################################################################
# 			RUN STYLE TESTS
################################################################################
print_info_message "Running 8-Bit Hubble CLI version Coding Style tests (it can take a while)..."
sh generate_coding_style_report.sh
if [ $? -ne 0 ]; then
	print_error_message "sh generate_coding_style_report.sh"
	exit 1
fi

################################################################################
print_success_message
