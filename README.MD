#To install all the deps execute:
`vcpkg install glfw3:x64-windows GLEW:x64-windows spdlog:x64-windows glm:x64-windows`
To build the project:

`cmake -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake -G"NMake Makefiles" -B build .`