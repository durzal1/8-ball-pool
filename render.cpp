#include "render.h"

// draws circle
void render::drawCircle(SDL_Renderer* renderer, ball ball) {
	// sets draw color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	auto points = ball.getCir();
	// plots points based on circumference vector
	for (int i = 0; i < 360; i++) {
		SDL_RenderDrawPoint(renderer, points[i][0], points[i][1]);
	}
}
