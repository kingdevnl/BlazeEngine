project("Engine")

file(GLOB_RECURSE BLAZE_ENGINE_SRC
        "src/blaze/*"
)



find_package(spdlog CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)


find_path(STB_INCLUDE_DIRS "stb.h")
add_library(BlazeEngine STATIC ${BLAZE_ENGINE_SRC})


target_link_libraries(BlazeEngine PUBLIC
    spdlog::spdlog spdlog::spdlog_header_only
    glfw
    GLEW::GLEW
    glm
    EnTT::EnTT
    assimp::assimp
)

target_include_directories(BlazeEngine PRIVATE ${STB_INCLUDE_DIRS})