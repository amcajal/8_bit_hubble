################################################################################
#   Project: 8-Bit Hubble.
#
#   File: Makefile
#
#   Description: Makefile of 8-Bit Hubble. This Makefile builds both CLI and GUI
#       versions of 8-Bit Hubble application, in all of its three types,
#       as well as the low level test for the CLI version (that comprises
#       in itself both the verification of functionality and coverage).
#       The following diagram shows the possible combinations:
#       
#       \ Type | Release  | Coverage            | Performance
#    Ver \     |          |                     |
#    ____________________________________________________________________
#
#    CLI       | make all | EXEC_TYPE=coverage  | EXEC_TYPE=performance 
#    ____________________________________________________________________
#
#    GUI       | make all | EXEC_TYPE=coverage  | EXEC_TYPE=performance 
#    ____________________________________________________________________
#
#    TEST_CLI  | make test| EXEC_TYPE=test_cov  | N/A
#    ____________________________________________________________________
#
#       "Coverage" executables adds gcov statements to the code, and its
#       intended to be used during testing phase to obtain coverage
#       information (statements and functions executed), not as release.
#       "Performance" executable adds gprof statements to the code, and
#       its intended to be used during testing phase to obtain time
#       measurements (execution time of functions), not as release.
#
#       This makefile also includes a conditional part to build Windows
#       executables, activated when TARGET=windows is passed as parameter.
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

# Compiler selection
COMPILER=gcc

# Compiler options selection
WARNING_OPTS=-Wall
DEBUG_OPTS=-g
OPTIMIZATION_OPTS=-O0 

ifeq ($(EXEC_TYPE),coverage)
	INSTRUMENTATION_OPTS=-coverage
	CLI_EXEC_NAME=8bh_cli_cov.exe
	GUI_EXEC_NAME=8bh_gui_cov.exe

# Notice this branch is for the low level test
else ifeq ($(EXEC_TYPE),test_cov) 
	INSTRUMENTATION_OPTS=-coverage
	CLI_TEST_EXEC_NAME=8bh_cli_test.exe

else ifeq ($(EXEC_TYPE),performance)
	INSTRUMENTATION_OPTS=-pg
	CLI_EXEC_NAME=8bh_cli_pfm.exe
	GUI_EXEC_NAME=8bh_gui_pfm.exe

else
	INSTRUMENTATION_OPTS=
	CLI_EXEC_NAME=8_bit_Hubble_cli.exe
	GUI_EXEC_NAME=8_bit_Hubble_gui.exe
endif

# All options in a single variable to handle it easily
ALL_OPTS=$(WARNING_OPTS) $(DEBUG_OPTS) $(OPTIMIZATION_OPTS) $(INSTRUMENTATION_OPTS)

# Compiler commands
COMPILE=-c
LINK=-o

# $(RENAME) var has the same value than $(LINK) var, but it is used 
# to change the ".o" name, not to link anything. So it is included 
# to make its purpose obvious
RENAME=-o

# Source directory where all source code is located
SRC=../src
# GUI source code for GNU/LINUX builds is used by default
GUI_CODE=$(SRC)/gui/gui.c

# Directory where low level test code is located
TEST_SRC=../test/low_level_test

# Header files and libraries required to build the software
LIBPNG_H=-I/usr/include/libpng
LIBGTK_H=`pkg-config --cflags gtk+-3.0`

LIBPNG_L=-lpng
LIBGTK_L=`pkg-config --libs gtk+-3.0`
LIBM=-lm

# Macros to control the behaviour of the software to build
CLI_MODE=-DCLI_MODE
GUI_MODE=-DGUI_MODE

# List of object files to link together in the final executable
CLI_OBJ=./status_reporter.o ./canvas.o ./palette.o ./rng.o ./sprites.o ./app_info.o ./user_config_checker.o ./galaxy_generator.o ./image_writer.o ./cli_core.o
GUI_OBJ=./status_reporter.o ./canvas.o ./palette.o ./rng.o ./sprites.o ./app_info.o ./user_config_checker.o ./galaxy_generator.o ./image_writer.o ./gui_core.o
CLI_TEST_OBJ=./palette_tests.o ./rng_tests.o ./sprites_tests.o
# Entry points (source code with function "main") are set aside, so list of object files can be reused in several builds
CLI_OBJ_ENTRY_POINT=./cli.o
GUI_OBJ_ENTRY_POINT=./gui.o
CLI_TEST_ENTRY_POINT=./8bH_test.o

