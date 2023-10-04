#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


#include "Convolution_Layer.h"
#include "ReLU_Layer.h"
#include "Max_Pooling_Layer.h"
#include "Softmax_Layer.h"
#include "Fully_Connected_Layer.h"
#include "File_reader.h"
#include "view.h"


#ifdef main
#undef main
#endif



bool flag = false;
int main() {

    //fetch image's pixels : height = 150 & width = 230 & channel = 3(RGB)

    float ***data;
    int j = 0;
    data = (float ***)malloc(sizeof(float **) * 3);

    for(int i = 0; i < 3; i++) {
        data[i] =(float **) malloc(sizeof(float * ) * 20);
        for (j = 0; j < 20; j++) {
            data[i][j] =(float *) malloc(sizeof(float) * 20);
        }
    }

    float * data_pixels = (float *)malloc(sizeof(float) * 3*20*20);
    data_pixels = Integer_Input_Reading("E:\\AHMADI-RO\\FaceRec\\C_Neural_Network\\input_image.txt", 3*20*20);

    int counter = 0;
    for(int i = 0; i < 3; i++) {
        for (j = 0; j < 20; j++) {
            for (int k = 0; k < 20 ; ++k) {
                *(*(*(data + i) + j)+ k) = ((*(data_pixels + counter))) ;
                 counter++;
            }
        }
    }

                                                    printf("%d\n", counter);
                                                    for(int i = 0; i < 3; i++) {
                                                        for (j = 0; j < 20; j++) {
                                                            for (int k = 0; k < 20 ; ++k) {

                                                                printf("%f, ", *(*(*(data + i) + j)+ k));
                                                            }
                                                            printf("\n");
                                                        }
                                                       printf("channel %d has been finished!!!\n\n\n\n\n", i+1);
                                                    }
//
    float Sample_Mean[3] = {151.8802,118.0312,100.9963};
//    for (int k = 0; k < 400 ; ++k) {
//        sum[0] += ((*(data_pixels + k))) ;
//        sum[1] += ((*(data_pixels + 400 +  k))) ;
//        sum[2] += ((*(data_pixels + 800 + k))) ;
//    }
//    sum[0] = sum[0]/400;
//    sum[1] = sum[1]/400;
//    sum[2] = sum[2]/400;
//    printf("the means of layers 1, 2, 3 are : %10f , %10f , %10f\n\n\n", sum[0], sum[1], sum[2]);
//
//    float RSS[3] = {0, 0, 0};
//    for (int k = 0; k < 400 ; ++k) {
//        RSS[0] += pow((*(data_pixels + k) - sum[0]), 2) ;
//        RSS[1] += pow((*(data_pixels + 400 +  k) - sum[1]), 2) ;
//        RSS[2] += pow((*(data_pixels + 800 + k) - sum[2]), 2) ;
//    }
//    RSS[0] = sqrt(RSS[0]/399);
//    RSS[1] = sqrt(RSS[1]/399);
//    RSS[2] = sqrt(RSS[2]/399);
//
//    printf("the standard deviation of layers 1, 2, 3 are : %10f , %10f , %10f\n\n\n", RSS[0], RSS[1], RSS[2]);


                                                    for(int i = 0; i < 3; i++) {
                                                        for (j = 0; j < 20; j++) {
                                                            for (int k = 0; k < 20 ; ++k) {
                                                                *(*(*(data + i) + j)+ k) = ( *(*(*(data + i) + j)+ k) - Sample_Mean[i] );
                                                                printf("%f, ", *(*(*(data + i) + j)+ k));
                                                            }
                                                            printf("\n");
                                                        }
                                                        printf("channel %d has been finished!!!\n\n\n\n\n", i+1);
                                                    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 * data's pixels reading check
 *
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////
////
////// fetching convolution layers weight

    int number_of_masks = 1;
    int mask_height, mask_width, mask_depth;
    mask_depth = mask_width = mask_height = 3;
    float **** masks = (float ****)malloc(sizeof(float ***) * number_of_masks);
    for (int m = 0; m <number_of_masks ; ++m) {
        masks[m] = (float ***)malloc(sizeof(float **) * mask_depth);
        for (int i = 0; i < mask_height; ++i) {
            masks[m][i] = (float **)malloc(sizeof(float *) * mask_height);
            for (int k = 0; k < mask_width; ++k) {
                masks[m][i][k] = (float *)malloc(sizeof(float) * mask_depth);
            }
        }
    }

    float * conv_weight = Weight_Reading("E:\\AHMADI-RO\\FaceRec\\C_Neural_Network\\conv_weights.txt", number_of_masks, mask_depth, mask_height, mask_width);

    counter = 0;
    for (int m = 0; m <1 ; ++m) {
        for (int i = 0; i < 3; ++i) {
            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < 3; ++l) {
                    *(*(*(*(masks + m) + i) + k) + l) = *(conv_weight + counter);
                    //printf(" %.10f \n",  *(*(*(*(masks + m) + i) + k) + l));
                    counter ++;
                }
            }
        }
    }


                                                           for (int m = 0; m <1 ; ++m) {
                                                                for (int i = 0; i < 3; ++i) {
                                                                    for (int k = 0; k < 3; ++k) {
                                                                        for (int l = 0; l < 3; ++l) {
                                                                            printf("%f, ", *(*(*(*(masks + m) + i) + k) + l));
                                                                        }
                                                                        printf("\n");
                                                                    }
                                                                    printf("conv weights for channel %d \n", i+1);
                                                                    printf("\n");
                                                                  }
                                                                printf("\n");
                                                             }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////*
