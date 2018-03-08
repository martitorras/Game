#include <iostream>
//#include <time.h>
#include "../SDL/include/SDL.h"
#include "../SDL_Image/include/SDL_image.h"
#include "../SDL_Mixer/include/SDL_mixer.h"
#pragma comment(lib, "../SDL/x86/SDL2.lib")
#pragma comment(lib, "../SDL/x86/SDL2main.lib")
#pragma comment(lib, "../SDL_Image/libx86/SDL2_image.lib")
#pragma comment(lib, "../SDL_Mixer/libx86/SDL2_mixer.lib")

using namespace std;

//void hit(int a, int b, int c, int d);

typedef struct {
	int j, i;
	bool shot;
}enemy;

int main(int argc, char* argv[]) {

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* image;
	SDL_Surface* image2;
	SDL_Surface* shot;
	
	
	
	//srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {//inicialitza SDL
		printf("SDL coud not be initialized! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}
	if (IMG_Init(IMG_INIT_PNG) < 0) {
		printf("IMG_INIT: %s\n", IMG_GetError());
		exit(2);
	}

	if (Mix_Init(MIX_INIT_OGG) < 0) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
	
	window = SDL_CreateWindow("Prova de joc amb SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	image = IMG_Load("titled.png");
	if (!image) {
		printf("IMG_Load: %s\n", IMG_GetError());
		system("pause");
		exit(1);
	}
	image2 = IMG_Load("space.png");
	if (!image) {
		printf("IMG_Load: %s\n", IMG_GetError());
		system("pause");
		exit(1);
	}
	shot = IMG_Load("shot.png");
	if (!image) {
		printf("IMG_Load: %s\n", IMG_GetError());
		system("pause");
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, image2);
	SDL_Texture* shoot = SDL_CreateTextureFromSurface(renderer, shot);
	bool exit = false;//pel bucle
	int x = 440, y = 260, a = 525, b = 350;
	enemy enemies[3];
	enemies[0].i = 1080;
	enemies[0].j = 250;
	bool up = false, down = false, right = false, left = false, shooting = false, is_flying = false;

	SDL_Event e;//Qualsevol input del teclat, ratolí... es guarda aqui
	
	while (!exit) {
		while (SDL_PollEvent(&e) != 0) {//quan rep un input, ho guarda a l'adreça de mem de e
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) exit = true;
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_UP) up = true;
				if (e.key.keysym.sym == SDLK_DOWN) down = true;
				if (e.key.keysym.sym == SDLK_RIGHT) right = true;
				if (e.key.keysym.sym == SDLK_LEFT) left = true;
				if (e.key.keysym.sym == SDLK_SPACE) {
					shooting = true;
					is_flying = true;
				}
			}
			else if (e.type == SDL_KEYUP) {
				if (e.key.keysym.sym == SDLK_UP) up = false;
				if (e.key.keysym.sym == SDLK_DOWN) down = false;
				if (e.key.keysym.sym == SDLK_RIGHT) right = false;
				if (e.key.keysym.sym == SDLK_LEFT) left = false;
				if (e.key.keysym.sym == SDLK_SPACE) shooting = false;
			}
		}
		if (up && y > -70) y -= 1;
		if (down && y < 592) y += 1;
		if (right && x < 950) x += 1;
		if (left && x > -70) x -= 1;
		if (!shooting && !is_flying) {
			a = x + 85;
			b = y + 100;
		}
		else {
			if (a < 1200) a += 2;
			else {
				a = x + 85;
				b = y + 100;
				is_flying = false;
			}
		}
		--enemies[0].i;
		if (enemies[0].i < -150) enemies[0].i = 1080;
			
		SDL_RenderClear(renderer);
		SDL_Rect target = { 0,0, 1080, 720 };
		//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
		SDL_RenderCopy(renderer, background, NULL, &target);
		
		if (is_flying) {
			SDL_Rect shot = { a, b, 80, 10 };
			//SDL_RenderFillRect(renderer, &shot);
			SDL_RenderCopy(renderer, shoot, NULL, &shot);
		}
		//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_Rect rect = { x, y, 200, 200 };
		//SDL_RenderFillRect(renderer, &rect);
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_Rect foe = { enemies[0].i, enemies[0].j, 150, 150 };
		SDL_RenderFillRect(renderer, &foe);
		SDL_RenderPresent(renderer);
		//hit(x, y, enemies[0].i, enemies[0].j);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}

/*void hit(int a, int b, int c, int d) {
	if (a < c + 150 && a > c && b < d + 150 && b > d) {
		exit(1);
		system("pause");
		exit(1);
	}
}*/