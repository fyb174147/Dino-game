#include "Included.h"

enum BackgroundType {
    GRASS,
    TREE,
    SKY,
    START,
    CREDIT,
    TOTAL_BACKGROUND_TYPE
};

class Background {
    public:
        Background(int _type);
        Background(int _type, int _xPos, int _yPos, int _width, int _height);
        ~Background();
        void Free();
        bool LoadFromFile(string path, SDL_Renderer *gRenderer);
        void Move(int speed);
        void Render(SDL_Renderer *gRenderer, SDL_Rect *clip, int customWidth, int customHeight);
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
        SDL_Texture *BackgroundTexture;
};

Background::Background(int _type) {
    xPos = 0;
    yPos = 0;
    width = 0;
    height = 0;
    type = 0;
    if (_type == GRASS) {
        type = _type;
        xPos = 0;
        yPos = 0;
        width = SCREEN_WIDTH;
        height = SCREEN_HEIGHT;
    }
    else if (_type == TREE) {
        type = _type;
        xPos = 0;
        yPos = 0;
        width = SCREEN_WIDTH;
        height = SCREEN_HEIGHT;
    }
    else if (_type == SKY) {
        type = _type;
        xPos = 0;
        yPos = 0;
        width = SCREEN_WIDTH;
        height = SCREEN_HEIGHT / 3;
    }
    else if (_type == START) {
        type = _type;
        xPos = SCREEN_WIDTH / 4;
        yPos = 0;
        width = SCREEN_WIDTH / 2;
        height = SCREEN_HEIGHT / 3;
    }
    else if (_type == CREDIT) {
        type = _type;
        xPos = 0;
        yPos = 0;
        width = SCREEN_WIDTH;
        height = SCREEN_HEIGHT;
    }
    BackgroundTexture = NULL;
}

Background::Background(int _type, int _xPos, int _yPos, int _width, int _height) {
    type = _type;
    xPos = _xPos;
    yPos = _yPos;
    width = _width;
    height = _height;
    BackgroundTexture = NULL;
}

Background::~Background() {
    Free();
}

void Background::Free() {
    if (BackgroundTexture == NULL) return;
    xPos = 0;
    yPos = 0;
    width = 0;
    height = 0;
    type = 0;
    BackgroundTexture = NULL;
}

bool Background::LoadFromFile(string path, SDL_Renderer *gRenderer) {
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
        BackgroundTexture = loadTexture;
    }
    return BackgroundTexture != NULL;
}

void Background::Move(int speed) {
    xPos -= speed;
}

void Background::Render(SDL_Renderer *gRenderer, SDL_Rect *clip, int customWidth, int customHeight) {
    SDL_Rect renderSpace = {xPos, yPos, width, height};
    if (clip != NULL) {
        renderSpace.w = clip -> w;
        renderSpace.h = clip -> h;
    }
    if (customWidth != -1) renderSpace.w = customWidth;
    if (customHeight != -1) renderSpace.h = customHeight;
    SDL_RenderCopy(gRenderer, BackgroundTexture, clip, &renderSpace);
}

int Background::GetType() {
    if (type == GRASS) {
        return GRASS;
    }
    else if (type == TREE) {
        return TREE;
    }
    return -1;
}

int Background::GetXPos() {
    return xPos;
}

int Background::GetYPos() {
    return yPos;
}

int Background::GetWidth() {
    return width;
}

int Background::GetHeight() {
    return height;
}
