#include "Included.h"
using namespace std;

enum CharacterStatus {
    JUMPING,
    SHIFTING,
    DIE,
    TOTAL_CHARACTER_STATUS
};

enum CharacterType {
    DINO,
    TOTAL_CHARACTER_TYPE
};

class Character {
    public:
        Character(int _type, int _status);
        ~Character();
        void Free();
        bool LoadFromFile(string path, SDL_Renderer *gRenderer);
        bool HandleEvents(SDL_Event &e);
        void Move(int speed);
        void Render(SDL_Renderer *gRenderer, SDL_Rect *clip, int customWidth, int customHeight);
        int GetType();
        int GetXPos();
        int GetYPos();
        int GetWidth();
        int GetHeight();
        void SetStatus(int _status);
        int GetStatus();
        void SetOrigin(int _type, int _status);
    private:
        bool jumping = false;
        bool falling = false;
        int xPos;
        int yPos;
        int width;
        int height;
        int type;
        int deltaH;
        int timeJump;
        int maxH;
        int status;
        SDL_Texture *CharacterTexture;
};

Character::Character(int _type, int _status) {
    xPos = 0;
    yPos = 0;
    width = 0;
    height = 0;
    type = 0;
    deltaH = 0;
    timeJump = 0;
    maxH = 0;
    status = 0;
    if (_type == DINO) {
        type = _type;
        xPos = 200;
        yPos = 550;
        width = 250;
        height = 250;
        deltaH = 0;
        timeJump = 0;
        maxH = 300;
        status = _status;
    }
    CharacterTexture = NULL;
}

Character::~Character() {
    Free();
}

void Character::Free() {
    if (CharacterTexture == NULL) return;
    CharacterTexture = NULL;
}

bool Character::LoadFromFile(string path, SDL_Renderer *gRenderer) {
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
        CharacterTexture = loadTexture;
    }
    return CharacterTexture != NULL;
}

bool Character::HandleEvents(SDL_Event &e) {
    if (status == DIE) {
        return false;
    }
    int previousStatus = status;
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP) {
            if (timeJump < 1 && !jumping) {
                jumping = true;
                deltaH = 0;
                timeJump++;
                status = JUMPING;
            }
        }
        else if (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_DOWN) {
            if (status != DIE) status = SHIFTING;
        }
        // trolling button. DO NOT PRESS !!!
        else if (e.key.keysym.sym == SDLK_0) {
            status = DIE;
        }
    }
    else {
        if (status != DIE) status = JUMPING;
    }
    return previousStatus != status;
}

void Character::Move(int speed) {
    if (jumping) {
        yPos -= speed;
        deltaH += speed;
        if (deltaH >= maxH) {
            jumping = false;
            falling = true;
        }
    }
    else if (falling) {
        yPos += speed;
        if (yPos >= 550) {
            falling = false;
            yPos = 550;
        }
    }
    if (yPos == 550) {
        timeJump = 0;
        deltaH = 0;
    }
}

void Character::Render(SDL_Renderer *gRenderer, SDL_Rect *clip, int customWidth, int customHeight) {
    SDL_Rect renderSpace = {xPos, yPos, width, height};
    if (clip != NULL) {
        renderSpace.w = clip -> w;
        renderSpace.h = clip -> h;
    }
    if (customWidth != -1) renderSpace.w = customWidth;
    if (customHeight != -1) renderSpace.h = customHeight;
    SDL_RenderCopy(gRenderer, CharacterTexture, clip, &renderSpace);
}

int Character::GetType() {
    if (type == DINO) {
        return DINO;
    }
    return 0;
}

int Character::GetXPos() {
    return xPos;
}

int Character::GetYPos() {
    return yPos;
}

int Character::GetWidth() {
    return width;
}

int Character::GetHeight() {
    return height;
}

void Character::SetStatus(int _status) {
    status = _status;
}

int Character::GetStatus() {
    if (status == JUMPING) {
        return JUMPING;
    }
    else if (status == SHIFTING) {
        return SHIFTING;
    }
    else if (status == DIE) {
        return DIE;
    }
    return 0;
}

void Character::SetOrigin(int _type, int _status) {
    xPos = 0;
    yPos = 0;
    width = 0;
    height = 0;
    type = 0;
    deltaH = 0;
    timeJump = 0;
    maxH = 0;
    status = 0;
    if (_type == DINO) {
        type = _type;
        xPos = 200;
        yPos = 550;
        width = 250;
        height = 250;
        deltaH = 0;
        timeJump = 0;
        maxH = 300;
        status = _status;
    }
}
