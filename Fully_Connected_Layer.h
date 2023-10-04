//
// Created by Css on 2/19/2021.
//

#ifndef PROJECT_MASTER_FULLY_CONNECTED_LAYER_H
#define PROJECT_MASTER_FULLY_CONNECTED_LAYER_H

float *Fully_Connected_Builder(float *input, int depth, int nnumber_of_output_neurons, float **weights);
void Sigmoid_Activation (float * neuron_output);

#endif //PROJECT_MASTER_FULLY_CONNECTED_LAYER_H
