#include "poseidon.hpp"
#include "shell.hpp"
#include <iostream>

int main() {
    std::cout << "🧬 ======================================================== 🧬" << std::endl;
    std::cout << "🔥 POSEIDON: Decentralized Fluidics Grid Command Prompt    🔥" << std::endl;
    std::cout << "🧬 ======================================================== 🧬" << std::endl;

    Poseidon::ResourceGridRouter router;

    // Launch the interactive interpretation command loop on bare metal
    Poseidon::launch_interactive_shell(router);

    return 0;
}
