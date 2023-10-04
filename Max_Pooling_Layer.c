//
// Created by Css on 2/19/2021.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "Max_Pooling_Layer.h"

float max_finder(float * max, int count){
    float maximum = -10000000000;
    for (int i = 0; i < count; ++i){
        if(maximum < *(max + i)){
            maximum = *(max + i);
        }
    }
    return maximum;
}

float Max_Sliding_Window(float **input, int height, int width, int sliding_windows_height, int sliding_windows_width){
    float *max = (float *) malloc(sizeof(float) * sliding_windows_height * sliding_windows_width);
    int counter = 0;
    for (int i = height; i < height + sliding_windows_height; ++i) {
        for (int j = width; j < width + sliding_windows_width ; ++j) {
            *(max + counter) = *(*(input + i) + j);
            counter++;
        }
    }
    float maximum = max_finder(max, sliding_windows_height * sliding_windows_width);
    return maximum;
}


float *** Max_Pooling(float ***input, int input_height, int input_width, int input_depth, int stride_x, int stride_y, int sliding_windows_height, int sliding_windows_width){
    float ***output;
    int height = input_height/stride_y;
    int width = input_width/stride_x;

    output = (float ***)malloc(sizeof(float **) * input_depth);

    for (int i = 0; i < input_depth; ++i) {
        output[i] = (float **)malloc(sizeof(float *) * height);
        for (int j = 0; j < height; ++j) {
            output[i][j] = (float *)malloc(sizeof(float ) * width);
        }
    }


    int x = 0;
    int y = 0;
    for (int k = 0; k < input_depth ; ++k) {
        x = 0;
        for (int i = 0; i < input_height;  i+=stride_x) {
            y = 0;
            for (int j = 0; j < input_width; j+=stride_y) {
                *(*(*(output + k) + x) + y) = Max_Sliding_Window(*(input + k), i, j, sliding_windows_height, sliding_windows_width);
                y += 1;
            }
            x += 1;
        }
    }


    return output;

}