#include "loss/absolute_error.c"

void test_absolute_error_basic(void) {
    double result1 = miniai_absolute_error(3.0, 1.0);
    if (result1==2.0) printf("test (3.0; 1.0) succeeded\n");
    else printf("test (3.0; 1.0) failed\n");

    double result2 = miniai_absolute_error(1.0, 3.0);
    if (result2==2.0) printf("test (1.0; 3.0) succeeded\n");
    else printf("test (1.0; 3.0) failed\n");

    double result3 = miniai_absolute_error(3.0, 3.0);
    if (result3==0.0) printf("test (3.0; 3.0) succeeded\n");
    else printf("test (3.0; 3.0) failed\n");

    double result4 = miniai_absolute_error(-0.0, 0.0);
    if (result4==0.0) printf("test (-0.0; 0.0) succeeded\n");
    else printf("test (-0.0; 0.0) failed\n");

    double result5 = miniai_absolute_error(NAN, 1.0);
    if (isnan(result5)) printf("test (NaN; 1.0) succeeded\n");
    else printf("test (NaN; 1.0) failed\n");
}