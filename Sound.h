#include "Included.h"
using namespace std;

enum SoundType{
    BACKGROUND_MUSIC,
    JUMPING_SOUND,
    GAME_OVER_SOUND,
    BUTTON_SOUND,
    TOTAL_GAME_SOUND,
};

class Sound{
    public:
        Sound();
        ~Sound();
        void Free();
        void Play(int _sound);
        void Pause(int _sound);
        void Stop(int _sound);
        bool LoadFromFile();
    private:
        Mix_Music *GameMusic;
        Mix_Chunk *JumpingSound;
        Mix_Chunk *GameOverSound;
        Mix_Chunk *ButtonSound;
};

Sound::Sound() {
    GameMusic = NULL;
    JumpingSound = NULL;
    GameOverSound = NULL;
    ButtonSound = NULL;
}

Sound::~Sound() {
    Free();
}

void Sound::Free() {
    Mix_FreeChunk(JumpingSound);
    JumpingSound = NULL;

    Mix_FreeChunk(GameOverSound);
    GameOverSound = NULL;

    Mix_FreeChunk(ButtonSound);
    ButtonSound = NULL;

    Mix_FreeMusic(GameMusic);
    GameMusic = NULL;
}

void Sound::Play(int _sound) {
    if (_sound == BACKGROUND_MUSIC) {
        if (!Mix_PlayingMusic()) Mix_PlayMusic(GameMusic, -1);
        else if (Mix_PausedMusic()) Mix_ResumeMusic();
    }
    else if (_sound == JUMPING_SOUND) Mix_PlayChannel(-1, JumpingSound, 0);
    else if (_sound == GAME_OVER_SOUND) Mix_PlayChannel(-1, GameOverSound, 0);
    else if (_sound == BUTTON_SOUND) Mix_PlayChannel(-1, ButtonSound, 0);
}

void Sound::Pause(int _sound) {
    if (_sound == BACKGROUND_MUSIC) {
        if (!Mix_PausedMusic()) Mix_PauseMusic();
    }
}

void Sound::Stop(int _sound) {
    if (_sound == BACKGROUND_MUSIC) {
        if (Mix_PlayingMusic()) Mix_HaltMusic();
    }
}

bool Sound::LoadFromFile() {
    bool success = true;

    GameMusic = Mix_LoadMUS("sound/Game.mp3");
    if (GameMusic == NULL) {
        cout << "Cannot load Game music: " << Mix_GetError() << '\n';
        success = false;
    }

    JumpingSound = Mix_LoadWAV("sound/Jump.wav");
    if (JumpingSound == NULL) {
        cout << "Cannot load Jumping sound: " << Mix_GetError() << '\n';
        success = false;
    }

    GameOverSound = Mix_LoadWAV("sound/GameOver.wav");
    if (GameOverSound == NULL) {
        cout << "Cannot load Game over sound: " << Mix_GetError() << '\n';
        success = false;
    }

    ButtonSound = Mix_LoadWAV("sound/Button.wav");
    if (ButtonSound == NULL) {
        cout << "Cannot load Button sound: " << Mix_GetError() << '\n';
        success = false;
    }

    return success;
}
