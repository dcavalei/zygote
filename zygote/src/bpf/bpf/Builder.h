#pragma once

#include <memory>

#include "Filter.h"
#include "conf/Config.h"

namespace bpf {
    namespace exception {
        struct BuilderAddAllowException;
        struct BuilderAddDenyException;
    }

    /** @brief Builder class for Filter class */
    class Builder {
    public:
        /** @brief Represent the default mode of bpf filter */
        enum class Mode {
            AUDIT, DENY, ALLOW
        };

        /** @brief Init a new bpf filter according to Mode */
        explicit Builder(Mode mode);

        /** @brief Init a new bpf filter from a Config interface */
        explicit Builder(conf::Config *conf);

        /** @brief Return the underlying Filter, empty the Builder class */
        std::unique_ptr<Filter> build();

        /** @brief Allow syscall_nr syscall */
        Builder &allow(int syscall_nr);

        /** @brief Deny syscall_nr syscall */
        Builder &deny(int syscall_nr);

        /** @brief Allow to execve() a certain path, by comparing the ptr value (not the dereferenced value) */
        Builder &allow_exec_path(std::string_view path);

    private:
        /** @brief Common code for initialization */
        void _init_from_mode(Mode mode);

        /** Filter to be constructed */
        std::unique_ptr<Filter> _filter;
    };
}
