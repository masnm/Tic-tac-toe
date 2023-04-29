#include "../include/enums.h"

#include <iostream>

void print_evaluation ( evaluation ev ) {
    switch ( ev ) {
    case eval_first:
        std::cout << "eval_first" << std::endl;
        break;
    case eval_second:
        std::cout << "eval_second" << std::endl;
        break;
    case eval_draw:
        std::cout << "eval_draw" << std::endl;
        break;
    case eval_play_more:
        std::cout << "eval_play_more" << std::endl;
        break;
    }
}
