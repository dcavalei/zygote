#pragma once


#include <string_view>

#include "Config.h"

#include "yaml-cpp/yaml.h"


namespace conf {

    class ConfigYaml : public Config {
    public:
        ConfigYaml() = default;

        ~ConfigYaml() override = default;

        explicit ConfigYaml(std::string_view path);


        MODE default_mode() override;

        std::vector<std::pair<std::string, bool>> syscalls() override;

    private:
        YAML::Node _config;
    };
} // conf
