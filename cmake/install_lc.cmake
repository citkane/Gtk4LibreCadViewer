set(LC_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include/librecad3")
set(LC_INCLUDE_DIRS)

file(
  GLOB dirs CONFIGURE_DEPENDS
  LIST_DIRECTORIES true
  RELATIVE "${LIBRECAD_SRC}"
  "${LIBRECAD_SRC}/*")

set(LC_SRC_HEADER_DIRS "")
set(blacklist
    AppImage
    desktop
    docs
    doxygen
    lcUI
    lcUILua
    lcUIpy
    unittest
    res
    scripts)
foreach(dir IN LISTS dirs)
  if(dir MATCHES "^[.]"
     OR dir IN_LIST blacklist
     OR NOT IS_DIRECTORY "${LIBRECAD_SRC}/${dir}")
    continue()
  endif()
  list(APPEND LC_SRC_HEADER_DIRS "${dir}")
  list(APPEND LC_INCLUDE_DIRS "${LC_INCLUDE_DIR}/${dir}")
endforeach()

# Selectively install the LibreCad header files and licenses
foreach(dir IN LISTS LC_SRC_HEADER_DIRS)
  file(
    GLOB_RECURSE files CONFIGURE_DEPENDS
    LIST_DIRECTORIES false
    "${LIBRECAD_SRC}/${dir}/*")

  foreach(file IN LISTS files)
    get_filename_component(name "${file}" NAME)

    if(name MATCHES "[.]h$"
       OR name MATCHES "[.]hpp$"
       OR name MATCHES "[.]tcc$"
       OR name STREQUAL "LICENSE")
      file(RELATIVE_PATH rel_dir "${LIBRECAD_SRC}" "${file}")
      get_filename_component(rel_dir "${rel_dir}" DIRECTORY)
      file(COPY "${file}" DESTINATION "${LC_INCLUDE_DIR}/${rel_dir}")
    endif()
  endforeach()
endforeach()
