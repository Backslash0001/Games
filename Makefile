CC := gcc
CFLAGS := $(shell sdl2-config --cflags --libs) #-Wall -Wextra
LDFLAGS := $(shell sdl2-config --libs) -lSDL2_image


all: snake

snake:
	@$(CC) $@/src/*.c -o $@/$@ $(CFLAGS) $(LDFLAGS)


.PHONY: snake all