/*******************************************************************************
*   Project: 8-Bit Hubble
*
*   File: rng_tests.c
*
*   Description: Source file for rng tests module. It verifies the proper
*               implementation of the rng module functionality (upper and
*               lower limits, seed configuration, etc).
*
*   Notes: Check for the label @VISUAL_CHECK 
* 			to uncomment printf for visual checkings.
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
#include <limits.h>
#include "../../src/rng/rng.h"

/*
* Test seed is properly loaded depending on the user choice.
* Requires visual checking too.
*/
void test_load_seed(void)
{
    /*
	*	Check the following:
	* 	> If seed is -1, seed is automatically generated.
    *   > If seed is not -1, seed is set to the input value.
	*/
    
    /*If seed is -1, seed is automatically generated. */
    load_seed(-1);
    assert(get_seed() != -1);
    
    /* If seed is not -1, seed is set to the input value. */
    load_seed(0);
    assert(get_seed() == 0);
    load_seed(65535);
    assert(get_seed() == 65535);
    load_seed(1234);
    assert(get_seed() == 1234);
}

/*
* Test generation of random number up to the given limit.
*/
void test_generate_rn_up_to(void)
{
    /*
	*	Check the following:
	* 	> Generate number up to 0.
    *   > Generate number up to negative number.
    *   > Generate number up to positive number.
    *   > Generate number with NULL as limit.
	*/
    load_seed(10); /* Seed doesn't really matters in this test. */
    int generated_n;
    int i;
    int checks = 20;
    int first_example = 80,
        second_example = 5,
        third_example = 1;
    
    /* Generate number up to 0. */
    generated_n = generate_rn_up_to(0);
    assert(generated_n == 0);
    
    /* Generate number up to negative number. */
    generated_n = generate_rn_up_to(-1);
    assert(generated_n == 0);
    
    /* Generate number up to positive number. */
    for (i=0; i< checks; i++){
        generated_n = generate_rn_up_to(first_example);
        assert((generated_n >= 0) && (generated_n <= first_example - 1));
        // @VISUAL_CHECK
        // printf("%d%s", generated_n, (i==19) ? "\n" : " ");
    }
    
    for (i=0; i< checks; i++){
        generated_n = generate_rn_up_to(second_example);
        assert((generated_n >= 0) && (generated_n <= second_example - 1));
        // @VISUAL_CHECK
        // printf("%d%s", generated_n, (i==19) ? "\n" : " ");
    }
    
    for (i=0; i< checks; i++){
        generated_n = generate_rn_up_to(third_example);
        assert((generated_n >= 0) && (generated_n <= third_example - 1));
        // @VISUAL_CHECK
        // printf("%d%s", generated_n, (i==19) ? "\n" : " ");
    }

    /* Generate number with NULL as limit. */
    /* Compiler with -Wall generates a warning, enought to correct the problem. */
}

/*
* Test generation of random number within the specified limits.
*/
void test_generate_rn_within(void)
{
    /*
    *   There are several possibilites to check:
    *   > Min and max equals:
    *       >> Negative value
    *       >> Zero
    *       >> Positive value
    *   > Min and max different:
    *       >> Min Negative, Max Positive
    *       >> Min Positive, Max Negative
    *       >> Min 0, Max Positive
    *       >> Min Positive, Max 0
    *       >> Min 0, Max Negative
    *       >> Min Negative, Max 0
    *
    *   However, the function generate_rn_within calls to generate_rn_up_to.
    *   Given that generate_rn_up_to covers all integer possibilities,
    *   problems may arise only when the values provided could lead to
    *   overflow integer results. These situations are the ones tested.
    *   Nevertheless, generate_rn_within structure avoids any possible
    *   overflow (there is not possible combination where the result can
    *   cause integer overflow).
	*/
    
    load_seed(10); /* Seed doesn't really matters in this test. */
    int generated_n;
    int i;
    int checks = 20;
    
    /* Normal checking. */
    int min = 0,
        max = 10;
    for (i=0; i< checks; i++){
        generated_n = generate_rn_within(min,max);
        assert((generated_n >= min) && (generated_n <= max));
        // @VISUAL_CHECK
        // printf("%d%s", generated_n, (i==19) ? "\n" : " ");
    }
    
    min = 5;
    max = 15;
    for (i=0; i< checks; i++){
        generated_n = generate_rn_within(min,max);
        assert((generated_n >= min) && (generated_n <= max));
        // @VISUAL_CHECK
        // printf("%d%s", generated_n, (i==19) ? "\n" : " ");
    }
    
    /* Overflow checking. */
    min = LONG_MAX;
    max = LONG_MAX;
    for (i=0; i< checks; i++){
        generated_n = generate_rn_within(min,max);
        assert((generated_n >= min) && (generated_n <= max));
        // @VISUAL_CHECK
        // printf("%d%s", generated_n, (i==19) ? "\n" : " ");
    }
}

/*
* Core function.
*/
void run_rng_tests(void)
{
    test_load_seed();
    test_generate_rn_up_to();
    test_generate_rn_within();
    printf("rng_tests: All tests successful.\n");
}
