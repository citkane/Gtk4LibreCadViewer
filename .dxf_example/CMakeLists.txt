cmake_minimum_required(VERSION 3.16)
project(
  dxf_example
  VERSION 0.0.0
  DESCRIPTION "Example app for Gtk4LibrecadDxfViewer widget"
  LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
include(GNUInstallDirs)

find_package(Gtk4LibreCadViewer REQUIRED)

set(SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp)
set(LIB_DIRS ${CMAKE_CURRENT_LIST_DIR}/../.local/lib)

add_compile_options("-Wall" "-Wextra")
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Gtk4LibreCadViewer
                                              PkgConfig::GTK4 peel::Gtk)

set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "$ORIGIN/../lib")
target_compile_options(${PROJECT_NAME} PRIVATE -w)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
