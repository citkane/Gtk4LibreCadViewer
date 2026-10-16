#!/usr/bin/bash

librecad_clone() {
    local pack=${1:-"librecad"}
    local src_dir=${LCAD_SRC_DIR:-$CLONE_DIR/$pack}
    local url=https://github.com/LibreCAD/LibreCAD_3.git
    [[ -e "$src_dir/CMakeLists.txt" ]] && return 0

    echo "Cloning LibreCad to $src_dir"
    rm -rf "$src_dir"
    git clone --recurse-submodules -b master --single-branch $url $src_dir
    (
        cd $src_dir
        local branch_name=$(git branch --show-current)
        echo "On branch $branch_name"
        if [[ $branch_name != $LCAD_HASH ]]; then
            git checkout $LCAD_HASH
            git switch -c $LCAD_HASH
            echo "Switched to branch $LCAD_HASH"
        fi
    )
}

librecad_configure() {
    local pack=${1:-"librecad"}
    local build_dir=$BUILD_DIR/$pack
    local src_dir=${LCAD_SRC_DIR:-$CLONE_DIR/$pack}
    local options=(
        -DWITH_QT_UI=OFF
        -DWITH_LUACMDINTERFACE=OFF
        -DWITH_UNITTESTS=OFF
        -DWITH_RENDERING_UNITTESTS=OFF
        -DWITH_CAIRO=ON
        -DWITH_PYTHONSCRIPT=OFF
        -DWITH_LCDXFDWG=ON
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
        -DCMAKE_BUILD_TYPE=$BUILD_TYPE
        -DCMAKE_C_STANDARD=17
        -DCMAKE_CXX_STANDARD=17
        -DCMAKE_C_STANDARD_REQUIRED=ON
        -DCMAKE_CXX_STANDARD_REQUIRED=ON
        -DCMAKE_C_EXTENSIONS=OFF
        -DCMAKE_CXX_EXTENSIONS=OFF
        -DCMAKE_C_COMPILER_LAUNCHER=ccache
        -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
        -DCMAKE_POLICY_DEFAULT_CMP0175=OLD
        -Wno-author
    )
    rm -rf "$src_dir/compile_commands.json"

    cmake --install-prefix $PREFIX -G Ninja \
        -S "$src_dir" -B "$build_dir" \
        "${options[@]}"

    cp "$build_dir/compile_commands.json" "$src_dir/compile_commands.json"
}
librecad_build() {
    local pack=${1:-"librecad"}
    local build_dir=$BUILD_DIR/$pack
    echo "Building LibreCad to $build_dir"
    GIT_DIR="$LCAD_SRC_DIR/.git" \
        GIT_WORK_TREE="$LCAD_SRC_DIR" \
        cmake --build "$build_dir" --parallel
}

librecad_install() {
    local pack=${1:-"librecad"}
    local build_dir=$BUILD_DIR/$pack
    echo "Installing LibreCad to $PREFIX"
    cmake --install $build_dir
}

librecad_uninstall() {
    local pack=${1:-"librecad"}
    local build_dir=$BUILD_DIR/$pack
    local manifest=$build_dir/install_manifest.txt
    [[ ! -e $manifest ]] && return 0

    uninstall_manifest "$manifest"
}

librecad_delete() {
    local pack=${1:-"librecad"}
    local build_dir=$BUILD_DIR/$pack
    ${pack}_uninstall $pack
    rm -rf $build_dir
}

librecad_clean() {
    local pack=${1:-"librecad"}
    local build_dir=$BUILD_DIR/$pack
    cmake --build "$build_dir" --target clean
}
