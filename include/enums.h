#pragma once

enum player { first, second, none };
enum evaluation { eval_first, eval_second, eval_draw, eval_play_more };

void print_evaluation ( evaluation ev );
