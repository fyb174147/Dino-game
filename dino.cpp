#include "dino.h"

Dino::Dino() {
	jumping = false;
	falling = false;

	posX = 100;
	posY = ground;

	deltaH = 0;

	timeJump = 0; 
	maxH = 200; 

	status = 0;// 0 là chạy hoặc nhảy , 1 là cúi đầu và 2 là hẹo nhé 
}

void Dino::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_SPACE) {
		if (timeJump < 2 and !jumping) {
			jumping = true;
			deltaH = 0;
			timeJump++;
		}
	}
	if (e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_s) {
		if (status != 2) status = 1;
	}
	if (e.type == SDL_KEYUP and status != 2) {
		status = 0;
	}
	if (e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_0) {
		status = 2;
	}
	

}

void Dino::move() {
	if (jumping) {
		posY -= jump_speed;
		deltaH += jump_speed;
		if (deltaH >= maxH) {
			jumping = false;
			falling = true;
		}
		
	}
	else if (falling) {

		posY += fall_speed;
		if (posY >= ground ) {
			falling = false;
			posY = ground;
		}
	}
	if (posY == ground) {
		timeJump = 0;
		deltaH = 0;
	}
}

void Dino::render(SDL_Rect* clips, SDL_Renderer* gRenderer,LTexture characterTexture) {

	characterTexture.Render(posX, posY, gRenderer, clips);
}


double Dino::getposX() {
	return posX;
}
double Dino::getposY() {
	return posY;
}

int Dino::getStatus() {
	return status;
}