#include "Included.h"
using namespace std;

enum Button {
    ENUM_PRESS_PAUSE,
    ENUM_RELEASE_PAUSE,
    ENUM_HIDDEN_PAUSE,
    ENUM_SHOWN_PAUSE,

    ENUM_PRESS_SHIFT,
    ENUM_RELEASE_SHIFT,
    ENUM_HIDDEN_SHIFT,
    ENUM_SHOWN_SHIFT,

    ENUM_HIDDEN_SCORE,
    ENUM_SHOWN_SCORE,

    ENUM_HIDDEN_TEXT_SCORE,
    ENUM_SHOWN_TEXT_SCORE,

    ENUM_PRESS_SPACE,
    ENUM_RELEASE_SPACE,
    ENUM_HIDDEN_SPACE,
    ENUM_SHOWN_SPACE,

    ENUM_SHOWN_MAIN_MENU,
    ENUM_HIDDEN_MAIN_MENU,

    ENUM_REPLAY,
    ENUM_PLAY,
    ENUM_CREDIT,
    ENUM_EXIT,
    ENUM_CONTINUE,

    ENUM_PRESS_BUTTON,
    ENUM_JUMP,
};

class Menu {
    public:
        Menu();
        ~Menu();
        bool LoadFromFile(SDL_Renderer *gRenderer);
        void Free();
        int HandleEvents(SDL_Event e);
        void Show();
        bool Pause();
        int GetStatus();
        void SetDie(bool _die);
    private:
        SDL_Renderer* gRenderer = NULL;
        TTF_Font* gFont = NULL;
        SDL_Color textColor = { 0,0,0 };
        int count = 0;

        bool die = false;
        int optional = ENUM_PLAY;
        int status_menu = ENUM_SHOWN_MAIN_MENU;
        int status_pause = ENUM_HIDDEN_PAUSE;
        int status_shift = ENUM_SHOWN_SHIFT;
        int status_score = ENUM_SHOWN_SCORE;
        int status_text_score = ENUM_SHOWN_TEXT_SCORE;
        int status_space = ENUM_SHOWN_SPACE;
        SDL_Texture* menuTexture = NULL;
        SDL_Texture* settingTexture = NULL;
        SDL_Texture* buttonTexture = NULL;
};

Menu::Menu() {
    gFont = NULL;
    textColor = { 0,0,0 };
    count = 0;
    die = false;
    optional = ENUM_PLAY;
    status_menu = ENUM_SHOWN_MAIN_MENU;
    status_pause = ENUM_HIDDEN_PAUSE;
    status_shift = ENUM_SHOWN_SHIFT;
    status_score = ENUM_SHOWN_SCORE;
    status_text_score = ENUM_SHOWN_TEXT_SCORE;
    status_space = ENUM_SHOWN_SPACE;
    menuTexture = NULL;
    settingTexture = NULL;
    buttonTexture = NULL;
}

bool Menu::LoadFromFile(SDL_Renderer *_gRenderer) {
    gRenderer = _gRenderer;
    bool success = true;
    gFont = TTF_OpenFont("font/fontPixel.ttf", 50);
    if (gFont == NULL) {
        std::cout << "cannot load font from ttf!"<<TTF_GetError() << std::endl;
        success = false;
    }
    {
        SDL_Surface* tmpSetting = IMG_Load("image/setting.png");
        if (tmpSetting == NULL) {
            std::cout << "cannot load img setting" << std::endl;
            success = false;
        }
        settingTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSetting);
        if (settingTexture == NULL) {
            std::cout << "cannot create setting texture from surface" << std::endl;
            success = false;
        }
        SDL_FreeSurface(tmpSetting);
    }

    {
        SDL_Surface* tmpButton = IMG_Load("image/key1,5.png");
        if (tmpButton == NULL) {
            std::cout << "cannot load img button" << std::endl;
            success = false;
        }
        buttonTexture = SDL_CreateTextureFromSurface(gRenderer, tmpButton);
        if (buttonTexture == NULL) {
            std::cout << "cannot create button texture from surface" << std::endl;
            success = false;
        }
        SDL_FreeSurface(tmpButton);
    }

    {
        SDL_Surface* tmpMenu = IMG_Load("image/khung.png");
        if (tmpMenu == NULL) {
            std::cout << "cannot load img menu" << std::endl;
            success = false;
        }
        menuTexture = SDL_CreateTextureFromSurface(gRenderer, tmpMenu);
        if (menuTexture == NULL) {
            std::cout << "cannot create menu texture from surface" << std::endl;
            success = false;
        }
        SDL_FreeSurface(tmpMenu);
    }
    return success;
}

