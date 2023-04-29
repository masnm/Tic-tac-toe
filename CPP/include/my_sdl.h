#pragma once

#include <SDL2/SDL.h>
#include <string>

class my_sdl {
    public:
        SDL_Window *window;
        SDL_Renderer *renderer;
        int32_t w_width, w_height;

    public:
        my_sdl ( int width = 800, int height = 600,
                 std::string name = "Tic Tac Toe" );
        ~my_sdl ();

    public:
        void sync_window_size ( void );
};
