//
// Created by Css on 2/19/2021.
//

#ifndef PROJECT_MASTER_MAX_POOLING_LAYER_H
#define PROJECT_MASTER_MAX_POOLING_LAYER_H

float max_finder(float * max, int count);
float Max_Sliding_Window(float **input, int height, int width, int sliding_windows_height, int sliding_windows_width);
float *** Max_Pooling(float ***input, int input_height, int input_width, int input_depth, int stride_x, int stride_y, int sliding_windows_height, int sliding_windows_width);


#endif //PROJECT_MASTER_MAX_POOLING_LAYER_H
