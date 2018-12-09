################################################################################
#   Project: 8-Bit Hubble.
#
#   File: 8bh_csv_to_sprite.py
#
#   Description: Turns a CSV representing an 8-Bit Hubble Sprite into text line 
#               representing a C language static array, in a suitable form 
#               to process it during the galaxy random image generation.
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

import sys

if len(sys.argv) != 2:
    print "Usage: $ python 8bh_csv_to_sprite.py <input_csv>"
    print "<input_csv> is a valid csv file with the data of the sprite"
    exit(1)

ip = "p_b->position"    # ip = init post string
sp = "p_c->data"        # sp = struct pointer string
nc = "p_c->dim_y"       # nc = number of columns string
of = "offset"           # of = offset string
bg = "=p_b->color;\n"   # bg = background color string
pc_i = "=p_b->color["   # pc_i = palette color init string
pc_e = "];\n"           # pc_e = palette color end string
wc = "=white_color;\n"  # wc = white color string

source_code_lines = ["int offset=0;\n"]
update_offset_string = ""
paint_pixel_string = ""

# Obtain content from the CSV file
csv_content = open(sys.argv[1], 'r').read().split("\n")

source_code_line = ""
color_codes = ["s2", "s1", "b", "t1", "t2", "w"]
for row_index, line in enumerate(csv_content):
    update_offset_string = of + "=" + nc + "*" + str(row_index) + ";\n"    
    cells_with_color = [(i,x) for i,x in enumerate(line.split(";")) if x in color_codes]
    if cells_with_color:
        source_code_lines.append(update_offset_string);
        for col_index, cell_value in cells_with_color:
            if cell_value == "s2":
                source_code_line = sp + "[" + ip + "+" + str(col_index) + "+" + of + "]" + pc_i + str(0) + pc_e
            elif cell_value == "s1":
                source_code_line = sp + "[" + ip + "+" + str(col_index) + "+" + of + "]" + pc_i + str(1) + pc_e
            elif cell_value == "b":
                source_code_line = sp + "[" + ip + "+" + str(col_index) + "+" + of + "]" + pc_i + str(2) + pc_e
            elif cell_value == "t1":
                source_code_line = sp + "[" + ip + "+" + str(col_index) + "+" + of + "]" + pc_i + str(3) + pc_e
            elif cell_value == "t2":
                source_code_line = sp + "[" + ip + "+" + str(col_index) + "+" + of + "]" + pc_i + str(4) + pc_e
            elif cell_value =='w':
                source_code_line = sp + "[" + ip + "+" + str(col_index) + "+" + of + "]" + wc
                
            source_code_lines.append(source_code_line);
        
# Write line in output file and exit
output_file = sys.argv[1] + "_sprite.txt"
writer = open(output_file, "w").write(''.join(source_code_lines));
print "Results saved in ./" + output_file