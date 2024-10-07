include(FetchContent)

#set(SPDLOG_BUILD_SHARED ON)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.14.1
)

FetchContent_MakeAvailable(spdlog)
target_compile_definitions(spdlog
        PUBLIC
        SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG
#        SPDLOG_FUNCTION=__PRETTY_FUNCTION__
)
