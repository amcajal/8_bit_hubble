#!/bin/bash
################################################################################
#   Project: 8-Bit Hubble.
#
#   File: c_header_comment_adder.sh
#
#   Description: This script concatenates at the beginning of C source files 
#                (.c and .h) found under <source_root_dir> (iterated recursively) 
#                the header comment text found in <template_file>.
#
#                Parameters:
#                   $1: <source_root_dir> root directory containing the source files (absoulte path)
#                   $2: <template_file> text file containing the header comment boilerplate (absolute path)
#
#                Usage: <script_name> <source_root_dir> <template_file>
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

if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <source_root_dir> <template_file.txt>"
  exit 1
fi
for file in $(find $1 -regex ".*\.\(c\|h\)"); do $(cat $2 | cat - $file > temp && mv temp $file); done
