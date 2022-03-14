<!--- PROJECT LOGO --->
![project_logo](https://github.com/amcajal/8_bit_hubble/blob/master/project/doc/media/8_bit_hubble_readme_logo.png)

<!--- BADGES AND SHIELDS --->
![License](https://img.shields.io/badge/License-GPL%20v3.0-blue.svg)
![Version](https://img.shields.io/badge/Version-1.0.1-blue.svg)
[![Build Status](https://travis-ci.org/amcajal/8_bit_hubble.svg?branch=master)](https://travis-ci.org/amcajal/8_bit_hubble)
[![codecov](https://codecov.io/gh/amcajal/8_bit_hubble/branch/master/graph/badge.svg)](https://codecov.io/gh/amcajal/8_bit_hubble)

<!--- PROJECT SUMMARY/OVERVIEW --->
**8-bit Hubble** is a desktop application that generates [PNG](https://es.wikipedia.org/wiki/Portable_Network_Graphics) images of galaxies
with an 8-bit appearance - also known as [Pixel Art](https://en.wikipedia.org/wiki/Pixel_art). 
The galaxies are random: number of stars, its color, size, position, shape, 
as well as other elements like background
color (technically, the [nebula](https://en.wikipedia.org/wiki/Nebula)) are randomly chosen.

[Re-implementation in Go](https://github.com/amcajal/8_bit_hubble_golang) already available

Here are some examples:
![Galaxy_collage](https://github.com/amcajal/8_bit_hubble/blob/master/project/doc/media/8bh_galaxy_collage.png)

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
A comparison between Ross famous catchphrases and the algorithm [can be seen here.](https://github.com/amcajal/8_bit_hubble/wiki/Page-6:-Bob-Ross-Algorithm)

For technical details and more info, visit the [Wiki of the project](https://github.com/amcajal/8_bit_hubble/wiki)

**8-bit Hubble** is also a proof of concept project, whose goal is to test the
compatibility between [Safety-Critical System Software](https://en.wikipedia.org/wiki/Safety-critical_system) goals
and "Clean Code" principles, like
[Test Driven Development](https://en.wikipedia.org/wiki/Test-driven_development),
[Extreme Programming](https://en.wikipedia.org/wiki/Extreme_programming),
and [Continuous Integration](https://en.wikipedia.org/wiki/Continuous_integration).

Also, the project is a sandbox for "homebrew principles", like a [5s Philosophy Directory Structure](https://github.com/amcajal/8_bit_hubble/wiki/Content-of-the-project).

---

## Index
1. [Quickstart](#quickstart)
2. [Contributions](#contributions)
3. [License](#license)
4. [Contact](#contact)

---

## Quickstart
#### For users:
**8-bit Hubble** is a single executable. No installation is needed.
[Click here](https://github.com/amcajal/8_bit_hubble/tree/master/downloads) to go to the downloads page, select your version, and click on "Download" button (at the right side of the screen).
Once downloaded, usage is straightforward: double click on the exe and
1. Choose the image's name
2. Optional, choose a seed for the image (it will control the random generation process)
3. Click "Generate".
Any errors will appear in the messages windows. Otherwise... enjoy!

#### For developers:

- Clone the repository: 
```
$> git clone https://github.com/amcajal/8_bit_hubble.git
```


- Modify the <root_dir>/project/dev/test/high_level_test/python_uat.py (instructions in the very file) with
the proper information. Otherwise, several errors will appear during the build.

- Run "setup.sh" script. It performs a full build process. Use bash, not sh!
(dependency checking, executable build, tests running, coverage and performance reports, etc).
```
$> cd <project root dir>
$> bash setup.sh
```

A "setup_log.txt" is generated with the results of the build process.
If everything is correct, then the GUI can be launched (as explained in the previous section), or
the CLI version.

```
$> 8_bit_Hubble_cli.exe --help
```

- To run tests:
```
$> cd <root_dir>/project/dev/integration
$> make clean
$> make all
$> make tests
```
Then, under /test/ dir, the executable can be launch

- For windows, things are a little more complicated. Open the _Makefile_ (under <root_dir>/project/dev/integration) for more information, but in summary, launch the following command:
```
$> make all TARGET=windows
```

Finally, to jump right into the code, its recommended to start reading the "big_bang_core" module implementation, located at <root_dir>/project/dev/src/big_bang_core/

[Back to index](#index)


## License

About **8-bit Hubble**:

Alberto Martin Cajal is the original author of **8-bit Hubble**. 
**8-bit Hubble** is released under GNU GPL version 3.0 license. Check LICENSE file for a full version of it, or visit the [official GNU web page](https://www.gnu.org/licenses/gpl-3.0.en.html)


About **libpng** and **GTK**:

These libraries are third-party libraries and are NOT owned by **8-bit Hubble** author.

libpng is released under the libpng license. Check the [official webpage](http://www.libpng.org/pub/png/libpng.html).

GTK+ is released under GNU LGPL license. Check the [official webpage](https://developer.gnome.org/gtk3/stable/index.html)

[Back to index](#index)


## Contributions
**8-bit Hubble** is open to contributions! [Check the related page at the Wiki of the project](https://github.com/amcajal/8_bit_hubble/wiki/Page-9:-Contributions)

[Back to index](#index)


## Contact
Alberto Martin Cajal at:
 
- Gmail: amartin.glimpse23@gmail.com (amartin DOT glimpse23 AT gmail DOT com)
- [Blogspot](http://glimpse-23.blogspot.com.es/)
- [LinkedIn](https://es.linkedin.com/in/alberto-martin-cajal-b0a63379)
- Twitter: @amartin_g23

[Back to index](#index)

---

#### This project has been created trying to make it useful. This project has been created in order to learn new things. But over all, this project has been created because it is fun. As Isaac Asimov said:

*The most exciting phrase to hear in science, the one that heralds new discoveries, is not 'Eureka' but 'That's funny...'*
