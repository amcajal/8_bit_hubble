################################################################################
#   Project: 8-Bit Hubble.
#
#   File: include_header_searcher.py
#
#   Description: Standalone python script. It iterates over the source directory
#	and, for each C source file, checks for #include directives. Then, saves
#	the results in the "include_header_searcher_results.txt" file. This script
#	aims to aid in the generation of the Makefile (with the results file,
#	is more easy to establish the recipes for each object file).
#
#	Usage: $ python include_header_searcher.py <path_to_source_dir>
#		where <path_to_source_dir> is a relative path to the directory
#		containing the source files (i.e: ../dev/src)
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

import os
import sys

if len(sys.argv) == 1:
	print "Usage: $ python include_header_searcher.py <path_to_source_dir>\n"
	exit(1)

if not os.path.isdir(sys.argv[1]):
	print "Path provided does not exist\n"
	exit(1)

src_dir = sys.argv[1]
results_file = "./include_header_searcher_results.txt"
results_file_content = ""

for path, dirname, filename in os.walk(src_dir):
	for name in filename:
		if name.endswith(".c"):
			results_file_content += "\n" + name + ":\n"
			file_reader = open(path + "/" + name, "r")
			file_content = file_reader.read().split("\n")
			for line in file_content:
				if "#include \"" in line:
					results_file_content += "\t" + line + "\n"
			file_reader.close()

file_writer = open(results_file, "w")
file_writer.write(results_file_content)
file_writer.close()