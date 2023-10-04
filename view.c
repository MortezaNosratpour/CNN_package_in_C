////
//// Created by Css on 2/19/2021.
////
//#include <stdio.h>
//#include <stdbool.h>
//#include <stdlib.h>
//#include <math.h>
//#include <SDL.h>
//#include <SDL2_gfxPrimitives.h>
//
//#include "view.h"
//
//SDL_Window* window;
//SDL_Renderer* renderer;
//SDL_Surface* screen;
//
//void init_window(void){
//    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
//    window = SDL_CreateWindow("Ulter_Tank!!!", 400, 80, 677, 718, SDL_WINDOW_OPENGL);
//
//}
//void destroy_window(void){
//
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//}
//void set_renderer(void){
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//}
//void draw_renderer(void){
//    SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
//    SDL_RenderClear(renderer);
//
//}
//void renderer_present(void){
//    SDL_RenderPresent(renderer);
//}
