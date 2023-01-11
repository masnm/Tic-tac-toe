#include "../include/states.h"

game_states next_state ( game_states current ) {
    if ( current >= game_game_over )
        current = game_waiting_to_start;
    else
        current = game_states ( int ( current ) + 1 );
    return current;
}

game_states previous_state ( game_states current ) {
    if ( current == game_waiting_to_start )
        current = game_game_over;
    else
        current = game_states ( int ( current ) - 1 );
    return current;
}
