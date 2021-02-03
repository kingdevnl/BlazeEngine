project("Engine")

# Find source files
file(GLOB_RECURSE BlazeEngine_SRC
        "src/blaze/*.h"
        "src/blaze/*.cpp"
        )

find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)


add_library(BlazeEngine STATIC ${BlazeEngine_SRC})

target_link_libraries(BlazeEngine PUBLIC
        glfw
        GLEW::GLEW
        spdlog::spdlog spdlog::spdlog_header_only
        glm
        )
