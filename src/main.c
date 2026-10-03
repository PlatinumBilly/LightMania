#include "include/base.h"
#include "GameLoop.h"

int main(int argc,char* argv[]) {
    GameEngine *e = createEngine();
    e->Init(e);

    e->GameLoop(e);

    e->Exit(e);
    return 0;
}
