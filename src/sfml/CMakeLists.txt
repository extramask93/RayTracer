add_executable(test_sfml test.cpp)
target_link_libraries(test_sfml PRIVATE project_warnings project_options CONAN_PKG::imgui-sfml)