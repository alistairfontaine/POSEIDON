# POSEIDON Operator Interface & Manual

This manifest details the command-line primitives configured to operate the decentralized fluidics optimization engine core.

---

## Micro-Grid Configuration Operations

### 1. Registering Resource Node Coordinates
To package and cache a resource node's spatial coordinates and capacity limits directly within the RAM cache tables, run the `node` primitive:
```text
poseidon-cli> node <id> <lat> <lon> <capacity_liters> <is_contaminated>
```
*Example:* To map a clean 5000L water station at coordinate index 1, type:
```text
poseidon-cli> node 1 -20.146 28.583 5000 0
```

### 2. Mapping Directional Topology Links
To establish a directional link connectivity edge and assign a distance path weight between nodes, run the `edge` primitive:
```text
poseidon-cli> edge <src_id> <dest_id> <distance_weight_km>
```
*Example:* To connect node 1 to node 2 across a 4.0 km path, type:
```text
poseidon-cli> edge 1 2 4.0
```

### 3. Executing Risk-Avoidance Path Optimization
To trigger the core Dijkstra traversal routing loop and calculate the shortest safe pathway between target nodes while blacklisting contaminated points, run the `optimize` primitive:
```text
poseidon-cli> optimize <source_node_id> <destination_node_id>
```

---

## 📦 Data Storage & Serialization Operations

### 1. Serializing Active Topology to Disk
To commit the entire active in-memory grid state into a dense binary container format file, run the `save` primitive:
```text
poseidon-cli> save network_backup.poseidon
```
This isolates the output file directly within the `tests/` directory channel.

### 2. Ingesting Existing Topology Containers
To stream a raw database file off disk and completely reconstruct your active in-memory tracking logs, run the `load` primitive:
```text
poseidon-cli> load network_backup.poseidon
```
