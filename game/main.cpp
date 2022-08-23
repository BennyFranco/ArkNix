#include "galaga.h"

#ifdef main
#undef main
#endif

int main(int argc, char **args) {
    Galaga newGame;
    newGame.Awake();
    newGame.LoadScene("Scene1.yaml");
    // newGame.currentScene->Save("test.yaml");
    newGame.Run();
    newGame.Quit();
    return 0;
}