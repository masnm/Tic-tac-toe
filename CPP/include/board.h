#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "./enums.h"

class board {
    public:
        std::vector<std::vector<player>> data;
        const int32_t row = 3, col = 3;

    public:
        board ( void );
        board ( const board &other );

    public:
        void clear ( void );
        bool set_piece ( player _player, int32_t row, int32_t col );
        player get_piece ( int32_t row, int32_t col );
        board &operator= ( const board &other );

    public:
        evaluation board_evaluate ( void );

    public:
        void draw_board_sdl ( SDL_Renderer *renderer, int32_t width,
                              int32_t height );
};
