#include <stdio.h>
#include <miniai/math/statistics.h>

int main() {
    double data1[]={1, 2, 3};
    double data2[]={2, 4, 6, 8};

    size_t n1 = sizeof(data1) / sizeof(data1[0]);
    size_t n2 = sizeof(data2) / sizeof(data2[0]);

    double answer1 = miniai_variance( data1, n1 );
    double answer2 = miniai_variance( data2, n2 );
    printf( "example1: %lf\n", answer1 );
    printf( "example2: %lf\n", answer2 );
    return 0;
}