#pragma once

#include <memory>
#include <cstdio>

namespace bpf {

    class Filter {
    public:
        friend class Builder;

        /** @brief load bpf filter to kernel */
        void load();

        /** @brief Filter destructor */
        ~Filter();
    private:
        /** context from seccomp lib */
        void *_ctx;
    };


} // bpf
