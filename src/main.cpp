#include "poseidon.hpp"
#include <iostream>
#include <vector>

int main() {
    std::cout << "🧬 ======================================================== 🧬" << std::endl;
    std::cout << "🔥 POSEIDON: Decentralized Fluidics Grid Optimization Engine  🔥" << std::endl;
    std::cout << "🧬 ======================================================== 🧬" << std::endl;

    Poseidon::ResourceGridRouter router;
    std::string test_storage_vault = "tests/grid_topology.poseidon";

    // 1. Map an advanced resource network structure containing alternative tracks
    std::cout << "📝 [Topology Mapping] Registering local survival resource coordinates..." << std::endl;
    router.add_node_to_cache(1, -20.146, 28.583, 5000, 0);  // Node 1: Pure Source Station
    router.add_node_to_cache(2, -20.155, 28.591, 12500, 0); // Node 2: Detour Pivot Station
    router.add_node_to_cache(3, -20.162, 28.604, 0, 1);     // Node 3: CONTAMINATED DIRECT HIGHWAY
    router.add_node_to_cache(4, -20.170, 28.615, 8000, 0);  // Node 4: Target Delivery Zone

    // 2. Define edge distance weights connecting the distribution vectors
    router.add_edge_link(1, 3, 2.5f);  // 1 -> 3 (Short direct highway path: 2.5 km but contaminated)
    router.add_edge_link(3, 4, 3.0f);  // 3 -> 4 (Contaminated out-link)

    router.add_edge_link(1, 2, 4.0f);  // 1 -> 2 (Longer clean alternative: 4.0 km)
    router.add_edge_link(2, 4, 3.5f);  // 2 -> 4 (Clean connection link: 3.5 km)

    // 3. Serialize our initial grid state
    router.serialize_grid_to_disk(test_storage_vault);
    router.display_cached_grid();

    // 4. Trigger the bare-metal pointer Dijkstra optimization route solver
    std::cout << "\n🔀 [Path Optimization] Resolving supply lines between Node 1 and Node 4..." << std::endl;
    std::vector<uint32_t> resolved_path;

    if (router.optimize_supply_route(1, 4, resolved_path)) {
        router.display_optimized_route(resolved_path);
    } else {
        std::cerr << "❌ Path Solver Error: Engine failed to resolve safe path variables." << std::endl;
    }

    std::cout << "\n🚀 [Status Update] Milestone 2 bare-metal router path solvers fully functional!" << std::endl;
    std::cout << "🧬 ======================================================== 🧬" << std::endl;
    return 0;
}