void Menu::Free() {
    TTF_CloseFont(gFont);
    gFont = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
}

Menu::~Menu() {
    Free();
}

int Menu::HandleEvents(SDL_Event e) {
    int ReturnStatus = -1;
    if (status_menu == ENUM_SHOWN_MAIN_MENU) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;
            if ((mouseX >= 742 && mouseX <= 742 + 80) && (mouseY >= 330 && mouseY <= 330 + 50)) {
                status_menu = ENUM_HIDDEN_MAIN_MENU;
                return ENUM_PLAY;
            }
            if ((mouseX >= 722 && mouseX <= 742 + 120) && (mouseY >= 425 && mouseY <= 425 + 50)) {
                return ENUM_CREDIT;
            }
            if ((mouseX >= 742 && mouseX <= 742 + 80) && (mouseY >= 505 && mouseY <= 505 + 50)) {
                std::exit(0);
            }
        }
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN) {
            if (optional == ENUM_PLAY) optional = ENUM_CREDIT;
            else if (optional == ENUM_CREDIT) optional = ENUM_EXIT;
            else if(optional == ENUM_EXIT) optional = ENUM_PLAY;
            ReturnStatus = ENUM_PRESS_BUTTON;
        }

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP ) {
            if (optional == ENUM_PLAY) optional = ENUM_EXIT;
            else if (optional == ENUM_CREDIT) optional = ENUM_PLAY;
            else if(optional == ENUM_EXIT)optional = ENUM_CREDIT;
            ReturnStatus = ENUM_PRESS_BUTTON;
        }

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN ) {
            if (optional == ENUM_PLAY) {
                status_menu = ENUM_HIDDEN_MAIN_MENU;
                return ENUM_PLAY;
            }
            else if (optional == ENUM_CREDIT) {
                return ENUM_CREDIT;
            }
            else if(optional== ENUM_EXIT) {
                std::exit(0);
            }
            ReturnStatus = ENUM_PRESS_BUTTON;
        }

    }

    if(status_menu == ENUM_HIDDEN_MAIN_MENU && die == false)
    {
        if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_DOWN) && status_pause == ENUM_HIDDEN_PAUSE && status_space == ENUM_SHOWN_SPACE) {
            status_shift = ENUM_PRESS_SHIFT;
        }
        else if (e.type == SDL_KEYUP && status_pause == ENUM_HIDDEN_PAUSE) {
            status_shift = ENUM_SHOWN_SHIFT;
        }
        if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP) && status_pause == ENUM_HIDDEN_PAUSE && status_shift == ENUM_SHOWN_SHIFT) {
            status_space = ENUM_PRESS_SPACE;
            return ENUM_JUMP;
        }
        else if (e.type == SDL_KEYUP && status_pause == ENUM_HIDDEN_PAUSE) {
            status_space = ENUM_SHOWN_SPACE;
        }
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE && status_pause == ENUM_HIDDEN_PAUSE) {
            status_pause = ENUM_SHOWN_PAUSE;
            optional = ENUM_CONTINUE;
            return ENUM_SHOWN_PAUSE;
        }
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE && status_pause == ENUM_SHOWN_PAUSE) {
            status_pause = ENUM_HIDDEN_PAUSE;
            optional = ENUM_PLAY;
            return ENUM_RELEASE_PAUSE;
        }
        {
            if (optional == ENUM_CONTINUE) {
                if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP)) {
                    optional = ENUM_EXIT;
                    ReturnStatus = ENUM_PRESS_BUTTON;
                }
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                    status_pause = ENUM_HIDDEN_PAUSE;
                    return ENUM_RELEASE_PAUSE;
                }
            }
            else if (optional == ENUM_EXIT) {
                if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP)) {
                    optional = ENUM_CONTINUE;
                    ReturnStatus = ENUM_PRESS_BUTTON;
                }
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                    std::exit(0);
                }
            }
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                int mouseX = e.button.x;
                int mouseY = e.button.y;
                if (status_pause == ENUM_SHOWN_PAUSE) {
                    if ((mouseX >= 10 && mouseX <= 60) && (mouseY >= 10 && mouseY <= 60)) {
                        status_pause = ENUM_HIDDEN_PAUSE;
                        return ENUM_RELEASE_PAUSE;
                    }
                    if ((mouseX >= 710 && mouseX <= 710 + 180) && (mouseY >= 425 && mouseY <= 425 + 50)) {
                        status_pause = ENUM_HIDDEN_PAUSE;
                        return ENUM_RELEASE_PAUSE;
                    }
                    if ((mouseX >= 750 && mouseX <= 850) && (mouseY >= 475 && mouseY <= 475 + 50)) {
                        std::exit(0);
                    }
                    if ((mouseX >= 10 && mouseX <= 60) && (mouseY >= 10 && mouseY <= 60)) {
                        status_pause = ENUM_HIDDEN_PAUSE;
                        return ENUM_RELEASE_PAUSE;
                    }

                }
                else {
                    if ((mouseX >= 10 && mouseX <= 60) && (mouseY >= 10 && mouseY <= 60)) {
                        status_pause = ENUM_SHOWN_PAUSE;
                        return ENUM_SHOWN_PAUSE;
                    }

                }
                std::cout << "clicked at:(" << mouseX << "," << mouseY << ")" << std::endl;

            }
        }
        if ((e.type == SDL_KEYDOWN && status_pause == ENUM_SHOWN_PAUSE && e.key.keysym.sym == SDLK_RETURN) || e.key.keysym.sym == SDLK_KP_ENTER) {
            status_pause = ENUM_HIDDEN_PAUSE;
            return ENUM_RELEASE_PAUSE;
        }
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_0) {
            die = true;
            optional = ENUM_REPLAY;
        }
    }

    if (die == true) {
        if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP)) {
            if (optional == ENUM_REPLAY) optional = ENUM_EXIT;
            else optional = ENUM_REPLAY;
            ReturnStatus = ENUM_PRESS_BUTTON;
        }
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
            if (optional == ENUM_REPLAY) {
                die = false;
                count = 0;
                return ENUM_REPLAY;
            }
            else std::exit(0);
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;
            if(optional == ENUM_REPLAY){
                if ((mouseX >= 692 && mouseX <= 692 + 180) && (mouseY >= 350 && mouseY <= 350 + 50)) {
                    die = false;
                    count = 0;
                    return ENUM_REPLAY;
                }
                if ((mouseX >= 742 && mouseX <= 742 + 80) && (mouseY >= 450 && mouseY <= 450 + 50)) std::exit(0);

            }
            if (optional == ENUM_EXIT) {
                if ((mouseX >= 722  && mouseX <= 7222 + 120) && (mouseY >= 350 && mouseY <= 350 + 50)) {
                    die = false;
                    count = 0;
                    return ENUM_REPLAY;
                }
                if ((mouseX >= 712 && mouseX <= 712 + 140) && (mouseY >= 450 && mouseY <= 450 + 50)) std::exit(0);

            }
        }
    }
    return ReturnStatus;
}

