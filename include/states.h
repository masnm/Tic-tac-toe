#pragma once

enum game_states {
    game_waiting_to_start = 0,
    game_playing = 1,
    game_game_over = 2,
};

game_states next_state ( game_states current );
game_states previous_state ( game_states current );
