#include "shell.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

namespace Poseidon {

void launch_interactive_shell(ResourceGridRouter& router) {
    std::string line;
    std::cout << "\n🛡️ [POSEIDON Decentralized Router Active] Type 'help' to review command matrices." << std::endl;

    while (true) {
        std::cout << "poseidon-cli> ";
        if (!std::getline(std::cin, line)) break;

        if (line.empty()) continue;

        // Tokenize input string fragments cleanly using standard string stream arrays
        std::stringstream ss(line);
        std::string command;
        ss >> command;

        std::vector<std::string> args;
        std::string arg;
        while (ss >> arg) {
            args.push_back(arg);
        }

        // --- COMMAND ROUTING INDEX MATRIX ---
        if (command == "exit" || command == "quit") {
            std::cout << "👋 Deactivating optimization interfaces. System dropping offline." << std::endl;
            break;
        }
        else if (command == "help") {
            std::cout << "\n📋 Operational POSEIDON Core Primitives:" << std::endl;
            std::cout << "  node <id> <lat> <lon> <l> <err> - Packages and registers a resource node entry into memory" << std::endl;
            std::cout << "  edge <src_id> <dest_id> <weight> - Adds a directional link distance weight between nodes" << std::endl;
            std::cout << "  optimize <src_id> <dest_id>    - Triggers the Dijkstra solver to calculate safest paths" << std::endl;
            std::cout << "  view                           - Prints out a detailed grid list view of all cached nodes" << std::endl;
            std::cout << "  save <file.poseidon>           - Serializes the active graph matrix state directly to disk" << std::endl;
            std::cout << "  load <file.poseidon>           - Ingests a raw .poseidon file and rebuilds table caches" << std::endl;
            std::cout << "  exit / quit                    - Safely releases descriptors and terminates the shell\n" << std::endl;
        }
        else if (command == "node") {
            if (args.size() < 5) {
                std::cerr << "⚠️ Usage error: node <id> <lat> <lon> <capacity_liters> <is_contaminated>" << std::endl;
                continue;
            }
            uint32_t id = std::stoul(args[0]);
            double lat = std::stod(args[1]);
            double lon = std::stod(args[2]);
            uint32_t liters = std::stoul(args[3]);
            uint8_t contaminated = static_cast<uint8_t>(std::stoul(args[4]));

            if (router.add_node_to_cache(id, lat, lon, liters, contaminated)) {
                std::cout << "✓ Node successfully registered in RAM cache matrix." << std::endl;
            }
        }
        else if (command == "edge") {
            if (args.size() < 3) {
                std::cerr << "⚠️ Usage error: edge <src_id> <dest_id> <distance_weight>" << std::endl;
                continue;
            }
            uint32_t src_id = std::stoul(args[0]);
            uint32_t dest_id = std::stoul(args[1]);
            float weight = std::stof(args[2]);

            if (router.add_edge_link(src_id, dest_id, weight)) {
                std::cout << "✓ Directional topology link edge successfully mapped." << std::endl;
            }
        }
        else if (command == "optimize") {
            if (args.size() < 2) {
                std::cerr << "⚠️ Usage error: optimize <source_node_id> <destination_node_id>" << std::endl;
                continue;
            }
            uint32_t src_id = std::stoul(args[0]);
            uint32_t dest_id = std::stoul(args[1]);
            std::vector<uint32_t> route_path;

            std::cout << "🔀 Resolving supply lines. Executing risk-avoidance pointer traversals..." << std::endl;
            if (router.optimize_supply_route(src_id, dest_id, route_path)) {
                router.display_optimized_route(route_path);
            }
        }
        else if (command == "view") {
            router.display_cached_grid();
        }
        else if (command == "save") {
            if (args.empty()) {
                std::cerr << "⚠️ Usage error: save <filename.poseidon>" << std::endl;
                continue;
            }
            std::string dest_path = "tests/" + args[0]; // Isolate output files into tests/ directory channel
            router.serialize_grid_to_disk(dest_path);
        }
        else if (command == "load") {
            if (args.empty()) {
                std::cerr << "⚠️ Usage error: load <filename.poseidon>" << std::endl;
                continue;
            }
            std::string source_path = "tests/" + args[0];
            router.deserialize_grid_from_disk(source_path);
        }
        else {
            std::cerr << "❌ Unknown primitive: Type 'help' to review structural command arrays." << std::endl;
        }
    }
}

} // namespace Poseidon
