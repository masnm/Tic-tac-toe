#include "../include/ai_min_max.h"

#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>

ai_min_max::ai_min_max ( void ) {
    done = false;
}

void ai_min_max::populate_input ( board _input ) {
    input = _input;
}

// enum evaluation { eval_first, eval_second, eval_draw, eval_play_more };
int32_t tic_tac_toe_ai ( ai_min_max *obj, board _board, int32_t depth = 10,
                         bool maximize = true ) {
    if ( depth <= 0 ) {
        return 0;
    }
    evaluation eval = _board.board_evaluate ();
    switch ( eval ) {
    case eval_first:
        return INT_MIN;
    case eval_second:
        return INT_MAX;
    case eval_draw:
        return 0;
        break;
    case eval_play_more:
        std::vector<std::pair<int32_t, int32_t>> vp;
        for ( int32_t i = 0; i < 3; ++i ) {
            for ( int32_t j = 0; j < 3; ++j ) {
                if ( _board.data[i][j] == none ) vp.emplace_back ( i, j );
            }
        }
        std::vector<std::tuple<int32_t, int32_t, int32_t>> vtp;
        for ( auto &item : vp ) {
            board nboard = _board;
            nboard.data[item.first][item.second] =
                ( maximize ? second : first );
            int32_t ths_cst =
                tic_tac_toe_ai ( obj, nboard, depth - 1, maximize ^ true );
            vtp.emplace_back ( item.first, item.second, ths_cst );
        }
        std::sort ( vtp.begin (), vtp.end (), [] ( auto &l, auto &r ) {
            return std::get<2> ( l ) > std::get<2> ( r );
        } );
        const std::lock_guard<std::mutex> lock ( obj->writing_output );
        if ( maximize ) {
            obj->output.first = std::get<0> ( vtp[0] );
            obj->output.second = std::get<1> ( vtp[0] );
            return std::get<2> ( vtp[0] );
        } else {
            obj->output.first = std::get<0> ( vtp.back () );
            obj->output.second = std::get<1> ( vtp.back () );
            return std::get<2> ( vtp.back () );
        }
        break;
    }
    assert ( false );
}

void thread_function ( ai_min_max *obj, board _board ) {
    obj->done = false;
    tic_tac_toe_ai ( obj, _board );
    obj->done = true;
}

void ai_min_max::start_calculation ( void ) {
    _thread = std::thread ( thread_function, this, input );
}

bool ai_min_max::done_calculation ( void ) {
    bool _done = done;
    return _done;
}
