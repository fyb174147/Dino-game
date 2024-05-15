#include "Obstacles.h"
#include "Background.h"
#include "Character.h"
#include "Meteor.h"
#include "Menu.h"
#include "Sound.h"

mt19937 Rand(time(NULL));

class Game: public Obstacle, public Background, public Character, public Meteor, public Menu, public Sound{
    public:
        Game(): Grass(GRASS), Tree(TREE), Sky(SKY), Credit(CREDIT),
                CactusSmall(CACTUS_SMALL), CactusMedium(CACTUS_MEDIUM), CactusLarge(CACTUS_LARGE), Bird(BIRD),
                Dino(DINO, JUMPING) {}
        bool Init();
        bool LoadMedia();
        void Close();
        void Run();

        bool isQuit();
    private:
        int gameSpeed = 2;

        SDL_Window *gWindow = NULL;
        SDL_Renderer *gRenderer = NULL;

        Menu MainMenu;
        Sound MainGameSound;

        Background Grass;
        Background Tree;
        Background Sky;
        Background Credit;

        Obstacle CactusSmall;
        Obstacle CactusMedium;
        Obstacle CactusLarge;
        Obstacle Bird;

        Character Dino;

        Meteor BigBoi;

        SDL_Rect birdSpriteClips[5];
        SDL_Rect characterSpriteClips[5];

        SDL_Event e;
        bool quit = false;
        long long totalFrame = 0;
        int characterFrame = 0;
        int previousObstacleXPos = 0;
        int countObstacles = 0;
        bool setCharacterFrameToZero = false;

        deque<Background> GrassQueue;
        deque<Background> TreeQueue;
        deque<Background> SkyQueue;
        deque<Obstacle> GameObject;

        bool GameOver = false;
        bool GameStart = false;
        bool GamePause = false;
        bool MeteorIncoming = false;

        bool ShowCredit = false;
};

bool Game::Init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cout << "SDL could not initialize: " << SDL_GetError() << '\n';
        success = false;
    }
    else {
        gWindow = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            cout << "Cannot create window: " << SDL_GetError() << '\n';
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                cout << "Renderer bruhh: " << SDL_GetError() << '\n';
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlag = IMG_INIT_PNG;
                if (IMG_Init(imgFlag) == false && imgFlag > 0) {
                    cout << "SDL_image bruhh: " << IMG_GetError() << '\n';
                    success = false;
                }
                if (TTF_Init() == -1) {
                    cout << "SDL_ttf bruhh: " << TTF_GetError() << '\n';
                    success = false;
                }

                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
            }
        }
    }

    return success;
}

bool Game::LoadMedia() {
    bool success = true;
    if (!CactusSmall.LoadFromFile("image/cactusSmall.png", gRenderer)) {
        cout << "Cannot load Cactus Small\n";
        success = false;
    }
    if (!CactusMedium.LoadFromFile("image/cactusMedium.png", gRenderer)) {
        cout << "Cannot load Cactus Medium\n";
        success = false;
    }
    if (!CactusLarge.LoadFromFile("image/cactusLarge.png", gRenderer)) {
        cout << "Cannot load Cactus Large\n";
        success = false;
    }
    if (!Bird.LoadFromFile("image/bird.png", gRenderer)) {
        cout << "Cannot load Bird\n";
        success = false;
    }
    else {
        birdSpriteClips[0].x = 0;
        birdSpriteClips[0].y = 0;
        birdSpriteClips[0].w = 50;
        birdSpriteClips[0].h = 50;

        birdSpriteClips[1].x = 50;
        birdSpriteClips[1].y = 0;
        birdSpriteClips[1].w = 50;
        birdSpriteClips[1].h = 50;

        birdSpriteClips[2].x = 100;
        birdSpriteClips[2].y = 0;
        birdSpriteClips[2].w = 50;
        birdSpriteClips[2].h = 50;

        birdSpriteClips[3].x = 150;
        birdSpriteClips[3].y = 0;
        birdSpriteClips[3].w = 50;
        birdSpriteClips[3].h = 50;

        birdSpriteClips[4].x = 200;
        birdSpriteClips[4].y = 0;
        birdSpriteClips[4].w = 50;
        birdSpriteClips[4].h = 50;
    }
    if (!Tree.LoadFromFile("image/tree.png", gRenderer)) {
        cout << "Cannot load Tree\n";
        success = false;
    }
    if (!Grass.LoadFromFile("image/grass.png", gRenderer)) {
        cout << "Cannot load Grass\n";
        success = false;
    }
    if (!Sky.LoadFromFile("image/sky.png", gRenderer)) {
        cout << "Cannot load Sky\n";
        success = false;
    }
    if (!Dino.LoadFromFile("image/dinoRun.png", gRenderer)) {
        cout << "Cannot load Dino Jump\n";
        success = false;
    }
    else {
        characterSpriteClips[0].x = 0;
        characterSpriteClips[0].y = 0;
        characterSpriteClips[0].w = 240;
        characterSpriteClips[0].h = 240;

        characterSpriteClips[1].x = 240;
        characterSpriteClips[1].y = 0;
        characterSpriteClips[1].w = 240;
        characterSpriteClips[1].h = 240;

        characterSpriteClips[2].x = 480;
        characterSpriteClips[2].y = 0;
        characterSpriteClips[2].w = 240;
        characterSpriteClips[2].h = 240;

        characterSpriteClips[3].x = 720;
        characterSpriteClips[3].y = 0;
        characterSpriteClips[3].w = 240;
        characterSpriteClips[3].h = 240;

        characterSpriteClips[4].x = 960;
        characterSpriteClips[4].y = 0;
        characterSpriteClips[4].w = 240;
        characterSpriteClips[4].h = 240;
    }
    if (!Credit.LoadFromFile("image/credit.png", gRenderer)) {
        cout << "Cannot load Credit\n";
        success = false;
    }
    if (!MainMenu.LoadFromFile(gRenderer)) {
        cout << "Cannot load Menu\n";
        success = false;
    }
    if (!BigBoi.LoadFromFile(gRenderer)) {
        cout << "Cannot load Big Boi\n";
        success = false;
    }
    if (!MainGameSound.LoadFromFile()) {
        cout << "Cannot load Sound\n";
        success = false;
    }
    return success;
}

