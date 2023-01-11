#include "../include/board.h"

#include <iostream>

board::board ( void ) {
    data = std::vector<std::vector<player>> (
        row, std::vector<player> ( col, none ) );
}

board::board ( const board &other ) {
    data = other.data;
}

void board::clear ( void ) {
    for ( auto &_row : data )
        for ( auto &_col : _row )
            _col = none;
}

bool board::set_piece ( player _player, int32_t _row, int32_t _col ) {
    if ( data[_row][_col] != none ) return false;
    data[_row][_col] = _player;
    return true;
}

// Copied from:
// https://stackoverflow.com/questions/38334081/how-to-draw-circles-arcs-and-vector-graphics-in-sdl
void DrawCircle ( SDL_Renderer *renderer, int32_t centreX, int32_t centreY,
                  int32_t radius ) {
    const int32_t diameter = ( radius * 2 );

    int32_t x = ( radius - 1 );
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = ( tx - diameter );

    while ( x >= y ) {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint ( renderer, centreX + x, centreY - y );
        SDL_RenderDrawPoint ( renderer, centreX + x, centreY + y );
        SDL_RenderDrawPoint ( renderer, centreX - x, centreY - y );
        SDL_RenderDrawPoint ( renderer, centreX - x, centreY + y );
        SDL_RenderDrawPoint ( renderer, centreX + y, centreY - x );
        SDL_RenderDrawPoint ( renderer, centreX + y, centreY + x );
        SDL_RenderDrawPoint ( renderer, centreX - y, centreY - x );
        SDL_RenderDrawPoint ( renderer, centreX - y, centreY + x );

        if ( error <= 0 ) {
            ++y;
            error += ty;
            ty += 2;
        }

        if ( error > 0 ) {
            --x;
            tx += 2;
            error += ( tx - diameter );
        }
    }
}

board &board::operator= ( const board &other ) {
    data = other.data;
    return *this;
}

evaluation board::board_evaluate ( void ) {
    bool game = true;
    for ( auto &_row : data ) {
        for ( auto &val : _row )
            if ( val == none || val != _row[0] ) game = false;
        if ( game && _row[0] == first ) return eval_first;
        if ( game && _row[0] == second ) return eval_second;
    }
    for ( int32_t i = 0; i < row; ++i ) {
        game = true;
        for ( int32_t j = 0; j < col; ++j )
            if ( data[j][i] == none || data[j][i] != data[0][i] ) game = false;
        if ( game && data[0][i] == first ) return eval_first;
        if ( game && data[0][i] == second ) return eval_second;
    }
    game = true;
    for ( int32_t i = 0; i < 3; ++i ) {
        if ( data[i][i] == none || data[i][i] != data[0][0] ) game = false;
    }
    if ( game && data[0][0] == first ) return eval_first;
    if ( game && data[0][0] == second ) return eval_second;
    game = true;
    for ( int32_t i = 0; i < 3; ++i ) {
        if ( data[i][2 - i] == none || data[i][2 - i] != data[1][1] )
            game = false;
    }
    if ( game && data[1][1] == first ) return eval_first;
    if ( game && data[1][1] == second ) return eval_second;
    for ( int32_t i = 0; i < row; ++i )
        for ( int32_t j = 0; j < col; ++j )
            if ( data[i][j] == none ) return eval_play_more;
    return eval_draw;
}

void board::draw_board_sdl ( SDL_Renderer *renderer, int32_t width,
                             int32_t height ) {
    std::pair<int32_t, int32_t> cell_sz =
        std::make_pair<int32_t, int32_t> ( width / 3, height / 3 );
    // drawing the lines
    SDL_SetRenderDrawColor ( renderer, 255, 0, 0, 255 );
    for ( int32_t i = 1; i <= 2; ++i ) {
        SDL_RenderDrawLine ( renderer, i * cell_sz.first, 0, i * cell_sz.first,
                             height );
        SDL_RenderDrawLine ( renderer, 0, i * cell_sz.second, width,
                             i * cell_sz.second );
    }
    auto get_radious = [] ( std::pair<int32_t, int32_t> halfs ) {
        float half = std::min ( halfs.first, halfs.second );
        half *= 0.8;
        return int32_t ( half );
    };
    // drawing the pieces
    std::pair<int32_t, int32_t> current =
                                    std::make_pair<int32_t, int32_t> ( 0, 0 ),
                                half = std::make_pair<int32_t, int32_t> (
                                    cell_sz.first / 2, cell_sz.second / 2 );
    for ( int32_t i = 0; i < 3; ++i ) {
        for ( int32_t j = 0; j < 3; ++j ) {
            if ( data[i][j] == first ) {
                SDL_SetRenderDrawColor ( renderer, 0, 255, 0, 255 );
                DrawCircle ( renderer, current.first + half.first,
                             current.second + half.second,
                             get_radious ( half ) );
            } else if ( data[i][j] == second ) {
                SDL_SetRenderDrawColor ( renderer, 0, 0, 255, 255 );
                SDL_RenderDrawLine ( renderer, current.first, current.second,
                                     current.first + cell_sz.first,
                                     current.second + cell_sz.second );
                SDL_RenderDrawLine ( renderer, current.first + cell_sz.first,
                                     current.second, current.first,
                                     current.second + cell_sz.second );
            }
            current.first += cell_sz.first;
        }
        current.first = 0;
        current.second += cell_sz.second;
    }
}
