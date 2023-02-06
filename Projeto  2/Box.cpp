#pragma once

#include "Box.h"

Box::Box(int x, int y){
	Update(x, y, false);
}

Box::~Box() {
	cout << "calling box destructor" << endl;
}

void Box::Update(int x, int y, bool complete) {
	pos.x = x;
	pos.y = y;

	rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

	bool inGoal = complete;
}

Vec2 Box::GetPos() {
	return pos;
}

SDL_Rect* Box::GetRect() {
	return &rect;
}

bool Box::GetInGoal() {
	return inGoal;
}