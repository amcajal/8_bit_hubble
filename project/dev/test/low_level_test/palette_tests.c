/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: palette_tests.c
*
*   Description: Source file of palette tests module. Palette tests module
*               implements unit tests that verify the correct functionality
*               of palette module (are colors properly generated? tints and
*               shades concur mathematically? etc)
*
*   Notes: N/A
*
*   Contact: Alberto Martin Cajal, amartin.glimpse23<AT>gmail.com
*
*   URL: https://github.com/amcajal/8_bit_hubble
*
*   License: GNU GPL v3.0
*
*   Copyright (C) 2018 Alberto Martin Cajal
*
*   This file is part of 8-Bit Hubble.
*
*   8-Bit Hubble is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   8-Bit Hubble is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/


#include <stdio.h>
#include <assert.h>
#include "../../src/palette/palette.h"
#include "../../src/status_reporter/status_reporter.h"
#include "../../src/brush/brush.h"

/* 
* To improve the readability of the tests, follow this look-up table for
* the palettes to be generated (substract 16 units to the index of the 216 palette
* to obtain the real index of the color:
*/

/* 216 ANSI color palette:
16 => 000000
17 => 00005f
18 => 000087
19 => 0000af
20 => 0000d7
21 => 0000ff
22 => 005f00
23 => 005f5f
24 => 005f87
25 => 005faf
26 => 005fd7
27 => 005fff
28 => 008700
29 => 00875f
30 => 008787
31 => 0087af
32 => 0087d7
33 => 0087ff
34 => 00af00
35 => 00af5f
36 => 00af87
37 => 00afaf
38 => 00afd7
39 => 00afff
40 => 00d700
41 => 00d75f
42 => 00d787
43 => 00d7af
44 => 00d7d7
45 => 00d7ff
46 => 00ff00
47 => 00ff5f
48 => 00ff87
49 => 00ffaf
50 => 00ffd7
51 => 00ffff
52 => 5f0000
53 => 5f005f
54 => 5f0087
55 => 5f00af
56 => 5f00d7
57 => 5f00ff
58 => 5f5f00
59 => 5f5f5f
60 => 5f5f87
61 => 5f5faf
62 => 5f5fd7
63 => 5f5fff
64 => 5f8700
65 => 5f875f
66 => 5f8787
67 => 5f87af
68 => 5f87d7
69 => 5f87ff
70 => 5faf00
71 => 5faf5f
72 => 5faf87
73 => 5fafaf
74 => 5fafd7
75 => 5fafff
76 => 5fd700
77 => 5fd75f
78 => 5fd787
79 => 5fd7af
80 => 5fd7d7
81 => 5fd7ff
82 => 5fff00
83 => 5fff5f
84 => 5fff87
85 => 5fffaf
86 => 5fffd7
87 => 5fffff
88 => 870000
89 => 87005f
90 => 870087
91 => 8700af
92 => 8700d7
93 => 8700ff
94 => 875f00
95 => 875f5f
96 => 875f87
97 => 875faf
98 => 875fd7
99 => 875fff
100 => 878700
101 => 87875f
102 => 878787
103 => 8787af
104 => 8787d7
105 => 8787ff
106 => 87af00
107 => 87af5f
108 => 87af87
109 => 87afaf
110 => 87afd7
111 => 87afff
112 => 87d700
113 => 87d75f
114 => 87d787
115 => 87d7af
116 => 87d7d7
117 => 87d7ff
118 => 87ff00
119 => 87ff5f
120 => 87ff87
121 => 87ffaf
122 => 87ffd7
123 => 87ffff
124 => af0000
125 => af005f
126 => af0087
127 => af00af
128 => af00d7
129 => af00ff
130 => af5f00
131 => af5f5f
132 => af5f87
133 => af5faf
134 => af5fd7
135 => af5fff
136 => af8700
137 => af875f
138 => af8787
139 => af87af
140 => af87d7
141 => af87ff
142 => afaf00
143 => afaf5f
144 => afaf87
145 => afafaf
146 => afafd7
147 => afafff
148 => afd700
149 => afd75f
150 => afd787
151 => afd7af
152 => afd7d7
153 => afd7ff
154 => afff00
155 => afff5f
156 => afff87
157 => afffaf
158 => afffd7
159 => afffff
160 => d70000
161 => d7005f
162 => d70087
163 => d700af
164 => d700d7
165 => d700ff
166 => d75f00
167 => d75f5f
168 => d75f87
169 => d75faf
170 => d75fd7
171 => d75fff
172 => d78700
173 => d7875f
174 => d78787
175 => d787af
176 => d787d7
177 => d787ff
178 => d7af00
179 => d7af5f
180 => d7af87
181 => d7afaf
182 => d7afd7
183 => d7afff
184 => d7d700
185 => d7d75f
186 => d7d787
187 => d7d7af
188 => d7d7d7
189 => d7d7ff
190 => d7ff00
191 => d7ff5f
192 => d7ff87
193 => d7ffaf
194 => d7ffd7
195 => d7ffff
196 => ff0000
197 => ff005f
198 => ff0087
199 => ff00af
200 => ff00d7
201 => ff00ff
202 => ff5f00
203 => ff5f5f
204 => ff5f87
205 => ff5faf
206 => ff5fd7
207 => ff5fff
208 => ff8700
209 => ff875f
210 => ff8787
211 => ff87af
212 => ff87d7
213 => ff87ff
214 => ffaf00
215 => ffaf5f
216 => ffaf87
217 => ffafaf
218 => ffafd7
219 => ffafff
220 => ffd700
221 => ffd75f
222 => ffd787
223 => ffd7af
224 => ffd7d7
225 => ffd7ff
226 => ffff00
227 => ffff5f
228 => ffff87
229 => ffffaf
230 => ffffd7
231 => ffffff
*/

