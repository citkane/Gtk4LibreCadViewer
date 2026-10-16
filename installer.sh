#!/usr/bin/bash

BUILD_DIR=${BUILD_DIR:-"$(pwd)/.build"}
CLONE_DIR=${CLONE_DIR:-"$(pwd)/.clone"}
PREFIX=${PREFIX:-"$(pwd)/.local"}
BUILD_TYPE=${BUILD_TYPE:-"Debug"}
LCAD_SRC_DIR=${LCAD_SRC_DIR:-"$CLONE_DIR/librecad"}
LCAD_HASH=${LCAD_HASH:-"f972953aa3295543550a90f4c6ed1c4609124c59"}

echo "install.sh: LCAD_SRC_DIR=$LCAD_SRC_DIR"

source .scripts/build.sh
source .scripts/librecad.sh
source .scripts/peel.sh
source .scripts/dxf_viewer.sh
source .scripts/dxf_example.sh

run() {
    (
        local pack=$1
        set_path
        $pack
    )
}
set_path() {
    DEV_PATHS=("$PREFIX" "$PREFIX/bin" "$PREFIX/lib" "$PREFIX/lib64")
    for path in ${DEV_PATHS[@]}; do
        [[ $PATH == *"$path"* ]] && continue
        export PATH="$path:$PATH"
    done
}

install_peel() {
    peel_clone
    peel_build
    peel_install
}

reinstall() {
    (
        echo "reinstall: LCAD_SRC_DIR=$LCAD_SRC_DIR"
        local pack=$1
        set_path
        set -e
        ${pack}_delete
        ${pack}_configure
        ${pack}_build
        ${pack}_install
    )
}

update() {
    (
        local pack=$1
        set_path
        set -e
        print_same_line ${pack}_build
        print_same_line ${pack}_install
    )
}
