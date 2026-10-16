#!/usr/bin/bash

dxf_example_configure() (
    local pack=${1:-"dxf_example"}
    local src_dir=.$pack
    local build_dir=$BUILD_DIR/$pack
    local options=(
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
        -DCMAKE_BUILD_TYPE=$BUILD_TYPE
    )
    rm -f $src_dir/compile_commands.json
    ${pack}_uninstall $pack
    cmake --install-prefix $PREFIX -G Ninja \
        -S $src_dir -B $build_dir \
        "${options[@]}"

    cp $build_dir/compile_commands.json $src_dir/compile_commands.json
)
dxf_example_build() (
    local pack=${1:-"dxf_example"}
    local build_dir=$BUILD_DIR/$pack
    cmake --build $build_dir --config Release --parallel 6
)

dxf_example_install() {
    local pack=${1:-"dxf_example"}
    local build_dir=$BUILD_DIR/$pack
    cmake --install $build_dir
}

dxf_example_uninstall() {
    local pack=${1:-"dxf_example"}
    local build_dir=$BUILD_DIR/$pack
    local manifest="$build_dir/install_manifest.txt"
    [[ ! -e "$manifest" ]] && return 0

    uninstall_manifest "$manifest"
}

dxf_example_clean() {
    local pack=${1:-"dxf_example"}
    local build_dir=$BUILD_DIR/$pack
    rm -f ./compile_commands.json
    rm -rf $build_dir/peel-generated
    cmake --build $build_dir --target clean
}

dxf_example_delete() {
    local pack=${1:-"dxf_example"}
    local build_dir=$BUILD_DIR/$pack
    ${pack}_uninstall $pack
    rm -rf $build_dir
}
