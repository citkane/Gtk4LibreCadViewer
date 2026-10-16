find_package(PkgConfig REQUIRED)

find_package(peel REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
peel_generate(Gtk 4.0 RECURSIVE)

find_package(Eigen3 REQUIRED)
find_package(RapidJSON)
set(LIBRECAD_LIB_DIRS ${LIBRECAD_INSTALL}/lib ${LIBRECAD_INSTALL}/lib64)
set(PROJ_LIBS
    PkgConfig::GTK4
    peel::Gtk
    Eigen3::Eigen
    dxfrw
    lckernel
    lcviewernoqt
    persistence)