void Menu::Show() {
    if (status_menu == ENUM_SHOWN_MAIN_MENU) {
        SDL_Rect main_menu = { 619,300,326,300 };
        SDL_RenderCopy(gRenderer, menuTexture, NULL, &main_menu);
        if (optional == ENUM_PLAY) {
            SDL_Color textColor_tmp = { 255,255,255 };
            if (status_pause == ENUM_HIDDEN_PAUSE) textColor_tmp = { 128,128,128 };

            SDL_Surface* play = TTF_RenderText_Blended(gFont, "PLAY <-", textColor_tmp);
            SDL_Texture* playTex = SDL_CreateTextureFromSurface(gRenderer, play);
            SDL_Rect play_rect = { 619 + (main_menu.w - play->w) / 2,330,play->w,play->h };
            SDL_RenderCopy(gRenderer, playTex, NULL, &play_rect);
            SDL_DestroyTexture(playTex);
            SDL_FreeSurface(play);

            SDL_Surface* credit = TTF_RenderText_Blended(gFont, "CREDIT", textColor);
            SDL_Texture* creditTex = SDL_CreateTextureFromSurface(gRenderer, credit);
            SDL_Rect credit_rect = { 619 + (main_menu.w - credit->w) / 2,425,credit->w,credit->h };

            SDL_RenderCopy(gRenderer, creditTex, NULL, &credit_rect);
            SDL_DestroyTexture(creditTex);
            SDL_FreeSurface(credit);

            SDL_Surface* exit = TTF_RenderText_Blended(gFont, "EXIT", textColor);
            SDL_Texture* exitTex = SDL_CreateTextureFromSurface(gRenderer, exit);
            SDL_Rect exit_rect = { 619 + (main_menu.w - exit->w) / 2,505,exit->w,exit->h };

            SDL_RenderCopy(gRenderer, exitTex, NULL, &exit_rect);
            SDL_DestroyTexture(exitTex);
            SDL_FreeSurface(exit);

        }
        if (optional == ENUM_CREDIT) {
            SDL_Color textColor_tmp = { 255,255,255 };
            if (status_pause == ENUM_HIDDEN_PAUSE) textColor_tmp = { 128,128,128 };

            SDL_Surface* play = TTF_RenderText_Blended(gFont, "PLAY", textColor);
            SDL_Texture* playTex = SDL_CreateTextureFromSurface(gRenderer, play);
            SDL_Rect play_rect = { 619 + (main_menu.w - play->w) / 2,330,play->w,play->h };
            SDL_RenderCopy(gRenderer, playTex, NULL, &play_rect);
            SDL_DestroyTexture(playTex);
            SDL_FreeSurface(play);

            SDL_Surface* credit = TTF_RenderText_Blended(gFont, "CREDIT <-", textColor_tmp);
            SDL_Texture* creditTex = SDL_CreateTextureFromSurface(gRenderer, credit);
            SDL_Rect credit_rect = { 619 + (main_menu.w - credit->w) / 2,425,credit->w,credit->h };

            SDL_RenderCopy(gRenderer, creditTex, NULL, &credit_rect);
            SDL_DestroyTexture(creditTex);
            SDL_FreeSurface(credit);

            SDL_Surface* exit = TTF_RenderText_Blended(gFont, "EXIT", textColor);
            SDL_Texture* exitTex = SDL_CreateTextureFromSurface(gRenderer, exit);
            SDL_Rect exit_rect = { 619 + (main_menu.w - exit->w) / 2,505,exit->w,exit->h };

            SDL_RenderCopy(gRenderer, exitTex, NULL, &exit_rect);
            SDL_DestroyTexture(exitTex);
            SDL_FreeSurface(exit);
        }
        if (optional == ENUM_EXIT) {
            SDL_Color textColor_tmp = { 255,255,255 };
            if (status_pause == ENUM_HIDDEN_PAUSE) textColor_tmp = { 128,128,128 };

            SDL_Surface* play = TTF_RenderText_Blended(gFont, "PLAY", textColor);
            SDL_Texture* playTex = SDL_CreateTextureFromSurface(gRenderer, play);
            SDL_Rect play_rect = { 619 + (main_menu.w - play->w) / 2,330,play->w,play->h };
            SDL_RenderCopy(gRenderer, playTex, NULL, &play_rect);
            SDL_DestroyTexture(playTex);
            SDL_FreeSurface(play);

            SDL_Surface* credit = TTF_RenderText_Blended(gFont, "CREDIT", textColor);
            SDL_Texture* creditTex = SDL_CreateTextureFromSurface(gRenderer, credit);
            SDL_Rect credit_rect = { 619 + (main_menu.w - credit->w) / 2,425,credit->w,credit->h };

            SDL_RenderCopy(gRenderer, creditTex, NULL, &credit_rect);
            SDL_DestroyTexture(creditTex);
            SDL_FreeSurface(credit);

            SDL_Surface* exit = TTF_RenderText_Blended(gFont, "EXIT <-", textColor_tmp);
            SDL_Texture* exitTex = SDL_CreateTextureFromSurface(gRenderer, exit);
            SDL_Rect exit_rect = { 619 + (main_menu.w - exit->w) / 2,505,exit->w,exit->h };

            SDL_RenderCopy(gRenderer, exitTex, NULL, &exit_rect);
            SDL_DestroyTexture(exitTex);
            SDL_FreeSurface(exit);
        }


    }
    else if(status_menu == ENUM_HIDDEN_MAIN_MENU) {
        {
            SDL_Rect setting_rect = { 10,10,50,50 };
            SDL_RenderCopy(gRenderer, settingTexture, NULL, &setting_rect);
        }

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
        if (status_pause == ENUM_SHOWN_PAUSE) {
            if (optional == ENUM_CONTINUE) {
                SDL_Color textColor_tmp = { 255,255,255 };
                if (status_pause == ENUM_HIDDEN_PAUSE) textColor_tmp = { 128,128,128 };

                SDL_Rect menu_rect = { 555,225,490,450 };
                SDL_RenderCopy(gRenderer, menuTexture, NULL, &menu_rect);

                SDL_Surface* pauseSurface = TTF_RenderText_Blended(gFont, "CONTINUE <-", textColor_tmp);
                SDL_Texture* pauseTexture = SDL_CreateTextureFromSurface(gRenderer, pauseSurface);
                SDL_Rect pauseRect = { 800 - pauseSurface->w / 2 , 425 - pauseSurface->h / 2, pauseSurface->w, pauseSurface->h };
                SDL_RenderCopy(gRenderer, pauseTexture, nullptr, &pauseRect);
                SDL_DestroyTexture(pauseTexture);
                SDL_FreeSurface(pauseSurface);


                SDL_Surface* exitSurface = TTF_RenderText_Blended(gFont, "EXIT", textColor);
                SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(gRenderer, exitSurface);
                SDL_Rect exitRect = { 800 - exitSurface->w / 2 , 475 - exitSurface->h / 2, exitSurface->w, exitSurface->h };
                SDL_RenderCopy(gRenderer, exitTexture, nullptr, &exitRect);
                SDL_DestroyTexture(exitTexture);
                SDL_FreeSurface(exitSurface);

            }
            if (optional == ENUM_EXIT) {
                SDL_Color textColor_tmp = { 255,255,255 };
                if (status_pause == ENUM_HIDDEN_PAUSE) textColor_tmp = { 128,128,128 };

                SDL_Rect menu_rect = { 555,225,490,450 };
                SDL_RenderCopy(gRenderer, menuTexture, NULL, &menu_rect);

                SDL_Surface* pauseSurface = TTF_RenderText_Blended(gFont, "CONTINUE", textColor);
                SDL_Texture* pauseTexture = SDL_CreateTextureFromSurface(gRenderer, pauseSurface);
                SDL_Rect pauseRect = { 800 - pauseSurface->w / 2 , 425 - pauseSurface->h / 2, pauseSurface->w, pauseSurface->h };
                SDL_RenderCopy(gRenderer, pauseTexture, nullptr, &pauseRect);
                SDL_DestroyTexture(pauseTexture);
                SDL_FreeSurface(pauseSurface);


                SDL_Surface* exitSurface = TTF_RenderText_Blended(gFont, "EXIT <-", textColor_tmp);
                SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(gRenderer, exitSurface);
                SDL_Rect exitRect = { 800 - exitSurface->w / 2 , 475 - exitSurface->h / 2, exitSurface->w, exitSurface->h };
                SDL_RenderCopy(gRenderer, exitTexture, nullptr, &exitRect);
                SDL_DestroyTexture(exitTexture);
                SDL_FreeSurface(exitSurface);

            }

        }
        if (status_shift == ENUM_SHOWN_SHIFT) {
            SDL_Rect shift_rect = { 50,680,270,90 };
            SDL_RenderCopy(gRenderer, buttonTexture, NULL, &shift_rect);

            SDL_Surface* shiftSurface = TTF_RenderText_Blended(gFont, "LShift/Down:bow", textColor);
            SDL_Texture* shiftTexture = SDL_CreateTextureFromSurface(gRenderer, shiftSurface);
            SDL_Rect shiftRect = { shift_rect.x + (shift_rect.w - shiftSurface->w) / 2, shift_rect.y + (shift_rect.h - shiftSurface->h) / 2, shiftSurface->w, shiftSurface->h };
            SDL_RenderCopy(gRenderer, shiftTexture, nullptr, &shiftRect);
            SDL_DestroyTexture(shiftTexture);

            SDL_FreeSurface(shiftSurface);
        }

        if (status_shift == ENUM_PRESS_SHIFT) {
            SDL_Rect shift_rect = { 50,690,270,90 };
            SDL_RenderCopy(gRenderer, buttonTexture, NULL, &shift_rect);

            SDL_Color textColor_tmp = { 255,255,255 };
            if (status_pause == ENUM_HIDDEN_PAUSE) textColor_tmp = { 128,128,128 };

            SDL_Surface* shiftSurface = TTF_RenderText_Blended(gFont, "LShift/Down:bow", textColor_tmp);
            SDL_Texture* shiftTexture = SDL_CreateTextureFromSurface(gRenderer, shiftSurface);
            SDL_Rect shiftRect = { shift_rect.x + (shift_rect.w - shiftSurface->w) / 2, shift_rect.y + (shift_rect.h - shiftSurface->h) / 2, shiftSurface->w, shiftSurface->h };
            SDL_RenderCopy(gRenderer, shiftTexture, nullptr, &shiftRect);
            SDL_DestroyTexture(shiftTexture);
            SDL_FreeSurface(shiftSurface);

        }

        if (status_score == ENUM_SHOWN_SCORE) {
            SDL_Rect score_rect = { 1280,30,270,90 };
            SDL_RenderCopy(gRenderer, buttonTexture, NULL, &score_rect);
            SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, "Score:", textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
            SDL_Rect textRect = { 1300, 50, textSurface->w, textSurface->h };
            SDL_RenderCopy(gRenderer, textTexture, nullptr, &textRect);
            SDL_DestroyTexture(textTexture);
            SDL_FreeSurface(textSurface);
            if (status_pause == ENUM_HIDDEN_PAUSE && die == false && count < 33349) {
                count++;
            }
            std::stringstream ss;
            ss << (count / 50);
            std::string num = ss.str();
            SDL_Surface* scoreSurface = TTF_RenderText_Blended(gFont, num.c_str(), textColor);
            SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(gRenderer, scoreSurface);
            SDL_Rect scoreRect = { 1280 + 160, 50, scoreSurface->w, scoreSurface->h };
            SDL_RenderCopy(gRenderer, scoreTexture, nullptr, &scoreRect);
            SDL_DestroyTexture(scoreTexture);
            SDL_FreeSurface(scoreSurface);
        }



        if (status_space == ENUM_SHOWN_SPACE) {
            SDL_Rect space_rect = { 330,680,270,90 };
            SDL_RenderCopy(gRenderer, buttonTexture, NULL, &space_rect);

            SDL_Surface* spaceSurface = TTF_RenderText_Blended(gFont, "Space/Up:jump", textColor);
            SDL_Texture* spaceTexture = SDL_CreateTextureFromSurface(gRenderer, spaceSurface);
            SDL_Rect spaceRect = { space_rect.x + (space_rect.w - spaceSurface->w) / 2, space_rect.y + (space_rect.h - spaceSurface->h) / 2, spaceSurface->w, spaceSurface->h };
            SDL_RenderCopy(gRenderer, spaceTexture, nullptr, &spaceRect);
            SDL_DestroyTexture(spaceTexture);
            SDL_FreeSurface(spaceSurface);
        }

        if (status_space == ENUM_PRESS_SPACE) {
            SDL_Rect space_rect = { 330,690,270,90 };
            SDL_RenderCopy(gRenderer, buttonTexture, NULL, &space_rect);

            SDL_Color textColor_tmp = { 255,255,255 };
            if (status_pause == ENUM_HIDDEN_PAUSE) textColor_tmp = { 128,128,128 };

            SDL_Surface* spaceSurface = TTF_RenderText_Blended(gFont, "Space/Up:jump", textColor_tmp);
            SDL_Texture* spaceTexture = SDL_CreateTextureFromSurface(gRenderer, spaceSurface);
            SDL_Rect spaceRect = { space_rect.x + (space_rect.w - spaceSurface->w) / 2, space_rect.y + (space_rect.h - spaceSurface->h) / 2, spaceSurface->w, spaceSurface->h };
            SDL_RenderCopy(gRenderer, spaceTexture, nullptr, &spaceRect);
            SDL_DestroyTexture(spaceTexture);
            SDL_FreeSurface(spaceSurface);

        }



    }
    if (die == true) {
        SDL_Rect main_menu = { 619,300,326,300 };
        SDL_RenderCopy(gRenderer, menuTexture, NULL, &main_menu);

        if (optional == ENUM_REPLAY) {
            SDL_Color textColor_tmp = { 255,255,255 };
            if (status_pause == ENUM_HIDDEN_PAUSE) textColor_tmp = { 128,128,128 };

            SDL_Surface* replay = TTF_RenderText_Blended(gFont, "REPLAY <-", textColor_tmp);
            SDL_Texture* replayTex = SDL_CreateTextureFromSurface(gRenderer,replay);
            SDL_Rect replay_rect = { 619 + (main_menu.w - replay->w) / 2,350,replay->w,replay->h };
            SDL_RenderCopy(gRenderer, replayTex, NULL, &replay_rect);
            SDL_DestroyTexture(replayTex);
            SDL_FreeSurface(replay);



            SDL_Surface* exit = TTF_RenderText_Blended(gFont, "EXIT", textColor);
            SDL_Texture* exitTex = SDL_CreateTextureFromSurface(gRenderer, exit);
            SDL_Rect exit_rect = { 619 + (main_menu.w - exit->w) / 2,450,exit->w,exit->h };

            SDL_RenderCopy(gRenderer, exitTex, NULL, &exit_rect);
            SDL_DestroyTexture(exitTex);
            SDL_FreeSurface(exit);

        }

        if (optional == ENUM_EXIT) {
            SDL_Color textColor_tmp = { 255,255,255 };
            if (status_pause == ENUM_HIDDEN_PAUSE) textColor_tmp = { 128,128,128 };

            SDL_Surface* replay = TTF_RenderText_Blended(gFont, "REPLAY", textColor);
            SDL_Texture* replayTex = SDL_CreateTextureFromSurface(gRenderer, replay);
            SDL_Rect replay_rect = { 619 + (main_menu.w - replay->w) / 2,350,replay->w,replay->h };
            SDL_RenderCopy(gRenderer, replayTex, NULL, &replay_rect);
            SDL_DestroyTexture(replayTex);
            SDL_FreeSurface(replay);

            SDL_Surface* exit = TTF_RenderText_Blended(gFont, "EXIT <-", textColor_tmp);
            SDL_Texture* exitTex = SDL_CreateTextureFromSurface(gRenderer, exit);
            SDL_Rect exit_rect = { 619 + (main_menu.w - exit->w) / 2,450,exit->w,exit->h };

            SDL_RenderCopy(gRenderer, exitTex, NULL, &exit_rect);
            SDL_DestroyTexture(exitTex);
            SDL_FreeSurface(exit);
        }

    }
}

bool Menu::Pause() {
    if (status_pause == ENUM_SHOWN_PAUSE || die == true) {
        return true;
    }
    return false;
}

int Menu::GetStatus() {
    return status_menu;
}

void Menu::SetDie(bool _die) {
    die = _die;
    optional = ENUM_REPLAY;
}
