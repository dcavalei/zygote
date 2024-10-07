#pragma once

#include <vector>
#include <string>

namespace proc {

    class Executor {
    public:
        Executor() = default;

        Executor(std::string_view path, std::vector<std::string> const &args, bool env = true);
    };

} // proc
