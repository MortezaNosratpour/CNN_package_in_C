//
// Created by Css on 2/19/2021.
//

#ifndef PROJECT_MASTER_CONVOLUTION_LAYER_H
#define PROJECT_MASTER_CONVOLUTION_LAYER_H

float Convolutione_Calculater(float ***input, int height, int width, float ***mask, int mask_height, int mask_width, int mask_depth, float bias, int stride_x, int stride_y);
float ** Convolutional_Plane_Builder(float *** input, int input_height, int input_width, int input_depth, float ***mask, int mask_height, int mask_width, int mask_depth, float bias, int stride_x, int stride_y);
float *** Convolutional_Layer_Builder(float ***input, int input_height, int input_width, int input_depth, float **** mask, int mask_height, int mask_width, int mask_depth, int number_of_masks, float bias, int stride_x, int stride_y);

#endif //PROJECT_MASTER_CONVOLUTION_LAYER_H
