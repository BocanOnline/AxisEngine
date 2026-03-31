include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY  https://github.com/BocanOnlineVendors/spdlog.git
    GIT_TAG         origin/v1.x
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE
)

message("Fetching spdlog...")
FetchContent_MakeAvailable(spdlog)
