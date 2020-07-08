option(CPP_STARTER_USE_IMGUI "Enable compilation of ImGui sample" OFF)

# imgui example
if(RAYTRACER_USE_SFML)
  message("Using SFML")
  add_subdirectory(sfml)
endif()
add_subdirectory(utils)
add_subdirectory(raytracer)
# Generic test that uses conan libs
add_executable(intro main.cpp)
add_executable(sphere sphere.cpp)
target_link_libraries(
        sphere PRIVATE project_options project_warnings utils raytracer CONAN_PKG::docopt.cpp
        CONAN_PKG::fmt CONAN_PKG::spdlog)
target_link_libraries(
  intro PRIVATE project_options project_warnings utils CONAN_PKG::docopt.cpp
                CONAN_PKG::fmt CONAN_PKG::spdlog)
