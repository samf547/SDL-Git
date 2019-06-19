#pragma once
#include<iostream>
#include<SDL2_ttf/SDL_ttf.h>
class Font {
	private:
		int fontSize;
		TTF_Font *fontRenderer;
		std::string filename;
	public:
		Font(int size = 20, std::string filename = "font.ttf") {
			this->filename = "/resources/" + filename;
			fontSize = size;
			fontRenderer = TTF_OpenFont(this->filename.c_str(), size);
			if (fontRenderer == NULL) {
				printf("Failed to load font\n");
			}
		}
		
		~Font() {
			std::cout << "FONT -> " << this->fontRenderer << std::endl;
			if (this->fontRenderer != NULL) {
				TTF_CloseFont(this->fontRenderer);
			}
			fontRenderer = NULL;
		}
		
		Font& operator=(const Font& font) {
			std::cout << "OPERATOR= E" << std::endl;
			this->fontSize = font.fontSize;
			std::cout << "BEFORE -> " << this->fontRenderer << std::endl;
			std::cout << "OTHERS -> " << font.fontRenderer << std::endl;
			if (this->fontRenderer != NULL) {
				TTF_CloseFont(fontRenderer);
				fontRenderer = NULL;
			}
			
			this->fontRenderer = TTF_OpenFont(font.filename.c_str(), font.fontSize);
			std::cout << "AFTER -> " << this->fontRenderer << std::endl;
			return *this;
		}
		
		void drawTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect rect, 
								SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, 
								SDL_RendererFlip flip = SDL_FLIP_NONE) {
			 SDL_RenderCopyEx(renderer, texture, clip, &rect, angle, center, flip);
		}
		
		void renderText(int x, int y, std::string text, SDL_Renderer *renderer, SDL_Color color, 
								SDL_Rect* clip = NULL, double angle = 0.0, 
								SDL_Point* center = NULL, 
								SDL_RendererFlip flip = SDL_FLIP_NONE) {
			SDL_Surface *surface = TTF_RenderText_Blended(fontRenderer, text.c_str(), color);
			if (!(surface == NULL)) {
				SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
				if (!(texture == NULL)) {
					SDL_FreeSurface(surface);
					SDL_Rect newRect = {x, y, surface->w, surface->h};
					drawTexture(renderer, texture, newRect, clip, angle, center, flip);
					SDL_DestroyTexture(texture);
				}
			}
		}
		
		void renderTextWrapped(int x, int y, std::string text, SDL_Renderer *renderer, SDL_Color color, int maxWidth,
								SDL_Rect* clip = NULL, double angle = 0.0, 
								SDL_Point* center = NULL, 
								SDL_RendererFlip flip = SDL_FLIP_NONE) {
			SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(fontRenderer, text.c_str(), color, maxWidth);
			if (surface != NULL) {
				SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
				if (!(texture == NULL)) {
					SDL_FreeSurface(surface);
					SDL_Rect newRect = {x, y, surface->w, surface->h};
					drawTexture(renderer, texture, newRect, clip, angle, center, flip);
					SDL_DestroyTexture(texture);
				}
			}
		}
};
