set(FMT_TEST OFF CACHE BOOL "" FORCE)
set(FMT_DOC OFF CACHE BOOL "" FORCE)
set(FMT_HEADER_ONLY ON CACHE BOOL "" FORCE)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        8.1.1
)

FetchContent_MakeAvailable(fmt)