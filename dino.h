#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include "LTexture.h"
class Dino {
public:
	int ground = 500;
	double jump_speed = 0.5; //chịu khó chỉnh tay nhé, vì hiện tại tốc độ rơi của dino chưa tính tới việc tăng hay giảm gì cả 
	double fall_speed = 0.5;

	Dino();

	void handleEvent(SDL_Event& e);

	void move();

	void render(SDL_Rect* currentClip, SDL_Renderer* gRenderer,LTexture characterTexture);


	double getposX();

	double getposY();

	int getStatus();

private:
	bool jumping;
	bool falling;

	double posX;// nhớ là double đấy, k chỉnh sang int đâu. Lưu ý: khi dùng ltexture::render(int x,int y,...) thif convert đám posX posY sang int. kiểu x = int(x) ý:D 
	double posY;

	double deltaH;

	int timeJump; //số lần nhảy 
	double maxH; //độ cao cao nhất chạm tới 

	int status;
	
};