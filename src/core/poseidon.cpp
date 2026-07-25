#include "poseidon.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

namespace Poseidon {

ResourceGridRouter::ResourceGridRouter() {}

ResourceGridRouter::~ResourceGridRouter() {}

/**
 * 🗺️ TOPOLOGY CACHE MATRIX REGISTRATION PRIMITIVE 🗺️
 * Bundles geographic and volumetric metrics into a packed structural layout node in RAM.
 */
bool ResourceGridRouter::add_node_to_cache(uint32_t id, double lat, double lon, uint32_t liters, uint8_t contaminated) {
    // Prevent duplicate node identifier collisions inside the table cache
    for (const auto& node : node_table_) {
        if (node.node_id == id) {
            std::cerr << "❌ Ingest Exception: Node ID " << id << " already registered in memory." << std::endl;
            return false;
        }
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

    // Write the raw array vector matrix bytes directly to storage sectors
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

} // namespace Poseidon