//// *
//// * mask's pixels reading check
//// *
//// */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
////    //doing convolution

    float *** conv_output = (float ***) malloc(sizeof(float **) * number_of_masks);
    for (int k1 = 0; k1 < number_of_masks; ++k1) {
        conv_output[k1] = (float**)malloc(sizeof(float*) * 20);
        for (int i = 0; i < 20; ++i) {
            conv_output[k1][i] = (float*)malloc(sizeof(float) * 20);
        }
    }
    //float ***input, int input_height, int input_width, int input_depth, float **** mask, int mask_height, int mask_width, int mask_depth, int number_of_mask, float bias, int stride_x, int stride_y){
    conv_output = Convolutional_Layer_Builder(data, 20, 20, 3, masks, 3, 3, 3, 1, 1, 1, 1);

    printf("the output of convolution layer is : \n");

    for (int k1 = 0; k1 < 1; ++k1) {
        for (int i = 1; i < 19; ++i) {
            for (int j = 1; j < 19; ++j) {
                switch(k1){
                    case 0:
                        *(*(*(conv_output + k1) + i)+j) += -0.14783237874507904;
                        break;
                }
                printf("%f, ", *(*(*(conv_output + k1) + i)+j));
            }
            printf("\n");
        }
        printf("\n");
        printf("next outputtttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt\n");
   }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////*
//// *
//// * convolution check
//// *
//// */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
//////Relu activation
//
////    void ReLU_Layer(float ***input, int input_height, int input_width, int input_depth){
    ReLU_Layer(conv_output, 20, 20, 1);
                                                                                                                        printf("\n");
                                                                                                                        printf("the output of ReLU : \n");
                                                                                                                        for (int k1 = 0; k1 < 1; ++k1) {
                                                                                                                            for (int i = 1; i < 19; ++i) {
                                                                                                                                for (int j = 1; j < 19; ++j) {
                                                                                                                                    printf("%f, ", *(*(*(conv_output + k1) + i)+j));
                                                                                                                                }
                                                                                                                                printf("\n");
                                                                                                                            }
                                                                                                                            printf("\n");
                                                                                                                            printf("\n");
                                                                                                                            //printf("next outputtttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt\n");
                                                                                                                        }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*
// *
// * Relu check
// *
// */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
    float *** pooling_input = (float ***) malloc(sizeof(float **) * number_of_masks);
    for (int k1 = 0; k1 < number_of_masks; ++k1) {
        pooling_input[k1] = (float**)malloc(sizeof(float*) * 18);
        for (int i = 0; i < 18; ++i) {
            pooling_input[k1][i] = (float*)malloc(sizeof(float) * 18);
        }
    }
    printf("\n");
    printf("the input of Pooling : \n");
    for (int k1 = 0; k1 < 1; ++k1) {
        for (int i = 1; i < 19; ++i) {
            for (int j = 1; j < 19; ++j) {
                *(*(*(pooling_input + k1) + i-1)+j-1) = *(*(*(conv_output + k1) + i)+j);
//                printf("%f, ", *(*(*(pooling_input + k1) + i-1)+j-1));
            }
//            printf("\n");
        }
        printf("\n");
        printf("\n");

    }
    float *** pooling_output = (float ***) malloc(sizeof(float **) * number_of_masks);
    for (int k1 = 0; k1 < number_of_masks; ++k1) {
        pooling_output[k1] = (float**)malloc(sizeof(float*) * 9);
        for (int i = 0; i < 9; ++i) {
            pooling_output[k1][i] = (float*)malloc(sizeof(float) * 9);
        }
    }


 //Max_Pooling(float ***input, int input_height, int input_width, int input_depth, int stride_x, int stride_y, int sliding_windows_height, int sliding_windows_width){
    pooling_output = Max_Pooling(pooling_input, 18, 18, 1, 2, 2, 2, 2);
                                                                                                                            printf("\n");
                                                                                                                            printf("the output of Pooling : \n");
                                                                                                                            for (int k1 = 0; k1 < 1; ++k1) {
                                                                                                                                for (int i = 0; i < 9; ++i) {
                                                                                                                                    for (int j = 0; j < 9; ++j) {
                                                                                                                                        printf("%f, ", *(*(*(pooling_output + k1) + i)+j));
                                                                                                                                    }
                                                                                                                                    printf("\n");
                                                                                                                                }
                                                                                                                                printf("\n");
                                                                                                                            }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*
