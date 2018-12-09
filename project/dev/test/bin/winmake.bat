gcc -Wall -O0 -c ../unit_test/user_config_checker_tests.c
gcc -Wall -O0 -c ../unit_test/rng_tests.c
gcc -Wall -O0 -c ../unit_test/palette_tests.c
gcc -Wall -O0 -c ./8bb_test.c
gcc -Wall -O0 -o ./8bb_test.exe ./user_config_checker_tests.o ./rng_tests.o ./palette_tests.o ./8bb_test.o 