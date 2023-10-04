//
// Created by Css on 2/25/2021.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "Softmax_Layer.h"

double * Softmax_Layer(float *input, int number_of_neurons){
    float * tmp;
    tmp = (float *) malloc(sizeof(float) * number_of_neurons);

    double sum = 0;
    for (int i = 0; i < number_of_neurons; ++i) {
        sum += exp(1.0 * *(input + i));
    }
    printf("\nsum = %f\n", sum);

    for (int i = 0; i < number_of_neurons; ++i) {
       *(tmp + i) = (exp(1.0 * *(input+i)))/sum;
        //printf("%f, ",  *(tmp + i));
    }
   // printf("\n");

    return tmp;
}