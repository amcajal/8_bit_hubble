#!/bin/bash
################################################################################
#   Project: 8-Bit Hubble.
#
#   File: path_finder.sh
#
#   Description: This script searches for "./" and "../" in all the files
#		under the <root_dir>. Its goal is to check all places where
#		references to relative paths are used.
#
#               Usage: $ path_finder.sh <root_dir>
#               <root_dir> root directory from where search process starts.
#
#   Notes: This script is named like one of the Mars Spacecrafts. It cannot be cooler.
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
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <root_dir>"
  exit 1
fi

rm ./path_finder_results.txt
for file in $(find $1); do 
    result=$(cat $file | grep -i -e "\./") 
    if [ $? -eq 0 ]; then 
        echo "$file \n ========== \n $result \n\n" >> ./path_finder_results.txt 
    fi
done