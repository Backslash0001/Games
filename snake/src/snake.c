#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

Snake snake_(int x, int y, Vector2 dir, int size) {
    Snake snake;
    snake.head = malloc(sizeof(Block));
    snake.head->x = x;
    snake.head->y = y;
    snake.dir = dir;

    Block *current = snake.head;
    for(int i=1; i<size; i++){
        Block *new = malloc(sizeof(Block));
        new->next = NULL;
        new->x = x - i*dir.x;
        new->y = y - i*dir.y;

        current->next = new;
        current = current->next;
    }

    return snake;
}

void move(Snake *snake, Vector2 dir){
    Block* new = malloc(sizeof(Block));
    new->x = snake->head->x + snake->dir.x;
    new->y = snake->head->y + snake->dir.y;
    new->next = snake->head;

    snake->head = new;
    snake->dir = dir;

    Block *current = snake->head;

    while(current->next->next != NULL) current = current->next;
    current->next=NULL;
}


int isEating(Snake snake, Fruit fruit) {
    return (snake.head->x+snake.dir.x == fruit.x) && (snake.head->y+snake.dir.y == fruit.y);
}

int isDying(Snake snake){
    if(snake.head->x+snake.dir.x < 0 || snake.head->x+snake.dir.x > 20) return 1;
    if(snake.head->y+snake.dir.y < 0 || snake.head->y+snake.dir.y > 20) return 1;

    return 0;
}


void plot(Snake snake) {
    Block *current = snake.head;

    while(current != NULL) {
        printf("(%d, %d) ", current->x, current->y);

        current = current->next;
    }
    printf("\n");
}