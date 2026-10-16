#ifndef GTK4_LIBRECAD_LIBRECAD_API_H
#define GTK4_LIBRECAD_LIBRECAD_API_H

#include "cad/Cad.hpp"

#include <cad/storage/documentimpl.h>
#include <cad/storage/storagemanagerimpl.h>
#include <documentcanvas.h>
#include <drawables/grid.h>
#include <painters/lccairopainter.tcc>

using painter_t = LcCairoPainter<CairoPainter::backend::Image>;

/**
 * @brief The offsreen buffer of the LibreCad API
 * */
struct librecad_fbo {
    /**
     * @brief The LibreCad cairo surface
     * */
    std::shared_ptr<painter_t> painter;
};

/**
 * @brief The LibreCad API
 * */
struct librecad_t {
    std::shared_ptr<Gtk4::Librecad::cad::Cad> cad;
    /**
     * @brief The LibreCad storage manager implementation
     * */
    std::shared_ptr<lc::storage::StorageManagerImpl> storage;
    /**
     * @brief The LibreCad document manager implementation
     * */
    std::shared_ptr<lc::storage::DocumentImpl> document;
    /**
     * @brief The LibreCad document canvas implementation
     * */
    std::shared_ptr<lc::viewer::DocumentCanvas> canvas;
    /**
     * @brief The LibreCad grid drawable implementation
     * */
    std::shared_ptr<lc::viewer::drawable::Grid> grid;
    /**
     * @brief The LibreCad offsreen framebuffer
     * */
    librecad_fbo fbo;
};

#endif // GTK4_LIBRECAD_LIBRECAD_API_H
