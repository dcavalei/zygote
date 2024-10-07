#include "Builder.h"

#include <seccomp.h>

#include <spdlog/spdlog.h>

namespace bpf {
    /** @brief From Mode to std::string */
    constexpr std::string_view to_string(Builder::Mode mode) {
        switch (mode) {
            case Builder::Mode::AUDIT:
                return "AUDIT";
            case Builder::Mode::DENY:
                return "DENY";
            case Builder::Mode::ALLOW:
                return "ALLOW";
            default:
                return "TODO";
        }
    }

    namespace exception {
        struct BuilderAddAllowException : public std::exception {
            explicit BuilderAddAllowException(int syscall_nr) : _nr(syscall_nr) {}

            [[nodiscard]] const char *what() const noexcept override {
                constexpr char msg[] = "Failed to add allow rule: syscall(%i)";
                static char buff[sizeof(msg) + 4]; // idc about multi-thread
                if (!buff[0]) std::snprintf(buff, sizeof(buff), msg, _nr);
                return buff;
            }

        private:
            int _nr;
        };

        struct BuilderAddDenyException : public std::exception {
            explicit BuilderAddDenyException(int syscall_nr) : _nr(syscall_nr) {}

            [[nodiscard]] const char *what() const noexcept override {
                constexpr char msg[] = "Failed to add deny rule: syscall(%i)";
                static char buff[sizeof(msg) + 3];
                if (!buff[0]) std::snprintf(buff, sizeof(buff), msg, _nr);
                return buff;
            }

        private:
            int _nr;
        };

    }

    Builder::Builder(Mode mode) {
        _init_from_mode(mode);
    }

    Builder::Builder(conf::Config *conf) {
        if (!conf) throw std::exception(/*TODO*/);

        // C++ switches suck
        switch (conf->default_mode()) {
            case conf::Config::MODE::ALLOW:
                _init_from_mode(Mode::ALLOW);
                break;
            case conf::Config::MODE::DENY:
                _init_from_mode(Mode::DENY);
                break;
        }

        for (const auto &[syscall, allowed]: conf->syscalls()) {
            if (int syscall_nr = seccomp_syscall_resolve_name(syscall.c_str()); syscall_nr != __NR_SCMP_ERROR) {
                SPDLOG_DEBUG("syscall '{}' resolved to int '{}'", syscall, syscall_nr);
                if (allowed) allow(syscall_nr);
                else deny(syscall_nr);
            } else {
                SPDLOG_CRITICAL("syscall {}", syscall);
                throw std::exception(/*TODO*/);
            }
        }
    }

    std::unique_ptr<Filter> Builder::build() {
        SPDLOG_DEBUG("moving filter...");
        return std::move(_filter);
    }


    Builder &Builder::allow(int syscall_nr) {
        if (seccomp_rule_add(_filter->_ctx, SCMP_ACT_ALLOW, syscall_nr, 0) < 0)
            throw exception::BuilderAddAllowException(syscall_nr);
        SPDLOG_DEBUG("syscall({})", syscall_nr);
        return *this;
    }

    Builder &Builder::deny(int syscall_nr) {
        if (seccomp_rule_add(_filter->_ctx, SCMP_ACT_KILL_PROCESS, syscall_nr, 0) < 0)
            throw exception::BuilderAddDenyException(syscall_nr);
        SPDLOG_DEBUG("syscall({})", syscall_nr);
        return *this;
    }

    Builder &Builder::allow_exec_path(std::string_view path) {
        // this will compare the ptr value, so the same ptr MUST be passed to execve() 1st argument.
        // TODO: find a better solution
        if (seccomp_rule_add(_filter->_ctx, SCMP_ACT_ALLOW, SCMP_SYS(execve), 1,
                             SCMP_A0(SCMP_CMP_EQ, (scmp_datum_t) path.data())) != 0)
            throw exception::BuilderAddAllowException(SCMP_SYS(execve));
        SPDLOG_INFO("execve() allowed for path '{}'", path);
        SPDLOG_DEBUG("execve() path ptr '{}'", fmt::ptr(path.data()));
        return *this;
    }

    void Builder::_init_from_mode(Mode mode) {
        SPDLOG_INFO("default rule '{}' all", to_string(mode));
        _filter = std::make_unique<Filter>();

        auto val = SCMP_ACT_ALLOW;
        switch (mode) {
            case Mode::AUDIT:
                val = SCMP_ACT_LOG;
                break;
            case Mode::DENY:
                val = SCMP_ACT_KILL_PROCESS;
                break;
            case Mode::ALLOW:
                val = SCMP_ACT_ALLOW;
                break;
        }
        _filter->_ctx = seccomp_init(val);
    }


}
