add_library(raytracer "")
target_link_libraries(raytracer PRIVATE project_options project_warnings CONAN_PKG::docopt.cpp
        CONAN_PKG::fmt CONAN_PKG::spdlog)
target_link_libraries(raytracer PUBLIC utils)

target_sources(raytracer
        PRIVATE
        ray/Ray.cpp
        shapes/Sphere.cpp
        shapes/Shape.cpp
        lights/PointLight.cpp
        materials/Material.cpp
        intersections/Intersection.cpp
        intersections/Intersections.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/ray/Ray.h
        ${CMAKE_CURRENT_LIST_DIR}/shapes/Shape.h
        ${CMAKE_CURRENT_LIST_DIR}/materials/Material.h
        ${CMAKE_CURRENT_LIST_DIR}/intersections/Intersections.h
        ${CMAKE_CURRENT_LIST_DIR}/shapes/Sphere.h
        ${CMAKE_CURRENT_LIST_DIR}/lights/PointLight.h
        ${CMAKE_CURRENT_LIST_DIR}/intersections/Intersection.h
        )
target_include_directories(raytracer
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )
