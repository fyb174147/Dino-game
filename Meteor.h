#include "Included.h"
#include "LTexture.h"
using namespace std;

class Meteor {
    public:
        Meteor();
        ~Meteor();
        void Free();
        bool LoadFromFile(SDL_Renderer *_gRenderer);
        void Render();
        void Move();
        void SetAct(bool a);
        bool Success();
        bool HalfSuccess();
    private:
        int x = 1600;
        int y = -360;
        int frame1 = 0,frame2 = 0;
        bool act = true;
        SDL_Renderer* gRenderer = NULL;
        SDL_Texture* meo_tex = NULL;
        LTexture nuclear;
        SDL_Rect action[5];
};

Meteor::Meteor() {
    x = 1600;
    y = -360;
    frame1 = frame2 = 0;
    act = true;
    gRenderer = NULL;
    meo_tex = NULL;
}

Meteor::~Meteor() {
	Free();
}

void Meteor::Free() {
    SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyTexture(meo_tex);
	meo_tex = NULL;
}

bool Meteor::LoadFromFile(SDL_Renderer *_gRenderer) {
    bool Success = true;
    gRenderer = _gRenderer;
	SDL_Surface* tmpSurface = IMG_Load("image/meteor.png");
	if (tmpSurface == NULL) {
		std::cout << "cannot load surface Meteor" << std::endl;
		Success = false;
	}
	meo_tex = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
	if (meo_tex == NULL) {
		std::cout << "cannot convert meo_tex from surface" << std::endl;
		Success = false;
	}
	if (!nuclear.LoadFromFile("image/boom.png", gRenderer)) {
		std::cout << "cannot open boom img" << std::endl;
		Success = false;
	}
	for (int i = 0; i < 5; i++) {
		action[i].x = 900 * i;
		action[i].y = 0;
		action[i].w = 900;
		action[i].h = 900;
	}
	SDL_FreeSurface(tmpSurface);
	return Success;
}

void Meteor::Move() {
	if(x > 762 and act == true) frame1+=2;
	if (x == 762 and act == true) frame2++;
	if (frame1 % 2 == 0 and x > 762 and act == true) {
		x--;
		y = -x + 1240;
	}
}
void Meteor::Render() {
	if (x > 762) {
		SDL_Rect meo_rect = { x,y,150,150 };
		SDL_RenderCopy(gRenderer, meo_tex, NULL, &meo_rect);
	}
	if (x == 762) {
		nuclear.Render(350, -300, gRenderer, &action[frame2 / 50]);
	}
}
bool Meteor::Success() {
	if (frame2 >= 250) return true;
	else return false;
}
void Meteor::SetAct(bool a) {
	act = a;
}
bool Meteor::HalfSuccess() {
	if (x == 762) {
		return true;
	}
	else return false;
}
