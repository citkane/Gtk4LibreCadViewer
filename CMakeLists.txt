cmake_minimum_required(VERSION 3.16)
project(
  Gtk4LibreCadViewer
  VERSION 0.0.0
  DESCRIPTION "Example app for gtk dxf widget"
  LANGUAGES C CXX)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(env)
include(install_lc)
include(standards)
include(libraries)
include(includes)
include(pkgconfig)

add_compile_options("-Wall" "-Wextra")
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
target_link_directories(${PROJECT_NAME} PRIVATE ${LIBRECAD_LIB_DIRS})
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "${RPATHS}")
target_compile_options(${PROJECT_NAME} PRIVATE -w)
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJ_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${LC_INCLUDE_DIR}
                                                         ${LC_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJ_INCDIR})

include(install)
