#ifndef SHELL_HPP
#define SHELL_HPP

#include "poseidon.hpp"

namespace Poseidon {

/**
 * 💻 THE OFFICIAL INTERACTIVE TERMINAL SHELL LOOP 💻
 * Hooks directly into standard input/output streams to spin an ultra-minimalist CLI workspace.
 * Parses user command strings and maps inputs straight onto low-level graph optimization methods.
 */
void launch_interactive_shell(ResourceGridRouter& router);

} // namespace Poseidon

#endif // SHELL_HPP
