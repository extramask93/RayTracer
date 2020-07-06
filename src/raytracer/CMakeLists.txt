add_library(raytracer "")
target_link_libraries(raytracer PRIVATE project_options project_warnings CONAN_PKG::docopt.cpp
        CONAN_PKG::fmt CONAN_PKG::spdlog)
target_link_libraries(raytracer PUBLIC utils)

target_sources(raytracer
        PRIVATE
        Ray.cpp
        Sphere.cpp
        Shape.cpp
        Intersection.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Ray.h
        ${CMAKE_CURRENT_LIST_DIR}/Shape.h
        ${CMAKE_CURRENT_LIST_DIR}/Sphere.h
        ${CMAKE_CURRENT_LIST_DIR}/Intersection.h
        )
target_include_directories(raytracer
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )
