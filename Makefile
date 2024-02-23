CC := gcc
CFLAGS := `sdl2-config --cflags --libs` #-Wall -Wextra


all: snake

snake:
	@$(CC) $@/src/*.c -o $@/$@ $(CFLAGS) 



.PHONY: snake all