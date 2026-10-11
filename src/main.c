#include "include/base.h"
#include "GameLoop.h"

int main() {
    GameEngine *e = createEngine();
    e->Init(e);

    e->GameLoop(e);

    e->Exit(e);

    e->DestoryEngine(e);

    return 0;
}
