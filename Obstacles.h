#include "LTexture.h"
using namespace std;

enum ObstacleType {
    CACTUS,
    BIRD,
    TOTAL_OBSTACLE_TYPE
};

class Obstacle {
    public:
        Obstacle(int _type);
        ~Obstacle();
        void Free();
        bool LoadFromFile(string path, SDL_Renderer *gRenderer);
        void Move(int speed);
        void Render(SDL_Renderer *gRenderer, SDL_Rect *clip);
        int GetType();
        int GetXPos();
        int GetYPos();
        int GetWidth();
        int GetHeight();
    private:
        int xPos;
        int yPos;
        int width;
        int height;
        int type;
        SDL_Texture *ObstacleTexture;
};

Obstacle::Obstacle(int _type) {
    xPos = 0;
    yPos = 0;
    width = 0;
    height = 0;
    type = 0;
    if (_type == CACTUS) {
        type = _type;
        xPos = 400;
        yPos = 450;
        width = 50;
        height = 50;
    }
    else if (_type == BIRD) {
        type = _type;
        xPos = 1200;
        yPos = 450;
        width = 50;
        height = 50;
    }
    ObstacleTexture = NULL;
}

Obstacle::~Obstacle() {
    Free();
}

void Obstacle::Free() {
    if (ObstacleTexture == NULL) return;
    xPos = 0;
    yPos = 0;
    width = 0;
    height = 0;
    type = 0;
    ObstacleTexture = NULL;
}

bool Obstacle::LoadFromFile(string path, SDL_Renderer *gRenderer) {
    SDL_Surface *loadSurface = IMG_Load(path.c_str());
    if (loadSurface == NULL) {
        cout << "Load image " << path << " error: " << IMG_GetError() << '\n';
    }
    else {
        SDL_Texture *loadTexture = SDL_CreateTextureFromSurface(gRenderer, loadSurface);
        if (loadTexture == NULL) {
            cout << "Create texture from surface " << path << " error: " << SDL_GetError() << '\n';
        }
        else {
            width = loadSurface -> w;
            height = loadSurface -> h;
        }
        SDL_FreeSurface(loadSurface);
        ObstacleTexture = loadTexture;
    }
    return ObstacleTexture != NULL;
}

void Obstacle::Move(int speed) {
    xPos -= speed;
}

void Obstacle::Render(SDL_Renderer *gRenderer, SDL_Rect *clip) {
    SDL_Rect renderSpace = {xPos, yPos, width, height};
    if (clip != NULL) {
        renderSpace.w = clip -> w;
        renderSpace.h = clip -> h;
    }
    SDL_RenderCopy(gRenderer, ObstacleTexture, clip, &renderSpace);
}

int Obstacle::GetType() {
    if (type == CACTUS) {
        return CACTUS;
    }
    else if (type == BIRD) {
        return BIRD;
    }
    return 0;
}

int Obstacle::GetXPos() {
    return xPos;
}

int Obstacle::GetYPos() {
    return yPos;
}

int Obstacle::GetWidth() {
    return width;
}

int Obstacle::GetHeight() {
    return height;
}
