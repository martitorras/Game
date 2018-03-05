#include <iostream>
#include "../SDL/include/SDL.h"
#include "../SDL_Image/include/SDL_image.h"
#pragma comment(lib, "../SDL/x86/SDL2.lib")
#pragma comment(lib, "../SDL/x86/SDL2main.lib")
#pragma comment(lib, "../SDL_Image/libx86/SDL2_image.lib")

using namespace std;

int main(int argc, char* argv[]) {

	SDL_Window* window;
	SDL_Renderer* renderer;
	IMG_Init(IMG_INIT_PNG);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {//inicialitza SDL
		printf("SDL coud not be initialized! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("La meva finestra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	bool exit = false;//pel bucle
	int x = 440, y = 260, a = 525, b = 350;
	
	bool up = false, down = false, right = false, left = false, shooting = false, is_flying = false;

	SDL_Event e;//Qualsevol input del teclat, ratolí... es guarda aqui
	
	while (!exit) {
		while (SDL_PollEvent(&e) != 0) {//quan rep un input, ho guarda a l'adreça de mem de e
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) exit = true;
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_UP) up = true;// y -= 5;
				if (e.key.keysym.sym == SDLK_DOWN) down = true;// y += 5;
				if (e.key.keysym.sym == SDLK_RIGHT) right = true; // x += 5;
				if (e.key.keysym.sym == SDLK_LEFT) left = true; // x -= 5;
				if (e.key.keysym.sym == SDLK_SPACE) {
					shooting = true;
					is_flying = true;
				}
			}
			else if (e.type == SDL_KEYUP) {
				if (e.key.keysym.sym == SDLK_UP) up = false;// y -= 5;
				if (e.key.keysym.sym == SDLK_DOWN) down = false;// y += 5;
				if (e.key.keysym.sym == SDLK_RIGHT) right = false; // x += 5;
				if (e.key.keysym.sym == SDLK_LEFT) left = false; // x -= 5;
				if (e.key.keysym.sym == SDLK_SPACE) shooting = false;
			}
		}
		if (up && y > 0) y -= 1;
		if (down && y < 522) y += 1;
		if (right && x < 880) x += 1;
		if (left && x > 0) x -= 1;
		if (!shooting && !is_flying) {
			a = x + 85;
			b = y + 90;
		}
		else {
			if (a < 1200) a += 2;
			else {
				a = x + 85;
				b = y + 90;
				is_flying = false;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_Rect shot = { a, b, 50, 15 };
		SDL_RenderFillRect(renderer, &shot);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_Rect rect = { x, y, 200, 200 };
		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}