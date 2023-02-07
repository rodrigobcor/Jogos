#pragma once

#include "Utils.h"
#include <fstream>
#include <string>

class LevelManager
{
public:
	void LoadLevel();
	void UpdateLevel();
	char levelMap[TILE_ROWS][TILE_COLS] = { '0' };
	int getCurrentLevel();
	void showText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);
	void gameOver(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);

private:
	ifstream levelFile;
	int currentLevel = 1;
	SDL_Rect levelTextRect;
	SDL_Surface* levelTextSurface = nullptr;
	SDL_Texture* levelTextTexture = nullptr;
	SDL_Rect gameOverRect;
	SDL_Surface* gameOverSurface = nullptr;
	SDL_Texture* gameOverTexture = nullptr;
};
