#pragma once

#include <string>
#include <vector>

namespace conf {
    namespace exception {
        struct ConfigDefaultModeException : public std::exception {
            [[nodiscard]] const char *what() const noexcept override {
                return "Failed to load default_mode from config file!";
            }
        };

        struct ConfigUnknownModeException : public std::exception {
            [[nodiscard]] const char *what() const noexcept override {
                return "Failed to load default_mode from config file!";
            }
        };

        struct ConfigSyscallsException : public std::exception {
            [[nodiscard]] const char *what() const noexcept override {
                return "Failed to load syscalls from config file!";
            }
        };
    } // exception

    class Config {
    public:
        enum class MODE {
            ALLOW, DENY
        };

        virtual ~Config() = default;

        virtual MODE default_mode() = 0;

        virtual std::vector<std::pair<std::string, bool>> syscalls() = 0;
    };
} // conf
