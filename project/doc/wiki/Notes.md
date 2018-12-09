NOTES
=====

This page contains the notes generated during the application development. The notes are kept for further usage and documentation
purposes, but they shall not be used as reference for the current application status (functionality, structure, etc). Such information
is located under project/def folder.

A number between brackets represents a reference to the [Resources](@TODO) page in the Wiki.
For example, [4] representes the entry with ID 4 at Resources page.
****

## Writting PNG images with LibPNG
First, download the libpng library [1]. There are two options, first recommended:   
1.1- Install through apt as follows:  
	`sudo apt-get install libpng-dev`

1.2 - Download the libpng library from the official webpage, using command wget:  
    ```
	wget http://prdownloads.sourceforge.net/libpng/libpng-1.6.32.tar.gz?download
    tar -xzvf <file>
    ```

The problem is that apt may download the version 1.2.50, and when compiling, reference to the 1.6. Later we will see
how to fix this.

If downloaded from the official webpage, do step 2:   
2 - Go to the decompressed folder, and install the library following the instructions of INSTALL file:
	```
    ./configure
	./make check
	./make tests
    ```

Then, if the test suit is correct (no failures):

3- Create a simple code to check if libraries can be properly included:   
    ```
	#include <png.h>
	#include <zlib.h>
	(...) png_image image; (...)
    ```

4- Compile. Depending on the versions in the computer, gcc command will vary:   
4.1 - Only one version installed   
	`gcc -Wall -O0 -o <output> <file_to_compile> -lm -lpng`

4.2 - Several versions installed:   
	run "whereis libpng" command to show all possible libs
	`gcc -Wall -O0 -I<route_to_desired_libpng> -o <output> <file_to_compile> -lm-lpng`

For example: version 1.6 installed manually and 1.2.50 from apt, so gcc command was:   
	`gcc -O0 -Wall -lm -I/usr/include/libpng -lpng -o wpng2 write_png_v1_6.c`