# POSEIDON Operator Interface & Manual

This manifest details the command-line primitives configured to operate the decentralized fluidics optimization engine core.

---

## Micro-Grid Configuration Operations

### 1. Initializing the Local Spatial Topology
To register distribution vertex matrices and cache local resource parameters inside RAM arrays, fire the tracking setup paths:
```text
poseidon-cli> node add <id> <lat> <lon> <capacity_liters>
```

### 2. Calculating the Safe Shortest Path Supply Lines
To trigger the bare-metal optimization routing loop and avoid contaminated coordinates automatically, fire the calculation token:
```text
poseidon-cli> route optimize <source_node_id> <destination_node_id>
```

### 3. Archive Log Serialization
To serialize the active in-memory topology state back into a dense binary container, type:
```text
poseidon-cli> record backup.poseidon
```