// *
// * Max-Pooling check
// *
// */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//


// the output of max pooling layer should be transpose before injecting it to FC


    float * fc_weights = (float *)malloc(sizeof(float) * 2*9*9);
    fc_weights =  Weight_Reading("E:\\AHMADI-RO\\FaceRec\\C_Neural_Network\\fc_weights.txt", 1, 2, 9, 9);

    float ** FC_Weights = (float**) malloc(sizeof(float *) * 2);
    for (int n = 0; n < 2; ++n) {
        FC_Weights[n] = (float*)malloc(sizeof(float) * 9*9);
    }

    counter = 0;
    for (int l1 = 0; l1 < 2; ++l1) {
        for (int i1 = 0; i1 < 9*9; ++i1) {
            *(*(FC_Weights + l1) + i1) = *(fc_weights + counter);
            printf("%10f, ", *(*(FC_Weights + l1) + i1));
            counter++;
        }
        printf("the weights of %d \n\n", l1 + 1);
    }

//  //  float *Fully_Connected_Builder(float *input, int depth, int nnumber_of_output_neurons, float **weights){
    float  *fully_connected;
    counter = 0;
    float * fc_input = (float *)malloc(sizeof(float) * 9*9);
    for (int k1 = 0; k1 < 1; ++k1) {
        for (int i = 0; i < 9; ++i) {
            for (int k = 0; k < 9; ++k) {
                *(fc_input + counter) = *(*(*(pooling_output + k1) + i) + k);
                //printf("%10f, ", *(fc_input + counter));
                counter++;
            }
        }
    }

    counter = 0;
    float * fc_input_transpose = (float *)malloc(sizeof(float) * 9*9);
    for (int m1 = 0; m1 < 9; ++m1) {
        for (int i = 0; i < 81; i+=9) {
            *(fc_input_transpose + counter) = *(fc_input + m1+i);
            printf("%10f, " , *(fc_input_transpose + counter));
            counter++;
        }

    }
    printf("\n\n\n");

    float sum1, sum2;
    sum1 = sum2 = 0;
    for (int n1 = 0; n1 < 81; ++n1) {
        sum1 +=  *(*(FC_Weights + 0) + n1) * *(fc_input_transpose + n1);
        sum2 +=  *(*(FC_Weights + 1) + n1) * *(fc_input_transpose + n1);
    }

    printf("\n %10f ,  %10f \n\n\n  %f", sum1+0.1858278512954712
            , sum2-0.18582794070243835);

//fully_connected = Fully_Connected_Builder(fc_input_transpose, 9*9, 2, FC_Weights);

//printf("\n %10f ,  %10f \n\n\n  %f", *(fully_connected+0)+0.1858278512954712
//        , *(fully_connected+1)-0.18582794070243835);
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *
// * FC check
// *
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//


//    printf("\n\n\n\n");
//    counter = 0;
//    double* flatten = (float *)malloc(sizeof(float) * 4*75*75);
//    flatten = Softmax_Layer(soft, 4*75*75);
//                                                                                                                        for (int k1 = 0; k1 < 4*75*75; ++k1) {
//                                                                                                                            printf("%f, ",  *(flatten + k1));



    /* init_window();
     set_renderer();

     int begining_of_time = SDL_GetTicks();
     const double FPS = 30;
     while (flag) {
         int start_ticks = SDL_GetTicks();
         SDL_SetRenderDrawColor(renderer, 120, 60, 80, 255);
         SDL_RenderClear(renderer);


         renderer_present();
         draw_renderer();
         while (SDL_GetTicks() - start_ticks < 1000 / FPS){
             SDL_Delay(50);
         }

     }
     destroy_window();*/
//    printf("\n");
//    for (int l1 = 0; l1 < 3*150*150; ++l1) {
//        printf("0,");
//    }
}
