#include <assert.h>

/*
* Test code.
*/  
void test_1(void)
{
    assert(1==1);
}

/*
* Core function.
*/
void run_tests (void)
{
    test_1();
    printf("tests: All tests successful.\n");
}
