#pragma once

#include <atomic>
#include <mutex>
#include <thread>

#include "./board.h"

class ai_min_max {
    private:
        board input;
        std::pair<int32_t, int32_t> position;

    public:
        std::thread _thread;
        std::atomic<bool> done;
        std::mutex writing_output;
        std::pair<int32_t, int32_t> output;

    public:
        ai_min_max ( void );

    public:
        void populate_input ( board _input );
        void start_calculation ( void );

    public:
        bool done_calculation ( void );
};
