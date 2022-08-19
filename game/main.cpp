#include "galaga.h"

int main(int argc, char **args) {
    Galaga newGame;
    newGame.Awake();
    newGame.LoadScene("Scene1.yaml");
    // newGame.currentScene->Save();
    newGame.Run();
    newGame.Quit();
    return 0;
}