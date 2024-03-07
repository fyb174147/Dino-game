#include "Included.h"
using namespace std;

class LTexture {
    public:
        LTexture();
        ~LTexture();
        void Free();
        bool LoadFromRenderedText(string textureText, TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *gRenderer);
        bool LoadFromFile(string path, SDL_Renderer *gRenderer);
        void Render(int x, int y, SDL_Renderer *gRenderer, SDL_Rect *clip);
        int GetWidth();
        int GetHeight();
    private:
        SDL_Texture *mTexture;
        int mWidth;
        int mHeight;
};

LTexture::LTexture() {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture() {
    Free();
}

void LTexture::Free() {
    if (mTexture != NULL) {
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

bool LTexture::LoadFromRenderedText(string textureText, TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *gRenderer) {
    Free();

    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if (textSurface == NULL) {
        cout << "Render text surface error: " << TTF_GetError() << '\n';
    }
    else {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (mTexture == NULL) {
            cout << "Create texture from rendered text error: " << SDL_GetError() << '\n';
        }
        else {
            mWidth = textSurface -> w;
            mHeight = textSurface -> h;
        }
        SDL_FreeSurface(textSurface);
    }

    return mTexture != NULL;
}

bool LTexture::LoadFromFile(string path, SDL_Renderer *gRenderer) {
    Free();

    SDL_Surface *loadSurface = IMG_Load(path.c_str());
    if (loadSurface == NULL) {
        cout << "Load image " << path << " error: " << IMG_GetError() << '\n';
    }
    else {
        SDL_Texture *loadTexture = SDL_CreateTextureFromSurface(gRenderer, loadSurface);
        if (loadSurface == NULL) {
            cout << "Create texture from surface " << path << " error: " << SDL_GetError() << '\n';
        }
        else {
            mWidth = loadSurface -> w;
            mHeight = loadSurface -> h;
        }
        SDL_FreeSurface(loadSurface);
        mTexture = loadTexture;
    }

    return mTexture != NULL;
}

void LTexture::Render(int x, int y, SDL_Renderer *gRenderer, SDL_Rect *clip) {
    SDL_Rect renderSpace = {x, y, mWidth, mHeight};

    if (clip != NULL) {
        renderSpace.w = clip -> w;
        renderSpace.h = clip -> h;
    }

    SDL_RenderCopy(gRenderer, mTexture, clip, &renderSpace);
}

int LTexture::GetWidth() {
    return mWidth;
}

int LTexture::GetHeight() {
    return mHeight;
}
