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

class ResourceGridRouter {
public:
    ResourceGridRouter();
    ~ResourceGridRouter();

    // Milestone 1 Core Primitives
    bool add_node_to_cache(uint32_t id, double lat, double lon, uint32_t liters, uint8_t contaminated);
    bool serialize_grid_to_disk(const std::string& host_path);
    bool deserialize_grid_from_disk(const std::string& host_path);
    void display_cached_grid() const;

    // State Tracking Getters
    size_t get_cached_node_count() const { return node_table_.size(); }
    const std::vector<LogisticsNode>& get_node_table() const { return node_table_; }

private:
    std::vector<LogisticsNode> node_table_; // In-memory database matrix array cache
};

} // namespace Poseidon

#endif // POSEIDON_HPP
