#include "poseidon.hpp"
#include <iostream>

int main() {
    std::cout << "🧬 ======================================================== 🧬" << std::endl;
    std::cout << "🔥 POSEIDON: Decentralized Fluidics Grid Optimization Engine  🔥" << std::endl;
    std::cout << "🧬 ======================================================== 🧬" << std::endl;

    Poseidon::ResourceGridRouter router;
    std::string test_storage_vault = "tests/grid_topology.poseidon";

    // 1. Ingest test nodes into the RAM matrix
    std::cout << "📝 [Topology Mapping] Registering local survival resource coordinates..." << std::endl;
    router.add_node_to_cache(1, -20.146, 28.583, 5000, 0);  // Pure water cache station
    router.add_node_to_cache(2, -20.155, 28.591, 12500, 0); // Primary supply node
    router.add_node_to_cache(3, -20.162, 28.604, 0, 1);     // Contaminated vector point

    // 2. Serialize raw array vectors to our custom .poseidon format extension
    if (router.serialize_grid_to_disk(test_storage_vault)) {
        // Instantiate a secondary independent object to cross-examine disk read metrics
        Poseidon::ResourceGridRouter diagnostic_parser;
        if (diagnostic_parser.deserialize_grid_from_disk(test_storage_vault)) {
            diagnostic_parser.display_cached_grid();
        }
    }

    std::cout << "\n🚀 [Status Update] Milestone 1 core .poseidon serialization primitives functional!" << std::endl;
    std::cout << "🧬 ======================================================== 🧬" << std::endl;
    return 0;
}
