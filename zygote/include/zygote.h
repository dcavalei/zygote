#pragma once

namespace zygote {
    constexpr std::string_view CONFIG_DEFAULT_PATH_FMT = "/etc/zygote/%s/config.yaml";
    constexpr std::string_view CONFIG_DEFAULT_MODE = "default_mode";
    constexpr std::string_view CONFIG_SYSCALLS = "syscalls";

    struct Cfg {
        bool debug{};
        std::string config_path{};
        std::vector<std::string> args{};
    };
}
