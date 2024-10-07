//
// Created by dcavalei on 04-10-2024.
//

#include "Executor.h"

#include <unistd.h>

#include <spdlog/spdlog.h>

namespace proc {
    Executor::Executor(std::string_view path, std::vector<std::string> const &args, bool env) {
        auto argv = std::vector<char const *>(args.size() + 1);

        for (const auto &arg: args)
            argv.emplace_back(arg.data());
        argv.emplace_back(nullptr);

        execve(path.data(), (char *const *) &argv[0], env ? environ : nullptr);
    }
} // proc
