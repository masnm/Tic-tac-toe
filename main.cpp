#include <cassert>
#include <iostream>

#include "include/ai_min_max.h"
#include "include/board.h"
#include "include/my_sdl.h"
#include "include/states.h"

std::pair<int32_t, int32_t> get_position ( int32_t width, int32_t height,
                                           int32_t x, int32_t y ) {
    int32_t row = width / 3, col = height / 3;
    std::pair<int32_t, int32_t> ret = std::make_pair<int32_t, int32_t> ( 3, 3 );
    for ( int32_t i = 0; i < 3; ++i ) {
        if ( x < ( i + 1 ) * row ) {
            ret.first = i;
            break;
        }
    }
    for ( int32_t i = 0; i < 3; ++i ) {
        if ( y < ( i + 1 ) * col ) {
            ret.second = i;
            break;
        }
    }
    std::swap ( ret.first, ret.second );
    return ret;
}

int main ( int argc, char **argv ) {
    (void)argc;
    (void)argv;
    srand ( 123 );
    my_sdl msdl;
    board brd;
    player current_player = first;
    game_states current_state = game_waiting_to_start;
    ai_min_max ai;

    bool done = false;
    SDL_Event e;
    while ( !done ) {
        SDL_SetRenderDrawColor ( msdl.renderer, 0, 0, 0, 255 );
        SDL_RenderClear ( msdl.renderer );
        while ( SDL_PollEvent ( &e ) ) {
            switch ( e.type ) {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_KEYDOWN:
                if ( current_state == game_waiting_to_start )
                    current_state = next_state ( current_state );
                if ( e.key.keysym.sym == SDLK_r ) brd.clear ();
                if ( e.key.keysym.sym == SDLK_e ) {
                    print_evaluation ( brd.board_evaluate () );
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch ( e.button.button ) {
                case SDL_BUTTON_LEFT:
                    if ( current_player == first ) {
                        int x, y;
                        SDL_GetMouseState ( &x, &y );
                        std::pair<int32_t, int32_t> pos =
                            get_position ( msdl.w_width, msdl.w_height, x, y );
                        if ( brd.set_piece ( current_player, pos.first,
                                             pos.second ) ) {
                            current_player = second;
                            print_evaluation ( brd.board_evaluate () );
                            ai.populate_input ( brd );
                            ai.start_calculation ();
                        }
                    }
                    // if ( current_player == second ) {
                    //     std::cerr << std::boolalpha << ai.done_calculation ()
                    //               << std::endl;
                    // }
                    break;
                }
            }
        }
        if ( current_player == second ) {
            if ( ai.done_calculation () ) {
                ai._thread.join ();
                std::cerr << "AI " << ai.output.first << " " << ai.output.second
                          << std::endl;
                brd.set_piece ( current_player, ai.output.first,
                                ai.output.second );
                current_player = first;
                print_evaluation ( brd.board_evaluate () );
            }
        }
        msdl.sync_window_size ();
        brd.draw_board_sdl ( msdl.renderer, msdl.w_width, msdl.w_height );
        SDL_RenderPresent ( msdl.renderer );
    }

    return 0;
}