void Game::Close() {
    Grass.Free();
    Tree.Free();
    Sky.Free();
    Credit.Free();

    CactusSmall.Free();
    CactusMedium.Free();
    CactusLarge.Free();
    Bird.Free();

    Dino.Free();

    BigBoi.Free();

    MainMenu.Free();
    MainGameSound.Free();

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

void Game::Run() {
    // generate first 3 grass background
    {
        {
            Background GenerateGrass(GRASS, -SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
            GenerateGrass.LoadFromFile("image/grass.png", gRenderer);
            GrassQueue.push_back(GenerateGrass);
        }
        {
            Background GenerateGrass(GRASS, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
            GenerateGrass.LoadFromFile("image/grass.png", gRenderer);
            GrassQueue.push_back(GenerateGrass);
        }
        {
            Background GenerateGrass(GRASS, SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
            GenerateGrass.LoadFromFile("image/grass.png", gRenderer);
            GrassQueue.push_back(GenerateGrass);
        }
    }

    // generate first 3 tree background
    {
        {
            Background GenerateTree(TREE, -SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
            GenerateTree.LoadFromFile("image/tree.png", gRenderer);
            TreeQueue.push_back(GenerateTree);
        }
        {
            Background GenerateTree(TREE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
            GenerateTree.LoadFromFile("image/tree.png", gRenderer);
            TreeQueue.push_back(GenerateTree);
        }
        {
            Background GenerateTree(TREE, SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
            GenerateTree.LoadFromFile("image/tree.png", gRenderer);
            TreeQueue.push_back(GenerateTree);
        }
    }

    // generate first 3 sky background
    {
        {
            Background GenerateSky(SKY, -SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
            GenerateSky.LoadFromFile("image/sky.png", gRenderer);
            SkyQueue.push_back(GenerateSky);
        }
        {
            Background GenerateSky(SKY, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
            GenerateSky.LoadFromFile("image/sky.png", gRenderer);
            SkyQueue.push_back(GenerateSky);
        }
        {
            Background GenerateSky(SKY, SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
            GenerateSky.LoadFromFile("image/sky.png", gRenderer);
            SkyQueue.push_back(GenerateSky);
        }
    }

    bool GameOver = false;
    bool GameStart = false;
    bool GamePause = false;
    bool MeteorIncoming = false;

    bool ShowCredit = false;


    while (!quit) {
        // increase game speed
        // removed this feature :(
        /*
        if (countObstacles >= obstaclesNeedToPass) {
            gameSpeed++;
            countObstacles = 0;
            obstaclesNeedToPass += 5;
        }
        */

        int grassSpeed = gameSpeed * 3;
        int treeSpeed = gameSpeed * 2;
        int skySpeed = gameSpeed;

        bool switchCharacterStatus = false;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (ShowCredit) {
                //if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) || (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)) ShowCredit = false;
                if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN) ShowCredit = false;
                continue;
            }

            // handle character events
            if (GameStart && !GamePause && !GameOver) switchCharacterStatus = Dino.HandleEvents(e);

            // Menu events
            int MenuStatus = MainMenu.HandleEvents(e);
            if (MenuStatus != -1) {
                if (MenuStatus == ENUM_JUMP && Dino.GetYPos() == 550) MainGameSound.Play(JUMPING_SOUND);
                else MainGameSound.Play(BUTTON_SOUND);
            }

            if (MenuStatus == ENUM_PLAY) {
                GamePause = false;
                GameStart = true;
            }
            else if (MenuStatus == ENUM_SHOWN_PAUSE) {
                GamePause = true;
            }
            else if (MenuStatus == ENUM_RELEASE_PAUSE) {
                GamePause = false;
            }
            else if (MenuStatus == ENUM_REPLAY) {
                while (!GameObject.empty()) {
                    Obstacle RemoveObstacle = GameObject.front();
                    GameObject.pop_front();
                    RemoveObstacle.Free();
                }
                Dino.SetOrigin(DINO, JUMPING);
                characterFrame = 0;
                previousObstacleXPos = 0;
                totalFrame = 0;
                GameOver = false;
                GamePause = false;
                switchCharacterStatus = true;
                countObstacles = 0;
            }
            else if (MenuStatus == ENUM_CREDIT) {
                ShowCredit = true;
            }
        }

        if (!GamePause) {
            MainGameSound.Play(BACKGROUND_MUSIC);

            // Generate more grass background
            {
                bool Erase = false;
                for (auto CurrentGrass:GrassQueue) {
                    if (CurrentGrass.GetXPos() <= -SCREEN_WIDTH) {
                        int GenerateXPos = GrassQueue.back().GetXPos() + 1600;
                        Background GenerateGrass(GRASS, GenerateXPos, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
                        GenerateGrass.LoadFromFile("image/grass.png", gRenderer);
                        GrassQueue.push_back(GenerateGrass);
                        if (GrassQueue.size() > 3) Erase = true;
                    }
                }
                if (Erase) {
                    Background RemoveGrass = GrassQueue.front();
                    GrassQueue.pop_front();
                    RemoveGrass.Free();
                }
            }

            // Generate more tree background
            {
                bool Erase = false;
                for (auto CurrentTree:TreeQueue) {
                    if (CurrentTree.GetXPos() <= -SCREEN_WIDTH) {
                        int GenerateXPos = TreeQueue.back().GetXPos() + 1600;
                        Background GenerateTree(TREE, GenerateXPos, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
                        GenerateTree.LoadFromFile("image/tree.png", gRenderer);
                        TreeQueue.push_back(GenerateTree);
                        if (TreeQueue.size() > 3) Erase = true;
                    }
                }
                if (Erase) {
                    Background RemoveTree = TreeQueue.front();
                    TreeQueue.pop_front();
                    RemoveTree.Free();
                }
            }

            // Generate more sky background
            {
                bool Erase = false;
                for (auto CurrentSky:SkyQueue) {
                    if (CurrentSky.GetXPos() <= -SCREEN_WIDTH) {
                        int GenerateXPos = SkyQueue.back().GetXPos() + 1600;
                        Background GenerateSky(SKY, GenerateXPos, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 3);
                        GenerateSky.LoadFromFile("image/sky.png", gRenderer);
                        SkyQueue.push_back(GenerateSky);
                        if (SkyQueue.size() > 3) Erase = true;
                    }
                }
                if (Erase) {
                    Background RemoveSky = SkyQueue.front();
                    SkyQueue.pop_front();
                    RemoveSky.Free();
                }
            }

            // Generate & destroy some obstacles
            {
                if (totalFrame > 1000 && previousObstacleXPos <= 0 && countObstacles < 123) {
                    previousObstacleXPos = 1600;
                    countObstacles++;
                    int CurrentObstacle = Rand() % TOTAL_OBSTACLE_TYPE;

                    if (CurrentObstacle == CACTUS_SMALL) {
                        Obstacle GenerateCactusSmall(CACTUS_SMALL);
                        GenerateCactusSmall.LoadFromFile("image/cactusSmall.png", gRenderer);
                        GameObject.push_back(GenerateCactusSmall);
                    }
                    else if (CurrentObstacle == CACTUS_MEDIUM) {
                        Obstacle GenerateCactusMedium(CACTUS_MEDIUM);
                        GenerateCactusMedium.LoadFromFile("image/cactusMedium.png", gRenderer);
                        GameObject.push_back(GenerateCactusMedium);
                    }
                    else if (CurrentObstacle == CACTUS_LARGE) {
                        Obstacle GenerateCactusLarge(CACTUS_LARGE);
                        GenerateCactusLarge.LoadFromFile("image/cactusLarge.png", gRenderer);
                        GameObject.push_back(GenerateCactusLarge);
                    }
                    else if (CurrentObstacle == BIRD) {
                        Obstacle GenerateBird(BIRD);
                        int yPos = 550 - Rand() % 500;
                        GenerateBird.SetYPos(yPos);
                        GenerateBird.LoadFromFile("image/bird.png", gRenderer);
                        GameObject.push_back(GenerateBird);
                    }
                }

                int countRemoveObstacles = 0;
                for (auto CurrentObstacle:GameObject) {
                    if (CurrentObstacle.GetXPos() < -600) {
                        countRemoveObstacles++;
                    }
                }
                while (countRemoveObstacles--) {
                    Obstacle RemoveObstacle = GameObject.front();
                    GameObject.pop_front();
                    RemoveObstacle.Free();
                }
            }

            // render stuff
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
            SDL_RenderClear(gRenderer);
            {
                for (auto &CurrentSky:SkyQueue) {
                    if (MeteorIncoming) continue;
                    CurrentSky.Render(gRenderer, NULL, 1600, 900);
                }

                for (auto &CurrentTree:TreeQueue) {
                    CurrentTree.Render(gRenderer, NULL, 1600, 900);
                }

                for (auto &CurrentGrass:GrassQueue) {
                    CurrentGrass.Render(gRenderer, NULL, 1600, 900);
                }

                for (auto &CurrentObstacle:GameObject) {
                    SDL_Rect *clip = NULL;
                    int currentObstacleFrame = CurrentObstacle.GetFrame();
                    if (CurrentObstacle.GetType() == BIRD) {
                        clip = &birdSpriteClips[currentObstacleFrame / 20];
                    }
                    CurrentObstacle.Render(gRenderer, clip, 150, 150);
                    int nextFrame = currentObstacleFrame + 1;
                    if (nextFrame / 20 >= 5) nextFrame = 0;
                    CurrentObstacle.SetFrame(nextFrame);
                }
            }
            // render character
            if (!GameOver) {
                int currentCharacterStatus = Dino.GetStatus();
                if (switchCharacterStatus) {
                    characterFrame = 0;
                    Dino.Free();
                    if (currentCharacterStatus == JUMPING) {
                        Dino.SetStatus(JUMPING);
                        Dino.LoadFromFile("image/dinoRun.png", gRenderer);
                    }
                    else if (currentCharacterStatus == SHIFTING) {
                        Dino.SetStatus(SHIFTING);
                        Dino.LoadFromFile("image/dinoShift.png", gRenderer);
                    }
                }
//                    if (currentCharacterStatus == DIE) {
//                        if (!Dino.LoadFromFile("image/dinoDie.png", gRenderer)) {
//                            cout << "Cannot load Dino Die\n";
//                        }
//                    }
                SDL_Rect *clip = &characterSpriteClips[characterFrame / 20];
                Dino.Render(gRenderer, clip, 150, 150);
                characterFrame++;
                if (currentCharacterStatus != DIE && characterFrame / 20 >= 5) characterFrame = 0;
            }

            // render credit
            /*
                if (characterFrame > 100) Credit.Render(gRenderer, NULL, 1600, 900);
            */
            {
                if (GameStart) {
                    totalFrame += gameSpeed;
                    previousObstacleXPos -= grassSpeed;
                }
            }

            // render Big Boi
            if (MeteorIncoming) {
                BigBoi.SetAct(true);
                BigBoi.Move();
                BigBoi.Render();
                if (BigBoi.Success()) {
                    Dino.SetStatus(DIE);
                    MeteorIncoming = false;
                }
            }

            MainMenu.Show();
            if (ShowCredit) Credit.Render(gRenderer, NULL, 1600, 900);

            SDL_RenderPresent(gRenderer);

            // move game object
            if (!GameOver) {
                for (auto &CurrentSky:SkyQueue) {
                    CurrentSky.Move(skySpeed);
                }
                for (auto &CurrentTree:TreeQueue) {
                    CurrentTree.Move(treeSpeed);
                }
                for (auto &CurrentGrass:GrassQueue) {
                    CurrentGrass.Move(grassSpeed);
                }
                for (auto &CurrentObstacle:GameObject) {
                    CurrentObstacle.Move(grassSpeed);
                }
            }

            // move character
            Dino.Move(2 * gameSpeed);

            // check collision
            bool colision = false;
            for (auto CurrentObstacle:GameObject) {
                int currentCharacterStatus = Dino.GetStatus();

                // hit box smaller about 50 pixels than image rendered
                int CharacterXPosLeft = Dino.GetXPos() + 50;
                int CharacterYPosLeft = Dino.GetYPos() + 50;
                int CharacterXPosRight = CharacterXPosLeft + 80;
                int CharacterYPosRight = CharacterYPosLeft + 80;
                if (currentCharacterStatus == SHIFTING) {
                    CharacterYPosLeft += 35;
                }
                int CurrentObstacleXPosLeft = CurrentObstacle.GetXPos() + 50;
                int CurrentObstacleYPosLeft = CurrentObstacle.GetYPos() + 50;
                int CurrentObstacleXPosRight = CurrentObstacleXPosLeft + 80;
                int CurrentObstacleYPosRight = CurrentObstacleYPosLeft + 80;

                // render hitbox. just for testing, can cause serious performance degradation
                /*
                if (!GameOver) {
                    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
                    SDL_RenderDrawLine(gRenderer, CharacterXPosLeft, CharacterYPosLeft, CharacterXPosRight, CharacterYPosLeft);
                    SDL_RenderDrawLine(gRenderer, CharacterXPosRight, CharacterYPosLeft, CharacterXPosRight, CharacterYPosRight);
                    SDL_RenderDrawLine(gRenderer, CharacterXPosLeft, CharacterYPosLeft, CharacterXPosLeft, CharacterYPosRight);
                    SDL_RenderDrawLine(gRenderer, CharacterXPosLeft, CharacterYPosRight, CharacterXPosRight, CharacterYPosRight);

                    SDL_RenderDrawLine(gRenderer, CurrentObstacleXPosLeft, CurrentObstacleYPosLeft, CurrentObstacleXPosRight, CurrentObstacleYPosLeft);
                    SDL_RenderDrawLine(gRenderer, CurrentObstacleXPosRight, CurrentObstacleYPosLeft, CurrentObstacleXPosRight, CurrentObstacleYPosRight);
                    SDL_RenderDrawLine(gRenderer, CurrentObstacleXPosLeft, CurrentObstacleYPosLeft, CurrentObstacleXPosLeft, CurrentObstacleYPosRight);
                    SDL_RenderDrawLine(gRenderer, CurrentObstacleXPosLeft, CurrentObstacleYPosRight, CurrentObstacleXPosRight, CurrentObstacleYPosRight);
                    SDL_RenderPresent(gRenderer);
                }
                */

                int x1 = max(CharacterXPosLeft, CurrentObstacleXPosLeft);
                int x2 = min(CharacterXPosRight, CurrentObstacleXPosRight);
                int y1 = max(CharacterYPosLeft, CurrentObstacleYPosLeft);
                int y2 = min(CharacterYPosRight, CurrentObstacleYPosRight);

                if (x2 >= x1 && y2 >= y1) {
                    colision = true;
                }
            }
            if (colision) {
                Dino.SetStatus(DIE);
            }

            // check trolling button pressed
            if (Dino.GetStatus() == DIE) {
                GameOver = true;
                MainMenu.SetDie(true);
                MainGameSound.Stop(BACKGROUND_MUSIC);
                MainGameSound.Play(GAME_OVER_SOUND);

                if (setCharacterFrameToZero == false) {
                    setCharacterFrameToZero = true;
                    characterFrame = 0;
                }

                GamePause = true;
            }

            // Quit game after 5 secs after die
            // Removed this feature
            /*
            if (characterFrame == 1300) quit = true;
            */

            // Big Boi
            if (countObstacles == 123) {
                MeteorIncoming = true;
            }
        }
        else {
            MainGameSound.Pause(BACKGROUND_MUSIC);
            BigBoi.SetAct(false);
            MainMenu.Show();
            SDL_RenderPresent(gRenderer);
        }

        if (GameOver) {
            Dino.Free();
            characterFrame = 0;
            if (!Dino.LoadFromFile("image/dinoDie.png", gRenderer)) {
                cout << "Cannot load Dino Die\n";
            }
            SDL_Rect *clip = &characterSpriteClips[characterFrame / 20];
            Dino.Render(gRenderer, clip, 150, 150);
            characterFrame++;
        }
    }
}

bool Game::isQuit() {
    return quit;
}
