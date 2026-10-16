#!/usr/bin/bash

peel_build() (
    local pack=peel
    local build_dir=$BUILD_DIR/$pack
    local src_dir=$CLONE_DIR/$pack

    rm -rf $build_dir
    meson setup --prefix=$PREFIX --buildtype=plain $build_dir $src_dir
    meson compile -C $build_dir
)

peel_clone() {
    local pack=peel
    local src_dir=$CLONE_DIR/$pack
    [[ -d "$src_dir" ]] || git clone https://gitlab.gnome.org/bugaevc/peel $src_dir
}

peel_install() {
    local pack=peel
    local build_dir=$BUILD_DIR/$pack
    meson install -C $build_dir
}

peel_uninstall() {
    local pack=peel
    local build_dir=$BUILD_DIR/$pack
    cd $build_dir
    ninja uninstall
}

peel_clean() {
    local pack=peel
    local build_dir=$BUID_DIR/$pack
    rm -rf $build_dir
}

peel_delete() {
    local pack=peel
    peel_uninstall $pack
    peel_clean $pack
}
