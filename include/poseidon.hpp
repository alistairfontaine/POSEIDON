#ifndef POSEIDON_HPP
#define POSEIDON_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace Poseidon {

#pragma pack(push, 1) // Enforce hard structural padding constraints for rapid binary serialization
/**
 * Packed Graph Vertex Node Structure
 * Size: Exactly 25 bytes per node, completely eliminating memory allocation leakage.
 */
struct LogisticsNode {
    uint32_t node_id;         // 32-bit unique geographical identification key index
    double   latitude;        // 64-bit micro-precision latitude tracking coordinate
    double   longitude;       // 64-bit micro-precision longitude tracking coordinate
    uint32_t resource_liters; // 32-bit localized volume capacity tracker metric
    uint8_t  is_contaminated; // 8-bit diagnostic anomaly state flag (0 = Pure, 1 = Compromised)
};
#pragma pack(pop)

#pragma pack(push, 1)
/**
 * Packed Directional Link Edge Structure
 * Size: Exactly 12 bytes, mapping directional supply channels between vertex indices.
 */
struct LogisticsEdge {
    uint32_t source_node_id;       // 32-bit tracking key of starting resource node
    uint32_t destination_node_id;  // 32-bit tracking key of ending destination node
    float    distance_weight;      // 32-bit floating point geographic distance path weight
};
#pragma pack(pop)

class ResourceGridRouter {
public:
    ResourceGridRouter();
    ~ResourceGridRouter();

    // Milestone 1 Core Primitives
    bool add_node_to_cache(uint32_t id, double lat, double lon, uint32_t liters, uint8_t contaminated);
    bool serialize_grid_to_disk(const std::string& host_path);
    bool deserialize_grid_from_disk(const std::string& host_path);
    void display_cached_grid() const;

    // 🚀 Milestone 2 Core Primitives (Bare-Metal Dijkstra Flow Optimizer)
    bool add_edge_link(uint32_t src_id, uint32_t dest_id, float weight);
    bool optimize_supply_route(uint32_t source_id, uint32_t dest_id, std::vector<uint32_t>& out_route_path);
    void display_optimized_route(const std::vector<uint32_t>& route_path) const;

    // State Tracking Getters
    size_t get_cached_node_count() const { return node_table_.size(); }
    const std::vector<LogisticsNode>& get_node_table() const { return node_table_; }
    size_t get_cached_edge_count() const { return edge_table_.size(); }

private:
    std::vector<LogisticsNode> node_table_; // In-memory database matrix array cache
    std::vector<LogisticsEdge> edge_table_; // In-memory topology link connectivity cache

    // Internal path solver help subroutines
    int32_t find_node_index_by_id(uint32_t id) const;
};


} // namespace Poseidon

#endif // POSEIDON_HPP
