//
// Created by Css on 2/26/2021.
//

#include "File_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int weight_counter = 0;
int  fc_weight_counter = 0;
int read_mode;
int length = 23;

float weight_maker(char weight[], int l){
    float  w = 0;
    float fw = 0;
    int len = 0;
    bool isNegative = false;
    bool beforeDot = true;
   // printf("\n");
    for (int i = 0; i < l; ++i) {
      //  printf("%c", weight[i]);
        if(weight[i] == '-'){
            isNegative = true;
            continue;
        }
        else if(beforeDot && weight[i] != '.'){
            continue;
        }
        else if(weight[i] == '.'){
            beforeDot = false;
            continue;
        }
        else if(!beforeDot){
            len ++;
            w = (w*10) + ((weight[i]-48));
        }
    }

    int tw = w;
    if(tw == 0){
        len = 1;
    }
    else{
        //printf(".............");
        fw = w;
        for (int j = 0; j < len; ++j) {
            fw /= 10;
        }
        //printf("............. w = %f ............fw = %f", w, fw);
    }
    if(isNegative){
        fw *= -1;
    }
//    printf("this id fw: %f  ----", fw);
    return fw;
}



int Integer_maker(char a[], int k){
    int tmp = 0;
    for (int i = 0; i < k; ++i) {
        tmp = ((tmp*10) + (a[i] - 48));
    }

    return tmp;
}

float* Integer_Input_Reading(char file_name[], int length){
    float *input_pixels = (float*) malloc(sizeof(float) * length);
    int counter = 0;
    char ch;
    FILE *fp;

    fp = fopen(file_name, "r"); // read mode

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("The contents of %s file are:\n", file_name);
    int tmp[length];

    int i = 0;
    while((ch = fgetc(fp)) != EOF){
        if(ch == '\n' || ch == ' '){
            continue;
        }
        else if(ch == ','){
           // tmp[i] = '$';
           int x = 0;
            for (int k = 0; k < i; ++k) {
                x = x*10 + tmp[k];
            }
            *(input_pixels + counter) = x;
            //printf("x : %d\n", x);
            counter++;
            i = 0;
            continue;
        }

        tmp[i] = ch - 48;
        i++;
    }


    fclose(fp);
    return input_pixels;

}





 float * Weight_Reading(char file_name[], int number_of_masks, int mask_depth, int mask_height, int mask_width){
    weight_counter = 0;
     float * conv_weights = (double *)malloc(sizeof(double) * number_of_masks*mask_depth*mask_height*mask_width);

    char ch;
    FILE *fp;

    fp = fopen(file_name, "r"); // read mode

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    printf("The contents of %s file are:\n", file_name);
    char tmp[length];

    int i = 0;
    int counter = 0;
    while((ch = fgetc(fp)) != EOF){
        if(ch == '\n' || ch == ' '){
            continue;
        }
        else if(ch == ','){
            float tmp_weight = weight_maker(tmp, i);
            *(conv_weights + counter) = tmp_weight;
            //printf("weight %d : %f\n", counter, tmp_weight );
            counter++;
            i = 0;
            continue;
        }
        tmp[i] = ch;
        i++;
    }


    fclose(fp);

    return conv_weights;



}













