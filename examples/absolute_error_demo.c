#include <math.h>
#include <stdio.h>

#include "miniai/ml/activation/absolute_error.h"

int main() {
    double prediction1=15.0;
    double prediction2=25.0;

    double target1=5.0;
    double target2=NAN;

    double answer1=miniai_absolute_error(prediction1,target1);
    double answer2=miniai_absolute_error(prediction2,target2);
    printf("example1: %lf", answer1);
    printf("example2: %lf", answer2);
}