#include "../include/my_sdl.h"

#include <SDL2/SDL.h>

#include <iostream>

my_sdl::my_sdl ( int width, int height, std::string name ) {
    using namespace std;
    if ( SDL_Init ( SDL_INIT_VIDEO ) != 0 ) {
        cerr << "Could not initialize sdl2: " << SDL_GetError () << endl;
        exit ( 1 );
    }
    window = SDL_CreateWindow ( name.c_str (), 100, 100, width, height,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if ( window == NULL ) {
        cerr << "SDL_CreateWindow Error: " << SDL_GetError () << endl;
        exit ( 1 );
    }
    renderer = SDL_CreateRenderer (
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( renderer == NULL ) {
        SDL_DestroyWindow ( window );
        cerr << "SDL_CreateRenderer Error: " << SDL_GetError () << endl;
        exit ( 1 );
    }

    w_width = width;
    w_height = height;
}

my_sdl::~my_sdl () {
    SDL_DestroyRenderer ( renderer );
    SDL_DestroyWindow ( window );
    SDL_Quit ();
}

void my_sdl::sync_window_size ( void ) {
    SDL_GetWindowSize ( window, &w_width, &w_height );
}
