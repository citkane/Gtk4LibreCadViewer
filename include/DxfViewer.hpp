#ifndef GTK4_LIBRECAD_DXFVIEWER_HPP
#define GTK4_LIBRECAD_DXFVIEWER_HPP

#include "LibreCadApi.h"
#include "input/Keyboard.hpp"
#include "input/Mouse.hpp"

#include <peel/Gtk/Gtk.h>
#include <peel/class.h>

namespace Gtk4::Librecad {
using namespace peel;

class DxfViewer final : public Gtk::DrawingArea {
    friend class input::Mouse;
    friend class input::InputCtrl;

    // Peel custom GObject class
    // @see
    // https://bugaevc.pages.gitlab.gnome.org/peel/custom-gobject-classes.html
    PEEL_SIMPLE_CLASS(DxfViewer, DrawingArea);

  public:
    /**
     * @brief Create a GObject of the Gtk4LibreCadViewer widget
     * */
    static FloatPtr<DxfViewer> create();

    /**
     * @brief The LibreCad API
     * */
    librecad_t lc;

    /**
     * @brief User utility to set a default empty page
     * */
    auto make_default_page() -> void;

  private:
    auto update_fbo(int w, int h) -> void;
    auto set_grid() -> void;
    /**
     * @brief Set the default displayed area for an empty drawing
     */
    auto default_display_area() -> void;

    /**
     * @brief Count the intitialisations.
     * GTK makes a double pass before rendering, so we count to register when
     * ready.
     * */
    int lc_init;

    std::shared_ptr<input::Mouse> input_mouse;
    std::shared_ptr<input::Keyboard> input_keyboard;

    // =============================
    // peel GObject intitialiser
    // =============================
    void init(Class *);
};

} // namespace Gtk4::Librecad

#endif // GTK4_LIBRECAD_DXFVIEWER_HPP
