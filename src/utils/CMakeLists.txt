add_library(utils "" Canvas.cpp Canvas.h CanvasPrinter.cpp CanvasPrinter.h)
target_link_libraries(utils PRIVATE project_options project_warnings
        )
target_sources(utils
        PRIVATE
        Tuple.cpp
        Color.cpp
        Matrix.cpp
        PUBLIC
       ${CMAKE_CURRENT_LIST_DIR}/Tuple.h
        ${CMAKE_CURRENT_LIST_DIR}/Color.h
        ${CMAKE_CURRENT_LIST_DIR}/Canvas.h
        ${CMAKE_CURRENT_LIST_DIR}/Matrix.h
        ${CMAKE_CURRENT_LIST_DIR}/Math.h
        ${CMAKE_CURRENT_LIST_DIR}/CanvasPrinter.h
        )
target_include_directories(utils
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )
