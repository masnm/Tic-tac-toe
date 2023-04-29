#include "../include/neural_network.h"

#include <tuple>

class node {
    public:
        float value = 0.0;
        std::vector<std::tuple<node *, float, float>> connections;

    public:
        node () = default;
};

neural_network::neural_network ( std::vector<int> nodes ) {
    layers = nodes;
    network.resize ( nodes.size () );
    for ( int i = 0; i < int ( nodes.size () ); ++i ) {
        auto &row = network[i];
        row.emplace_back ( node () );
        if ( i == 0 ) continue;
        for ( int j = 0; j < nodes[i]; ++j )
            for ( int k = 0; k < nodes[i - 1]; ++k )
                // this is terible < pointer to a vector element >
                // in this case this is fine maybe
                network[i][j].connections.emplace_back ( &network[i - 1][k],
                                                         0.5, 0.5 );
    }
}
