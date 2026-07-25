#include "poseidon.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <limits>
#include <algorithm>

namespace Poseidon {

ResourceGridRouter::ResourceGridRouter() {}

ResourceGridRouter::~ResourceGridRouter() {}

/**
 * INDEX POSITIONING HELPER
 * Resolves a unique Node ID into its active internal vector table cache array index.
 */
int32_t ResourceGridRouter::find_node_index_by_id(uint32_t id) const {
    for (size_t i = 0; i < node_table_.size(); ++i) {
        if (node_table_[i].node_id == id) {
            return static_cast<int32_t>(i);
        }
    }
    return -1;
}

/**
 * 🗺️ TOPOLOGY CACHE MATRIX REGISTRATION PRIMITIVE 🗺️
 * Bundles geographic and volumetric metrics into a packed structural layout node in RAM.
 */
bool ResourceGridRouter::add_node_to_cache(uint32_t id, double lat, double lon, uint32_t liters, uint8_t contaminated) {
    if (find_node_index_by_id(id) != -1) {
        std::cerr << "❌ Ingest Exception: Node ID " << id << " already registered in memory." << std::endl;
        return false;
    }

    LogisticsNode node;
    node.node_id = id;
    node.latitude = lat;
    node.longitude = lon;
    node.resource_liters = liters;
    node.is_contaminated = contaminated;

    node_table_.push_back(node);
    return true;
}

/**
 * ⛓️ EDGE CONNECTIVITY REGISTRATION PRIMITIVE ⛓️
 * Tracks links and directional distance vectors between distinct logistics nodes.
 */
bool ResourceGridRouter::add_edge_link(uint32_t src_id, uint32_t dest_id, float weight) {
    if (find_node_index_by_id(src_id) == -1 || find_node_index_by_id(dest_id) == -1) {
        std::cerr << "❌ Edge Exception: Link reference points invalid. Node IDs must exist." << std::endl;
        return false;
    }

    LogisticsEdge edge;
    edge.source_node_id = src_id;
    edge.destination_node_id = dest_id;
    edge.distance_weight = weight;

    edge_table_.push_back(edge);
    return true;
}

/**
 * 📦 .POSEIDON BINARY STREAM EXTENSION EXPORTER 📦
 * Commits the entire active in-memory graph layout array directly to a physical file chunk.
 */
bool ResourceGridRouter::serialize_grid_to_disk(const std::string& host_path) {
    if (node_table_.empty()) return false;

    std::ofstream out(host_path, std::ios::binary | std::ios::out | std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "❌ Data Write Exception: Failed to secure hardware disk locks on: " << host_path << std::endl;
        return false;
    }

    out.write(reinterpret_cast<const char*>(node_table_.data()), node_table_.size() * sizeof(LogisticsNode));
    out.flush();
    out.close();

    std::cout << "✓ [.poseidon Serialized] Topology written to disk. Saved "
              << node_table_.size() << " nodes safely." << std::endl;
    return true;
}

/**
 * 📡 .POSEIDON FILE INGEST DESERIALIZER 📡
 * Streams a raw database file off disk and rebuilds the active logistics state table.
 */
bool ResourceGridRouter::deserialize_grid_from_disk(const std::string& host_path) {
    std::ifstream in(host_path, std::ios::binary | std::ios::ate);
    if (!in.is_open()) {
        std::cerr << "❌ Ingest Exception: Could not trace target database file: " << host_path << std::endl;
        return false;
    }

    std::streamsize file_size = in.tellg();
    in.seekg(0, std::ios::beg);

    size_t total_nodes_detected = file_size / sizeof(LogisticsNode);
    if (total_nodes_detected == 0) {
        in.close();
        return false;
    }

    node_table_.resize(total_nodes_detected);
    in.read(reinterpret_cast<char*>(node_table_.data()), file_size);
    in.close();

    std::cout << "✓ [.poseidon Loaded] In-memory database reconstructed. Tracking "
              << total_nodes_detected << " grid coordinates." << std::endl;
    return true;
}

/**
 * 🖨️ IMMUTABLE TOPOLOGY LIST VIEW PRINTER 🖨️
 * Reads the virtual vertex array maps to output asset parameters in a clean format.
 */
void ResourceGridRouter::display_cached_grid() const {
    std::cout << "\n🌊 [POSEIDON Resource View] Active Micro-Grid Nodes:" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "NODE_ID\tLATITUDE\tLONGITUDE\tCAPACITY (L)\tSTATUS" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    if (node_table_.empty()) {
        std::cout << "[Empty grid topology network layout]" << std::endl;
        return;
    }

    for (const auto& node : node_table_) {
        std::string status_str = node.is_contaminated ? "❌ COMPROMISED" : "✓ PURE";
        std::cout << node.node_id << "\t"
                  << node.latitude << "\t"
                  << node.longitude << "\t"
                  << node.resource_liters << "\t\t"
                  << status_str << std::endl;
    }
    std::cout << "--------------------------------------------------------" << std::endl;
}

/**
 * 🚀 BARE-METAL DIJKSTRA ROUTING SOLVER WITH CONTAMINATION BLACKLISTING 🚀
 * Calculates the shortest path between nodes while avoiding contaminated targets entirely.
 */
bool ResourceGridRouter::optimize_supply_route(uint32_t source_id, uint32_t dest_id, std::vector<uint32_t>& out_route_path) {
    out_route_path.clear();

    int32_t src_idx = find_node_index_by_id(source_id);
    int32_t dest_idx = find_node_index_by_id(dest_id);

    if (src_idx == -1 || dest_idx == -1) {
        std::cerr << "❌ Router Failure: Source or Destination node ID not found in cache." << std::endl;
        return false;
    }

    // Verify if source or target are compromised upfront
    if (node_table_[src_idx].is_contaminated || node_table_[dest_idx].is_contaminated) {
        std::cerr << "❌ Path Exception: Routing blocked. Source or Destination nodes are contaminated." << std::endl;
        return false;
    }

    size_t num_nodes = node_table_.size();
    std::vector<float> shortest_distances(num_nodes, std::numeric_limits<float>::max());
    std::vector<int32_t> parent_nodes(num_nodes, -1);
    std::vector<bool> visited_set(num_nodes, false);

    shortest_distances[src_idx] = 0.0f;

    for (size_t step = 0; step < num_nodes - 1; ++step) {
        // Find minimum distance index loop
        float min_dist = std::numeric_limits<float>::max();
        int32_t u_idx = -1;

        for (size_t v = 0; v < num_nodes; ++v) {
            // 🔒 CONTAMINATION GATING RULE: Skip node if it is marked contaminated
            if (node_table_[v].is_contaminated) continue;

            if (!visited_set[v] && shortest_distances[v] <= min_dist) {
                min_dist = shortest_distances[v];
                u_idx = static_cast<int32_t>(v);
            }
        }

        if (u_idx == -1) break; // Remaining nodes are unreachable or blacklisted

        visited_set[u_idx] = true;

        // Relax adjacent neighbors loops
        uint32_t u_id = node_table_[u_idx].node_id;
        for (const auto& edge : edge_table_) {
            if (edge.source_node_id == u_id) {
                int32_t neighbor_idx = find_node_index_by_id(edge.destination_node_id);
                if (neighbor_idx == -1 || node_table_[neighbor_idx].is_contaminated) continue;

                if (!visited_set[neighbor_idx] && shortest_distances[u_idx] != std::numeric_limits<float>::max() &&
                    shortest_distances[u_idx] + edge.distance_weight < shortest_distances[neighbor_idx]) {

                    shortest_distances[neighbor_idx] = shortest_distances[u_idx] + edge.distance_weight;
                    parent_nodes[neighbor_idx] = u_idx;
                }
            }
        }
    }

    if (shortest_distances[dest_idx] == std::numeric_limits<float>::max()) {
        std::cerr << "❌ Path Exception: No safe uncontaminated route exists between targets." << std::endl;
        return false;
    }

    // Reconstruction path sequence
    int32_t curr = dest_idx;
    while (curr != -1) {
        out_route_path.push_back(node_table_[curr].node_id);
        curr = parent_nodes[curr];
    }

    std::reverse(out_route_path.begin(), out_route_path.end());
    return true;
}

/**
 * 🖨️ OPTIMIZED SUPPLY PATH INTERACTIVE DISPLAY PRINTER 🖨️
 */
void ResourceGridRouter::display_optimized_route(const std::vector<uint32_t>& route_path) const {
    if (route_path.empty()) return;

    std::cout << "\n🔀 [POSEIDON Route Solution] Safest Shortest Path Calculated:" << std::endl;
    std::cout << "  Start Node";
    for (size_t i = 0; i < route_path.size(); ++i) {
        std::cout << " -> [" << route_path[i] << "]";
    }
    std::cout << " -> Arrived" << std::endl;
}

} // namespace Poseidon
