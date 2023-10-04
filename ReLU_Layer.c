//
// Created by Css on 2/19/2021.
//

#include "ReLU_Layer.h"

void ReLU_Layer(float ***input, int input_height, int input_width, int input_depth){
    for (int i = 0; i < input_depth; ++i) {
        for (int j = 0; j < input_height; ++j) {
            for (int k = 0; k < input_width; ++k) {
                if(*(*(*(input + i) + j) + k) < 0){
                    *(*(*(input + i) + j) + k) = 0;
                }
            }
        }
    }
}