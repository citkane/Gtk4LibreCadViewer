#!/usr/bin/bash

echo "dxf_viewer.sh: LCAD_SRC_DIR=$LCAD_SRC_DIR"

dxf_viewer_configure() (
    local pack=${1:-"dxf_viewer"}
    local build_dir=$BUILD_DIR/$pack
    local options=(
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
        -DCMAKE_BUILD_TYPE=$BUILD_TYPE
        -DLIBRECAD_SRC="$LCAD_SRC_DIR"
        -DLIBRECAD_INSTALL="$PREFIX"
    )
    echo "LCAD_SRC_DIR=$LCAD_SRC_DIR"
    echo "${options[@]}"

    rm -f ./compile_commands.json
    ${pack}_uninstall $pack
    cmake --install-prefix $PREFIX -G Ninja \
        -S . -B $build_dir \
        "${options[@]}"

    cp $build_dir/compile_commands.json ./compile_commands.json
)

dxf_viewer_build() (
    local pack=${1:-"dxf_viewer"}
    local build_dir=$BUILD_DIR/$pack
    echo "Building Gtk4LibrecadDxfViewer to $build_dir"
    cmake --build $build_dir --parallel
)

dxf_viewer_clean() {
    local pack=${1:-"dxf_viewer"}
    local build_dir=$BUILD_DIR/$pack
    rm -f ./compile_commands.json
    rm -rf $build_dir/peel-generated
    cmake --build $build_dir --target clean
}

dxf_viewer_install() {
    local pack=${1:-"dxf_viewer"}
    local build_dir=$BUILD_DIR/$pack
    cmake --install $build_dir
}

dxf_viewer_uninstall() {
    local pack=${1:-"dxf_viewer"}
    local build_dir=$BUILD_DIR/$pack
    local manifest=$build_dir/install_manifest.txt
    [[ ! -e $manifest ]] && return 0

    uninstall_manifest "$manifest"
}

dxf_viewer_delete() {
    local pack=${1:-"dxf_viewer"}
    local build_dir=$BUILD_DIR/$pack
    ${pack}_uninstall $pack
    rm -rf $build_dir
}
