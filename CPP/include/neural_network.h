#pragma once

#include <vector>

class node;

class neural_network {
    private:
        std::vector<int> layers;
        std::vector<std::vector<node>> network;

    public:
        neural_network ( std::vector<int> nodes );

    public:
};
