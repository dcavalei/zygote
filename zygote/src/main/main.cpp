#include <seccomp.h>
#include <CLI/CLI.hpp>

#include <spdlog/spdlog.h>
#include <dlfcn.h>

#include "bpf/Builder.h"
#include "conf/ConfigYaml.h"
#include "proc/Executor.h"

#include "zygote.h"

int main(int argc, char *argv[], char *envp[]) {
    CLI::App app("Broken noodle hates Ramen");
    spdlog::set_pattern("[%^%l%$] %!: %v");

    zygote::Cfg cfg;
    app.add_flag("-d,--debug", cfg.debug, "Enable debug logging");
    app.add_flag("--config", cfg.config_path, "Path to config file")->check(CLI::ExistingPath)->required();
    app.add_option("ARGS", cfg.args)->allow_extra_args()->required();

    CLI11_PARSE(app, argc, argv);

    spdlog::set_level(cfg.debug ? spdlog::level::debug : spdlog::level::info);

    SPDLOG_DEBUG("--debug '{}'", cfg.debug);
    SPDLOG_DEBUG("--config '{}'", cfg.config_path);
    SPDLOG_DEBUG("ARGS ['{}']", fmt::join(cfg.args, "', '"));

    conf::Config *ptr = new conf::ConfigYaml(cfg.config_path);
    auto filter = bpf::Builder(ptr)
            .allow_exec_path(cfg.args[0])
            .build();
    delete ptr;


//    auto handle = dlopen(cfg.args[0].c_str(), RTLD_LAZY);
//    if (!handle) {
//        fprintf(stderr, "%s\n", dlerror());
//        exit(EXIT_FAILURE);
//    }
//    SPDLOG_CRITICAL("{}", fmt::ptr(handle));
//    auto main_func_ptr = dlsym(handle, "main");
//    SPDLOG_CRITICAL("{}", fmt::ptr(main_func_ptr));

    // No more syscalls from this point onwards. TODO: make this crap better.
    filter->load();

    proc::Executor(cfg.args[0], cfg.args, true);

  return 0;
}
