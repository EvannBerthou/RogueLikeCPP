#ifndef FONTS_H
#define FONTS_H

#include <SDL2/SDL_ttf.h>
#include "vec2.h"

TTF_Font *create_font(const char* font_name, int size);
SDL_Texture *font_as_texture(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color);
int render_text(SDL_Renderer *renderer, TTF_Font *font,
                const char* text, vec2i pos, SDL_Color color);

#endif

