OVERVIEW
======
**8-bit Hubble** is a desktop application that generates [PNG](https://es.wikipedia.org/wiki/Portable_Network_Graphics) images of galaxies
with an 8-bit appearance - also known as [Pixel Art](https://en.wikipedia.org/wiki/Pixel_art). 
The galaxies are random: number of stars, its color, size, position, shape, 
as well as other elements like background
color (technically, the [nebula](https://en.wikipedia.org/wiki/Nebula)) are randomly chosen.

**8-bit Hubble** its a humble tribute to:
- The [Hubble Space Telescope](http://hubblesite.org/), mankind's technological prodigy 
showing how important and amazing
the space exploration is. In fact, the images generated are somewhat similar 
to the ones at ["What is Hubble looking at now?"](http://spacetelescopelive.org/)
- Classic Videogames: technology made entertainment;
titles like R-Type DX, Super Mario World, Metroid,
and TMNT Turtles in Time serve as inspiration for the sprites of the application.
- [Bob Ross](https://en.wikipedia.org/wiki/Bob_Ross), the legendary painter. 
The "wet-on-wet" technique, used by Ross, serve as model to
the application algorithms (a kind of [Painter's Algorithm](https://en.wikipedia.org/wiki/Painter%27s_algorithm). 
A comparison between Ross famous catchphrases and the algorithm [can be seen here.](@TODO)

The application is fully developed in the C programing language. Besides the "kernel" code, the two main libraries used by the application
are the GTK library -for the GUI version-, and the libPNG, that handles the creation of the PNG images.



ARCHITECTURE
======
The application interfaces with the user in a very simple way, as the following diagram shows:

@TODO

Basically, the user specifies, either through the GUI or by command line, the name of the image, its output location, and as optional
parameter, a seed (that will control the [Random Number Generation](https://en.wikipedia.org/wiki/Random_number_generation)). 
If everything its correct, then a new image is generated. Otherwise, the application provides feedback of what went wrong.

A more detailed view of such process is shown in the next figure: 

@TODO

The architecture of 8-Bit Hubble tries to be modular, high-cohesive, low-coupled, with clean interfaces and easy to understand. These
goals gives as a result the following modules: 

@TODO imagen

Each module has its own source folder under <root_dir>/project/dev/src directory, making it easy to access to its code.
The name of the modules has been chosen to be as descriptive as possible -in fact, naming of certain functions and 
variables have been made following the real world objects, like "canvas" and "brush". In general, readability has been the
main goal to achieve in the whole project.

A quick description of each module is provided:

- **cli**: 
CLI module (Command Line
Interface) implements the ENTRY POINT of the application
in its CLI version. It parses the input arguments
provided by the user, and performs the required
operations (i.e: print version, help message, generate
image, or print error message).

- **gui**
It implements
the GTK source of the GUI and the ENTRY POINT for
such version.

- **big_bang_core**: 
This module represents
the "core" algorithm of the application.
It checks the user configuration, generates the random galaxy
and writes it in the png file, alongside with related cleanup
and error handling operations. It is called "big_bang" because,
as the homonymous theory, its the "origin" of the data.

- **status_reporter**: 
Status reporter
module is the "Error handler" module of the application.
It defines all possible error codes, used to check
if operations are being executed as expected. It
provides a feedback or "debug" functionality too,
to warn about encountered problems.

- **image_writer**: 
Image writer
generates ("writes") the final PNG image with the
created galaxy. Its core is the PNG library to create
the PNG image with the required data (magic number,
header data, etc).

- **user_config_checker**: 
As it name
implies, the module checks that the configuration
provided by the user to generate the galaxy is correct
in terms of: valid image name, valid output directory,
valid seed (if provided), etc.

- **galaxy_generator**: 
Galaxy_generator
module implements the CORE algorithm of the application.
It initializes the canvas and the palette, and then,
by layers, print the sprites on it, in a random fashion
(location, size, color).

- **canvas**: 
Contains both
the data structure representing the canvas (where the galaxy
will be painted), and related management operations.
The core concept of a canvas is its dimensions, width and height
that define at the same time the size of the output image.

- **palette**: 
Palette implements
the data structure that represents the real "palette"
of colors. It also implements the required methods
to obtain a color from it, and generate tints and
shadows, like a real painter would do.

- **rng**: 
RNG module provides a clean
interface to deal with Random Number Generator methods.
It basically generates random numbers on demand. 
Generation can be configured through a seed.

- **sprites**: 
As it names implies,
Sprites module contains the sprites that can be generated
in the galaxy. A sprite is characterized by its size,
and the pixels where it shall be painted. The module
provides a clean interface to "stamp" or "print"
a sprite into the canvas.

- **brush**: 
Contains the data
structure that represents a painting brush, characterized by
the color loaded on it, its position on the canvas, and the
"density" of the brushstrokes (more or less objects being
painted in the canvas).

- **app_info**: 
Provides textual data
of the application, like HELP and VERSION messages, as well
as the functions to print them.



IMAGE REPRESENTATION
======
First of all, the 8-bit term makes reference to the look of the images, not to a specific implementation of the code.

Images are coded as vectors (or arrays, in C language terminology), of X*Y elements, being X the width and Y the height. Each vector
element represents a pixel of the image with a specific color. This is known as [Direct Color](https://en.wikipedia.org/wiki/Color_depth#Direct_color).
The pixel colors are codified in [RGB](https://en.wikipedia.org/wiki/RGB_color_model) format, using 8 bits for each channel. 
Thus, each pixel can be represented using a 32-bit data type. Take
into consideration that the 8 last bits (from bit 31 to 24) are not used (no transparency applied here). In this way, each channel
can take values from 0 to 255.

The following image assemble all of this together, representing a 4-pixel image in its various interpretations (as the final image,
as the vector representation, and as a specific implementation in the C language).

@TODO



COLOR PALETTE
======
Once again, the 8-bit term makes reference to the look of the images, not to a [8-bit palette](https://en.wikipedia.org/wiki/8-bit_color).

To obtain such 8-bit look, a reduce color palette is used. The palette contains only 216 entries, and its based in the [ANSI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code).
In fact, an almost perfect mapping can be done between the application color palette and the hexadecimal values of such ANSI colors. Another
source of "inspiration" to choose the colors, is the [256 colors of the Xterm terminal](https://commons.wikimedia.org/wiki/File:Xterm_256color_chart.svg).

@TODO image of colors

However, these are not the only colors used in the images. Through the generation of shades and tints 
(two shades and two tints for each color),
the total number of available colors is much higher (more than 1000). 
This keeps that 8-bit looking, but provides a "cooler" sensation, giving the sprites
shadows and depth.

@TODO tints and shades

The color palette itself is codified as a vector of 32-bit data type elements, each one holding one RGB color.



SPRITES DESIGN
======
The starts, the main element in the images, are treated as [sprites](https://en.wikipedia.org/wiki/Sprite_(computer_graphics)).
Each sprite is a "sub-image": another X*Y vector, each component representing a pixel and its color. However, in this case, certain
elements are "empty", reproducing transparent pixels. This allows to overlap them, keeping a cool look.

Each sprite is coded as a specific sequence of instructions. In C terminology, each sprite is a function, which access to the array that
holds the image data, an iterates over it modifying specific pixels to draw the pixel on it.

@TODO

However, as the sprites becomes more complex, generate the functions manually would become a daunting task. The functions
or sequence of instructions are generated automatically through a python script, which input is a spreadsheet (yes, a spreadsheet).
Such spreadsheet has a specific format that allows the user to literally draw the sprites on it, selecting the color of each pixel.
This puts all the effort in the "artistic" side, and reliefs the user from the programming part.

Thus, the elements involved in this process are:
- The Spreadsheet, called _8bH_all_sprites.xlsx_, and located under <root_dir>\project\dev\design
- The python script, called _8bh_csv_to_sprite.py_, and located under <root_dir>\project\scripts

The spreadsheet contains detailed instructions on how to create new sprites, and it includes several working examples.
It is very easy to add new sprites! Some of the current ones are shown below:

@TODO

As a final note: this method of sprite design is somewhat similar to the [Digitizer System from Sega](https://segaretro.org/Digitizer_System).


THE "BOB ROSS" ALGORITHM
======
The core functionality of the application is contained in the *galaxy_generator* module, who contains the implementation of what its
called the "Bob Ross Algorithm".
The "Bob Ross Algorithm" is nothing but a implementation of the [Painters Algorithm](https://en.wikipedia.org/wiki/Painter%27s_algorithm),
inspired in [Bob Ross](https://en.wikipedia.org/wiki/Bob_Ross) and its [Wet-on-wet](https://en.wikipedia.org/wiki/Wet-on-wet) painting technique. 
Similar to the real world process, the algorithm generates the data
of the image layer by layer. Each layer is characterized by the type of stars to be painted, its position, the color of the sprites, etc.
Relation with Bob Ross does not finish in a choice of name: the chapters of his TV Show, "The Joy of Painting", where used to develop such
algorithm, as it almost mimics the steps he pursues to create its paintings. The following diagrams shows both the algorithm steps, and
the connection between them and the famous Ross catchphrases:

@TODO

Unfortunately, the digital world leaves out some iconic moments - no "beat the devil out of it".
And of course, you can find all episodes of the show in the [Bob Ross's Youtube Official Channel](https://www.youtube.com/user/BobRossInc/featured). 