#ifndef SNAKE_H
#define SNAKE_H
#define BLOCK_SIZE 50

typedef struct block {
    int x, y;
    struct block* next;
} Block;

typedef struct vector {
    int x;
    int y;
} Vector2;

typedef struct snake {
    int x, y;
    Vector2 dir;
    Block *head;
} Snake;

typedef struct fruit {
    int x;
    int y;
} Fruit;

Snake snake_(int x, int y, Vector2 dir, int size);
void move(Snake *snake, Vector2 dir);
void plot(Snake);

#endif