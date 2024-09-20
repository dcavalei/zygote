find_package(PkgConfig REQUIRED)

pkg_check_modules(SYS_LIBSECCOMP libseccomp REQUIRED)
find_path(LIBSECCOMP_INCLUDE_DIRS
        NAMES seccomp.h
        HINTS ${SYS_LIBSECCOMP_INCLUDEDIR}
)

find_library(LIBSECCOMP_LIBRARIES
        NAMES seccomp
        HINTS ${SYS_LIBSECCOMP_LIBDIR}
)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libseccomp
        REQUIRED_VARS LIBSECCOMP_LIBRARIES
        FOUND_VAR LIBSECCOMP_FOUND
        VERSION_VAR SYS_LIBSECCOMP_VERSION
)
