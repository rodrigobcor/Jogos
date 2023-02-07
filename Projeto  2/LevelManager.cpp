#pragma once

#include "LevelManager.h"

void LevelManager::LoadLevel() {
	int rowCount = 0;
	int colCount = 0;

	string path = "Levels/level" + to_string(currentLevel) + ".txt";

	levelFile.open(path);
	if (levelFile.is_open()) {
		char inChar;
		while (levelFile.get(inChar)) {
			if (inChar == '\n') {
				colCount = 0;
				rowCount++;
			}
			else {
				levelMap[colCount][rowCount] = inChar;
				colCount++;
			}
		}
	}

	levelFile.close();
}

void LevelManager::UpdateLevel() {
	if (currentLevel == 3) {
		currentLevel = 3;
	}
	else {
		currentLevel++;
	}
}

void LevelManager::showText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color) {
	levelTextSurface = TTF_RenderText_Solid(font, to_string(currentLevel).c_str(), color);

	levelTextRect.x = 5;
	levelTextRect.y = 5;
	levelTextRect.w = levelTextSurface->w;
	levelTextRect.h = levelTextSurface->h;

	levelTextTexture = SDL_CreateTextureFromSurface(renderer, levelTextSurface);

	SDL_RenderCopy(renderer, levelTextTexture, NULL, &levelTextRect);
}

void LevelManager::gameOver(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color) {
	gameOverSurface = TTF_RenderText_Solid(font, to_string(currentLevel).c_str(), color);

	gameOverRect.x = levelTextSurface->w / 2;
	gameOverRect.y = levelTextSurface->h / 2;
	gameOverRect.w = levelTextSurface->w;
	gameOverRect.h = levelTextSurface->h;

	gameOverTexture = SDL_CreateTextureFromSurface(renderer, levelTextSurface);

	SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
}

int LevelManager::getCurrentLevel() {
	return currentLevel;
}
