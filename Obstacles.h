#include "LTexture.h"
using namespace std;

enum ObstacleType {
    CACTUS_SMALL,
    CACTUS_MEDIUM,
    CACTUS_LARGE,
    BIRD,
    TOTAL_OBSTACLE_TYPE
};

class Obstacle {
    public:
        Obstacle(int _type);
        Obstacle(int _type, int _xPos, int _yPos, int _width, int _height, int _frame);
        ~Obstacle();
        void Free();
        bool LoadFromFile(string path, SDL_Renderer *gRenderer);
        void Move(int speed);
        void Render(SDL_Renderer *gRenderer, SDL_Rect *clip, int customWidth, int customHeight);
        int GetType();
        int GetXPos();
        int GetYPos();
        int GetWidth();
        int GetHeight();
        int GetFrame();
        void SetFrame(int _frame);
    private:
        int frame = 0;
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
    if (_type == CACTUS_SMALL) {
        type = _type;
        xPos = SCREEN_WIDTH;
        yPos = 300;
        width = 60;
        height = 80;
    }
    else if (_type == CACTUS_MEDIUM) {
        type = _type;
        xPos = SCREEN_WIDTH;
        yPos = 300;
        width = 93;
        height = 90;
    }
    else if (_type == CACTUS_LARGE) {
        type = _type;
        xPos = SCREEN_WIDTH;
        yPos = 300;
        width = 80;
        height = 80;
    }
    else if (_type == BIRD) {
        type = _type;
        xPos = SCREEN_WIDTH;
        yPos = 300;
        width = 50;
        height = 50;
    }
    frame = 0;
    ObstacleTexture = NULL;
}

Obstacle::Obstacle(int _type, int _xPos, int _yPos, int _width, int _height, int _frame) {
    type = _type;
    xPos = _xPos;
    yPos = _yPos;
    width = _width;
    height = _height;
    frame = _frame;
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
    frame = 0;
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

void Obstacle::Render(SDL_Renderer *gRenderer, SDL_Rect *clip, int customWidth, int customHeight) {
    SDL_Rect renderSpace = {xPos, yPos, width, height};
    if (clip != NULL) {
        renderSpace.w = clip -> w;
        renderSpace.h = clip -> h;
    }
    if (customWidth != -1) renderSpace.w = customWidth;
    if (customHeight != -1) renderSpace.h = customHeight;
    SDL_RenderCopy(gRenderer, ObstacleTexture, clip, &renderSpace);
}

int Obstacle::GetType() {
    if (type == CACTUS_SMALL) {
        return CACTUS_SMALL;
    }
    else if (type == CACTUS_MEDIUM) {
        return CACTUS_MEDIUM;
    }
    else if (type == CACTUS_LARGE) {
        return CACTUS_LARGE;
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

int Obstacle::GetFrame() {
    return frame;
}

void Obstacle::SetFrame(int _frame) {
    frame = _frame;
}
