#include "Game.h"
using namespace std;

int main(int args,char *argv[]) {
    Game NewGame;
    NewGame.Init();
    NewGame.LoadMedia();
    NewGame.Run();
    if (NewGame.isQuit()) NewGame.Close();
    return 0;
}
