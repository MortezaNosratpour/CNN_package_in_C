//
// Created by Css on 2/19/2021.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "Fully_Connected_Layer.h"

void Sigmoid_Activation (float * neuron_output){
    float const constant = -1;
    *(neuron_output) = (float)(1.0/(1+exp(constant * *(neuron_output))));
}

float *Fully_Connected_Builder(float *input, int depth, int number_of_output_neurons, float **weights){
    float *output;
    output = (float *)malloc(sizeof(float) * number_of_output_neurons);

    for (int i = 0; i < number_of_output_neurons; ++i){
            *(output + i) = 0;
    }

    for (int i = 0; i < number_of_output_neurons; ++i) {
        for (int j = 0; j < depth; ++j) {
            *(output + i) += ((*(input + j) * *(*(weights + i) + j)));
            if(i%2 ==1){
                printf("%10f, ", *(*(weights + i) + j));
            }
        }
       printf("............. %f", *(output+i));
        printf("\n");
//        Sigmoid_Activation((output + i));
//        printf("............. %f\n", *(output+i));
    }

    return output;
}