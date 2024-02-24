#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "snake.h"
#include "texture.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void render(SDL_Renderer *renderer, Snake snake){
    SDL_Rect src = {0, 0, 48, 48};
    SDL_Rect rect;
    Block* current = snake.head;
    char path[100];

    int i=0;
    while(current->next != NULL) {
        strcpy(path, "snake/assets/");

        // Snake head
        if(i==0) {
            rect.x = current->x * BLOCK_SIZE;
            rect.y = current->y * BLOCK_SIZE;
            rect.w = BLOCK_SIZE;
            rect.h = BLOCK_SIZE;

            strcat(path, headTexturePath(snake.dir));
            i++;
        }
        // snake body
        else {
            rect.x = current->next->x * BLOCK_SIZE;
            rect.y = current->next->y * BLOCK_SIZE;
            rect.w = BLOCK_SIZE;
            rect.h = BLOCK_SIZE;

            if(current->next->next != NULL) {
                Vector2 vect1 = {current->x-current->next->x, current->y-current->next->y};
                Vector2 vect2 = {current->next->next->x-current->next->x, current->next->next->y-current->next->y};
                strcat(path, bodyTexturePath(vect1, vect2));
            }
            else {
                Vector2 vect = {current->x-current->next->x, current->y-current->next->y};
                strcat(path, tailTexturePath(vect));
            }

            current = current->next;
        }        
        printf("\n");

        SDL_Surface* image_surface = IMG_Load(path);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image_surface);
        
        SDL_RenderCopy(renderer, texture, &src, &rect);
    }

}

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if(SDL_Init(SDL_INIT_VIDEO)!= 0){
        printf("SDL_InitError: %s", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow(
        "Simple SDL Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 800,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    
    
    if (window == NULL) {
        printf("SDL_CreateWindowError: %s\n", SDL_GetError());
        exit(1);
    } 
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL_CreateRendererError: %s\n", SDL_GetError());
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur lors de l'initialisation de SDL_image : %s\n", IMG_GetError());
        SDL_Quit();
        return -1;
    }


    Vector2 dir = {1, 0};
    Snake snake = snake_(5, 5, dir, 4);
    int quit = 0;
    SDL_Event e;

    SDL_Rect rect;


    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = 1;
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_LEFT:
                        dir.x = -1;
                        dir.y = 0;
                        break;
                    case SDLK_RIGHT:
                        dir.x = 1;
                        dir.y = 0;
                        break;
                    case SDLK_UP:
                        dir.x = 0;
                        dir.y = -1;
                        break;
                    case SDLK_DOWN:
                        dir.x = 0;
                        dir.y = 1;
                        break;
                }
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 88, 138, 53, 255);
        SDL_RenderClear(renderer);

        move(&snake, dir);
        render(renderer, snake);
        // rect.x = snake.head->x;
        // rect.y = snake.head->y;
        // rect.w = BLOCK_SIZE;
        // rect.h = BLOCK_SIZE;

        // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        // SDL_RenderFillRect(renderer, &rect);

        //plot(snake);

        SDL_RenderPresent(renderer);
        SDL_Delay(200);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
