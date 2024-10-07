#include "ConfigYaml.h"

#include <spdlog/spdlog.h>
#include <algorithm>
#include <cctype>

#include "zygote.h"

namespace conf {
    ConfigYaml::ConfigYaml(std::string_view path) : _config(YAML::LoadFile(path.data())) {
    }

    Config::MODE ConfigYaml::default_mode() {
        if (!_config[zygote::CONFIG_DEFAULT_MODE] ||
            !_config[zygote::CONFIG_DEFAULT_MODE].IsScalar())
            throw conf::exception::ConfigDefaultModeException();

        auto mode = _config[zygote::CONFIG_DEFAULT_MODE].as<std::string>();
        SPDLOG_DEBUG("Found default_mode({})", mode);
        std::transform(mode.begin(), mode.end(), mode.begin(), [](unsigned char c) { return std::tolower(c); });

        if (mode == "allow") return Config::MODE::ALLOW;
        else if (mode == "deny") return Config::MODE::DENY;
        else throw conf::exception::ConfigUnknownModeException();
    }

    std::vector<std::pair<std::string, bool>> ConfigYaml::syscalls() {
        if (!_config[zygote::CONFIG_SYSCALLS]) throw conf::exception::ConfigSyscallsException();

        YAML::Node node = _config[zygote::CONFIG_SYSCALLS];
        std::vector<std::pair<std::string, bool>> syscalls;

        syscalls.reserve(node.size());
        for (auto item: node) {
            auto key = item.first.as<std::string>();
            auto val = item.second.as<bool>();

            SPDLOG_DEBUG("Found syscall({}:{})", key, val);
            syscalls.emplace_back(key, val);
        }
        return syscalls;
    }
} // conf
