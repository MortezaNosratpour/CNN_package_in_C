//
// Created by Css on 2/19/2021.
//

#include <stdio.h>
#include <stdlib.h>


#include "Convolution_Layer.h"


float Convolutione_Calculater(float ***input, int height, int width, float ***mask, int mask_height, int mask_width, int mask_depth, float bias, int stride_x, int stride_y){
    float sum = 0;
    for (int i = 0; i < mask_depth; ++i) {
        for (int j = (-1*mask_height)/2 ; j < ((mask_height)/2) + 1 ; ++j) {
            for (int k = (-1*mask_width)/2; k < ((mask_width)/2) + 1; ++k) {
                sum += *(*(*(input + i) + height + j) + width + k) * *(*(*(mask + i) + j + ((mask_height)/2)) + k +((mask_width)/2));
            }
        }
    }
    return sum;
}

float ** Convolutional_Plane_Builder(float *** input, int input_height, int input_width, int input_depth, float ***mask, int mask_height, int mask_width, int mask_depth, float bias, int stride_x, int stride_y){
    float **output;
    output = (float **) malloc(sizeof(float *) * input_height);
    for (int i = 0; i < input_height; ++i) {
        output[i] = (float *) malloc(sizeof(float ) * input_width);
    }
    int x_margin = (2*(mask_height/2));
    int y_margin = (2*(mask_width/2));
    float ***tmp;
    tmp = (float***) malloc(sizeof(float **) * input_depth);
    for (int i = 0; i < input_depth; ++i) {
        tmp[i] = (float **) malloc(sizeof(float *) * (input_height + x_margin));
        for (int j = 0; j < input_height + x_margin; ++j) {
            tmp[i][j] = (float *) malloc(sizeof(float ) * (input_width + y_margin));
        }
    }

    float const padding_number = 0;
    for (int i = 0; i < input_depth; ++i) {
        for (int j = 0; j < input_height + x_margin; ++j) {
            for (int k = 0; k < input_width + y_margin; ++k) {
                if(k < y_margin/2 || j < x_margin/2 || k > input_width + y_margin/2  || j > input_height + x_margin/2 -1){
                    *(*(*(tmp + i) + j) + k) = padding_number;
                    //printf("%f   ", *(*(*(tmp + i) + j) + k));
                }
                else{
                    *(*(*(tmp + i) + j) + k) = *(*(*(input + i) + j-x_margin/2) + k-y_margin/2);
                    //printf("%f   ", *(*(*(tmp + i) + j) + k));
                }
            }
            //printf("\n");
        }
        //printf("\n");
    }

    int x = 0, y= 0;
    for (int l = x_margin/2; l < input_height+x_margin/2; l+= stride_x) {
        y = 0;
        for (int i = y_margin/2; i < input_width+y_margin/2; i+=stride_y) {
            *(*(output + x) + y) = Convolutione_Calculater(tmp, l, i, mask, mask_height, mask_width, mask_depth, bias, stride_x, stride_y);
            y += 1;
        }
        x += 1;
    }

    return output;
}

float ***Convolutional_Layer_Builder(float ***input, int input_height, int input_width, int input_depth, float **** mask, int mask_height, int mask_width, int mask_depth, int number_of_mask, float bias, int stride_x, int stride_y){
    float ***output;
    output = (float ***) malloc(sizeof(float **) * number_of_mask);
    for (int i = 0; i < number_of_mask; ++i) {
        output[i] = (float **) malloc(sizeof(float *) * input_height);
        for (int j = 0; j < input_height; ++j) {
            output[i][j] = (float *) malloc(sizeof(float ) * input_width);
        }
    }


    for (int i = 0; i < number_of_mask; ++i) {
        //printf("hi");
        output[i] = Convolutional_Plane_Builder(input, input_height, input_width, input_depth, *(mask + i), mask_height, mask_width, mask_depth, bias, stride_x, stride_y);
    }

    return output;
}

