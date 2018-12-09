#include <string.h>

#ifndef _DATA_FOR_TESTING_H
#define _DATA_FOR_TESTING_H

/* 
* NON_EXIST_DIR shall be a path to a non-existing folder.
* PERM_DIR and NO_PERM_DIR shall be paths to folders with and without
* reading/writing/executing permissons, respectively.
* Paths shall use slash char (/) as separator, and end with an slash.
* Paths can be relative or absolute, but make sure they are correct.
*
* Example:
* #define PERM_DIR "../example_dirs/all_perm_dir/"
* #define NO_PERM_DIR "/home/Neo/matrix_docs/smith_folder/"
*/

//#define NO_EXIST_DIR ""
//#define PERM_DIR ""
//#define NO_PERM_DIR ""

#if !defined(NO_EXIST_DIR) || !defined(PERM_DIR) || !defined(NO_PERM_DIR)
    #error "test/high_level_test/directories.h: Please define paths to valid test directories"
#endif

#define BASE_IMAGE_PATH "../high_level_test/base_image.png"
#define BASE_IMAGE_SEED 1526253834

#endif /* _DATA_FOR_TESTING_H */
