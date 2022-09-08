#include "galaga.h"

#ifdef main
#undef main
#endif

int main(int argc, char **args) {
    galaga::Galaga::Instance().Awake();
    galaga::Galaga::Instance().LoadScene("Scene2.yaml");
    galaga::Galaga::Instance().Run();
    galaga::Galaga::Instance().Quit();
    return 0;
}