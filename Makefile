PKGS=sdl2 SDL2_ttf SDL2_image
CXXFLAGS=-Wall -Wextra -g
LIBS=$(shell pkg-config --libs $(PKGS)) -lm

build:
	g++ $(CXXFLAGS) -o dungeon $(wildcard src/*.cpp) -Iincludes $(LIBS)
