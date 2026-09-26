#include "include/base.h"
#include "GameLoop.h"

int main(int argc,char* argv[]) {
    GameEngine *e = createEngine();
    e->Init(e);

    gameLoop(e);

    e->Exit(e);
    return 0;
}
