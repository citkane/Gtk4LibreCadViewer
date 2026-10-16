file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(LIBRECAD_INSTALL
    ""
    CACHE PATH "Path to Librecad install dir")

file(GLOB lc_found "${LIBRECAD_INSTALL}/lib/liblckernel.*")
if(NOT lc_found)
  message(
    FATAL_ERROR "Please set LIBRECAD_INSTALL to the Librecad installation root")
endif()

set(LIBRECAD_SRC
    ""
    CACHE PATH "Path to Librecad src dir")

if(NOT IS_DIRECTORY "${LIBRECAD_SRC}/lcviewernoqt")
  message(STATUS "LIBRECAD_SRC=${LIBRECAD_SRC} not found")
  message(FATAL_ERROR "Please set LIBRECAD_SRC to the Librecad source root")
endif()

set(RPATHS "$ORIGIN:$ORIGIN/../lib64")
