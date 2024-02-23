#include <SDL2/SDL.h>
#include "snake.h"
#include <stdlib.h>
#include <stdio.h>

void render(SDL_Renderer *renderer, Snake snake){
    Block* current = snake.head;

    SDL_Rect rect;

    while(current != NULL) {
        rect.x = current->x * BLOCK_SIZE;
        rect.y = current->y * BLOCK_SIZE;
        rect.w = BLOCK_SIZE;
        rect.h = BLOCK_SIZE;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        current = current->next;
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


    Vector2 dir = {1, 0};
    Snake snake = snake_(5, 5, dir, 4);
    int quit = 0;
    SDL_Event e;

    SDL_Rect rect;


    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = 1;
            if(e.type == SDL_KEYDOWN){
                printf("%s", e.key);
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);

        render(renderer, snake);
        // rect.x = snake.head->x;
        // rect.y = snake.head->y;
        // rect.w = BLOCK_SIZE;
        // rect.h = BLOCK_SIZE;

        // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        // SDL_RenderFillRect(renderer, &rect);

        plot(snake);
        move(&snake, dir);


        SDL_RenderPresent(renderer);
        SDL_Delay(400);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