################################################################################
# CONDITIONAL PART TO BUILD WINDOWS EXECUTABLES
# Key aspect is the STATIC_GTK variable. It is considered that Windows
# users wont have installed GTK or libpng. Thus, the executables shall contain
# all required libraries in static format. To do so, links to headers and libs
# shall be provided manually. A tested way to do this (there may be more) is:
# - Download GTK static development files: http://www.tarnyko.net/repo/gtk342_static-WIN32_(TARNYKO).zip (credits to the author of the webpage)
# - Extract the contents of the zip in <path/in/windows>
# - Set STATIC_GTK to <path/in/windows>

ifeq ($(TARGET),windows)
    WINDOWS_COMPILER=C:/MinGW/bin/gcc
    STATIC_GTK=C:\Users\temp_libs\8_bit_bang\static_gtk\gtk342_static
    COMPILER=$(WINDOWS_COMPILER)
    
    ifeq ($(COMPILER),None)
        $(error WINDOWS_COMPILER -Path to Compiler for Windows- is not set. Modify Makefile.)
    endif
    
    ifeq ($(STATIC_GTK),None)
        $(error STATIC_GTK -Path to Static GTK library- is not set. Modify Makefile.)
    endif
    
    # Use GUI source code for Windows builds
    GUI_CODE=$(SRC)/gui/gui_windows.c
    
    LIBPNG_H=-I$(STATIC_GTK)\include\libpng15
    LIBGTK_H=-I$(STATIC_GTK)\include\libpng15 -I$(STATIC_GTK)\include\gtk-3.0 -I$(STATIC_GTK)\include\glib-2.0 -I$(STATIC_GTK)\lib\glib-2.0\include -I$(STATIC_GTK)\include\gdk-pixbuf-2.0 -I$(STATIC_GTK)\include\pango-1.0 -I$(STATIC_GTK)\include\cairo -I$(STATIC_GTK)\include\atk-1.0

    LIBPNG_L=-L$(STATIC_GTK)\lib -lpng15 -lz
    LIBGTK_L=-L$(STATIC_GTK)\lib -lgtk-3 -lgdk-3 -lgdk_pixbuf-2.0 -lgobject-2.0 -lglib-2.0 -lpango-1.0 -latk-1.0 -lcairo -lcairo-gobject -lpangocairo-1.0 -lintl -lgmodule-2.0 -lgio-2.0 -limm32 -luser32 -lgdi32 -luuid -lole32 -lpng15 -lgdiplus -lpangowin32-1.0 -lffi -lws2_32 -lwinmm -lglib-2.0 -lpixman-1 -lfreetype -lfontconfig -lpangoft2-1.0 -lmsimg32 -liconv -lshlwapi -lz -lgdi32 -ldnsapi -lusp10 -lfreetype -lexpat -lgcc -lkernel32 -lmsvcrt
endif

################################################################################
all : $(CLI_EXEC_NAME) $(GUI_EXEC_NAME)

test : $(CLI_TEST_EXEC_NAME)

$(CLI_EXEC_NAME): $(CLI_OBJ) $(CLI_OBJ_ENTRY_POINT)
	$(COMPILER) $(ALL_OPTS) $(LINK) $(CLI_EXEC_NAME) $(CLI_OBJ_ENTRY_POINT) $(CLI_OBJ) $(LIBM) $(LIBPNG_L)

$(GUI_EXEC_NAME): $(GUI_OBJ) $(GUI_OBJ_ENTRY_POINT)
	$(COMPILER) $(ALL_OPTS) $(LINK) $(GUI_EXEC_NAME) $(GUI_OBJ_ENTRY_POINT) $(GUI_OBJ) $(LIBM) $(LIBPNG_L) $(LIBGTK_L)

# Take into consideration that next rule will work ONLY
# if the last make command was "make all EXEC_TYPE=coverage"
# and it finished successfully
$(CLI_TEST_EXEC_NAME) : $(CLI_TEST_OBJ) $(CLI_TEST_ENTRY_POINT)
	$(COMPILER) $(ALL_OPTS) $(LINK) $(CLI_TEST_EXEC_NAME) $(CLI_TEST_ENTRY_POINT) $(CLI_OBJ) $(CLI_TEST_OBJ) $(LIBM) $(LIBPNG_L)

# The rename operation only makes sense when building executables for Windows, but it is included anyway
gui.o : $(GUI_CODE) $(SRC)/gui/8bH_logo.h $(SRC)/big_bang_core/big_bang_core.h $(SRC)/app_info/app_info.h
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(RENAME) gui.o $(LIBGTK_H) $(GUI_CODE)

cli.o : $(SRC)/cli/cli.c $(SRC)/big_bang_core/big_bang_core.h $(SRC)/app_info/app_info.h $(SRC)/user_config_checker/user_config_checker.h
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(SRC)/cli/cli.c 

