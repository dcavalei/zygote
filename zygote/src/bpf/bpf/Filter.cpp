#include "Filter.h"
#include "spdlog/spdlog.h"

#include <seccomp.h>

namespace bpf {
    namespace {

    }

    void Filter::load() {
        seccomp_load(_ctx);
        seccomp_release(_ctx);
        _ctx = nullptr;
    }

    Filter::~Filter() {
        if (_ctx) seccomp_release(_ctx);
    }


} // bpf