/*
* Check proper generation of a 216 color palette based on ANSI escape codes.
* The structure of palette module makes easier to test several capabilities
* in the same function.
*/
void test_ansi_216_colors(void)
{   
    enum status stat;
    
    /* Check status, malloc and initialized variables.*/
    stat = initialize_palette(ANSI_216_COLORS);
    assert(stat == NO_ERROR);
    // assert(palette != NULL); This cannot be test in high level tests.
    assert(get_number_available_colors() == 216);
    
    /* Check colors from the palette. */
    assert(get_color_from_index(-10) == 0x000000); /* Outside limits (negative) */
    assert(get_color_from_index(300) == 0xffffff); /* Outside limits (positive) */
    assert(get_color_from_index(0) == 0x000000); /* Lower bound */
    assert(get_color_from_index(215) == 0xffffff); /* Upper bound */
    assert(get_color_from_index(10) == 0x005fd7); /* Nominal value */
    assert(get_color_from_index(114) == 0xaf5f00); /* Nominal value */
    assert(get_color_from_index(184) == 0xff00d7); /* Nominal value */
}

void test_generate_tints_and_shades (void)
{
	/* To check tints, the loaded palette doesn't really matters. */
	
	enum status stat;
    
    /* Check status, malloc and initialized variables.*/
    stat = initialize_palette(ANSI_216_COLORS);
    assert(stat == NO_ERROR);
    // assert(palette != NULL); This cannot be test in high level tests.
    assert(get_number_available_colors() == 216);
    
	int input_color;
	struct brush test_brush;
    
    /* Check tints and shades of black. */
    input_color = get_color_from_index(0);
    generate_tints_and_shades(input_color, &test_brush);
    assert(test_brush.color[0] == 0x000000);
    assert(test_brush.color[1] == 0x000000);
    assert(test_brush.color[2] == 0x000000);
    assert(test_brush.color[3] == 0x7F7F7F);
    assert(test_brush.color[4] == 0xBFBFBF);
    
    /* Check tints and shades of white. */
    input_color = get_color_from_index(215);
    generate_tints_and_shades(input_color, &test_brush);
    assert(test_brush.color[0] == 0x3F3F3F);
    assert(test_brush.color[1] == 0x7F7F7F);
    assert(test_brush.color[2] == 0xFFFFFF);
    assert(test_brush.color[3] == 0xFFFFFF);
    assert(test_brush.color[4] == 0xFFFFFF);
    
    /* Check tints and shades of a nominal color (red). */
    input_color = get_color_from_index(180);
    generate_tints_and_shades(input_color, &test_brush);
    assert(test_brush.color[0] == 0x3F0000);
    assert(test_brush.color[1] == 0x7F0000);
    assert(test_brush.color[2] == 0xFF0000);
    assert(test_brush.color[3] == 0xFF7F7F);
    assert(test_brush.color[4] == 0xFFBFBF);
}

/*
* Core function.
*/
void run_palette_tests(void)
{
    test_ansi_216_colors();
    test_generate_tints_and_shades();
    printf("palette_tests: All tests successful.\n");
}