cli_core.o : $(SRC)/big_bang_core/big_bang_core.c $(SRC)/status_reporter/status_reporter.h $(SRC)/user_config_checker/user_config_checker.h $(SRC)/image_writer/image_writer.h $(SRC)/canvas/canvas.h $(SRC)/rng/rng.h $(SRC)/galaxy_generator/galaxy_generator.h $(SRC)/app_info/app_info.h
	$(COMPILER) $(ALL_OPTS) $(CLI_MODE) $(RENAME) cli_core.o $(COMPILE) $(SRC)/big_bang_core/big_bang_core.c

gui_core.o : $(SRC)/big_bang_core/big_bang_core.c $(SRC)/status_reporter/status_reporter.h $(SRC)/user_config_checker/user_config_checker.h $(SRC)/image_writer/image_writer.h $(SRC)/canvas/canvas.h $(SRC)/rng/rng.h $(SRC)/galaxy_generator/galaxy_generator.h $(SRC)/app_info/app_info.h
	$(COMPILER) $(ALL_OPTS) $(GUI_MODE) $(RENAME) gui_core.o $(COMPILE) $(SRC)/big_bang_core/big_bang_core.c 

image_writer.o : $(SRC)/image_writer/image_writer.c $(SRC)/status_reporter/status_reporter.h $(SRC)/canvas/canvas.h $(SRC)/rng/rng.h $(SRC)/app_info/app_info.h
	$(COMPILER) $(ALL_OPTS) $(LIBPNG_H) $(COMPILE) $(SRC)/image_writer/image_writer.c  

galaxy_generator.o : $(SRC)/galaxy_generator/galaxy_generator.c $(SRC)/status_reporter/status_reporter.h $(SRC)/canvas/canvas.h $(SRC)/palette/palette.h $(SRC)/rng/rng.h $(SRC)/sprites/sprites.h $(SRC)/brush/brush.h
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(SRC)/galaxy_generator/galaxy_generator.c 

user_config_checker.o : $(SRC)/user_config_checker/user_config_checker.c $(SRC)/status_reporter/status_reporter.h
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(SRC)/user_config_checker/user_config_checker.c 

app_info.o : $(SRC)/app_info/app_info.c
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(SRC)/app_info/app_info.c 

sprites.o : $(SRC)/sprites/sprites.h $(SRC)/sprites/sprites.c $(SRC)/canvas/canvas.h $(SRC)/brush/brush.h
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(SRC)/sprites/sprites.c 

rng.o : $(SRC)/rng/rng.c
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(SRC)/rng/rng.c 

palette.o : $(SRC)/palette/palette.h $(SRC)/palette/palette.c $(SRC)/status_reporter/status_reporter.h $(SRC)/brush/brush.h
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(SRC)/palette/palette.c 

#brush module just contains a header file

canvas.o : $(SRC)/canvas/canvas.h $(SRC)/canvas/canvas.c
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(SRC)/canvas/canvas.c 

status_reporter.o : $(SRC)/status_reporter/status_reporter.h $(SRC)/status_reporter/status_reporter.c
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(SRC)/status_reporter/status_reporter.c   

### And now, the low level test objects

8bH_test.o : $(TEST_SRC)/8bH_test.c $(TEST_SRC)/palette_tests.h $(TEST_SRC)/rng_tests.h $(TEST_SRC)/sprites_tests.h
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(TEST_SRC)/8bH_test.c

palette_tests.o : $(TEST_SRC)/palette_tests.c $(SRC)/palette/palette.h $(SRC)/status_reporter/status_reporter.h $(SRC)/brush/brush.h
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(TEST_SRC)/palette_tests.c

rng_tests.o : $(TEST_SRC)/rng_tests.c $(SRC)/rng/rng.h
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(TEST_SRC)/rng_tests.c

sprites_tests.o : $(TEST_SRC)/sprites_tests.c $(SRC)/sprites/sprites.h $(SRC)/image_writer/image_writer.h $(SRC)/brush/brush.h $(SRC)/canvas/canvas.h $(SRC)/palette/palette.h $(SRC)/app_info/app_info.h $(SRC)/rng/rng.h
	$(COMPILER) $(ALL_OPTS) $(COMPILE) $(TEST_SRC)/sprites_tests.c


#################################################################################
.PHONY: clean
clean:
	rm -rf ./*.o ./*.png ./*.gcda ./*.gcno ./*.gcov ./gmon.out ./*.info ./*.exe 

# The only difference between "del_obj" and "clean" is that former deletes all BUT the executables in the directory
.PHONY: del_obj
del_obj:
	rm -rf ./*.o ./*.png ./*.gcda ./*.gcno ./*.gcov ./gmon.out ./*.info
