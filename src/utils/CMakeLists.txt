add_library(utils "")
target_link_libraries(utils PRIVATE project_options project_warnings CONAN_PKG::docopt.cpp
        CONAN_PKG::fmt CONAN_PKG::spdlog)
target_sources(utils
        PRIVATE
        Tuple.cpp
        PUBLIC
       ${CMAKE_CURRENT_LIST_DIR}/Tuple.h
        )
target_include_directories(utils
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )
