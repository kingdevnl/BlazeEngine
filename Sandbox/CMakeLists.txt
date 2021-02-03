project("Sandbox")


add_executable(Sandbox src/Sandbox.cpp)
target_include_directories(Sandbox PRIVATE "../Engine/src")

target_link_libraries(Sandbox
        PRIVATE
        BlazeEngine
        )

add_custom_command(TARGET Sandbox POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Sandbox/res ${CMAKE_BINARY_DIR}/bin/res)