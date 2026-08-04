#include <SDL3/SDL_version.h>
#include <SDL3/SDL_log.h>
#include <iostream>

int main() {
    constexpr int compiled = SDL_VERSION;
    const int linked = SDL_GetVersion();
    // std::cout<< "compiled: " << compiled << " linked: " << linked;
    SDL_Log("We compiled against SDL version %d.%d.%d ...\n",
        SDL_VERSIONNUM_MAJOR(compiled),
        SDL_VERSIONNUM_MINOR(compiled),
        SDL_VERSIONNUM_MICRO(compiled));

    SDL_Log("But we are linking against SDL version %d.%d.%d.\n",
        SDL_VERSIONNUM_MAJOR(linked),
        SDL_VERSIONNUM_MINOR(linked),
        SDL_VERSIONNUM_MICRO(linked));
    return 0;
}