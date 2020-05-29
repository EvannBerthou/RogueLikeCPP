#include "fonts.h"

TTF_Font *create_font(const char* font_name, int size) {
    TTF_Font *font = TTF_OpenFont(font_name, size);
    if (font == NULL){
        printf("error while loading font: %s\n", TTF_GetError());
        exit(1);
    }
    return font;
}

SDL_Texture *font_as_texture(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

int render_text(SDL_Renderer *renderer, TTF_Font *font,
                const char* text, vec2i pos, SDL_Color color) {

    int w,h;
    SDL_Texture *texture = font_as_texture(renderer, font, text, color);
    SDL_QueryTexture(texture, NULL, NULL, &w,&h);
    SDL_Rect dst = {(int)pos.x, (int)pos.y, w,h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
    return 1;
}
