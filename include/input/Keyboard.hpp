#ifndef GTK4_LIBRECAD_INPUT_KEYBOARD_HPP
#define GTK4_LIBRECAD_INPUT_KEYBOARD_HPP

#include "input/InputCtrl.hpp"
#include <peel/Gdk/Gdk.h>
#include <peel/Gtk/EventControllerKey.h>

namespace Gtk4::Librecad {
class DxfViewer;

namespace input {
using namespace peel;

class Keyboard : InputCtrl {
    friend class Gtk4::Librecad::DxfViewer;

  public:
    Keyboard(DxfViewer *viewer);
    ~Keyboard() = default;
    auto connect() -> void;

  protected:
    auto keyval_to_modifier(guint keyval) -> Gdk::ModifierType;

  private:
    auto connect_press() -> void;

    // auto connect_motion() -> void;
    // auto connect_scroll() -> void;
    // auto connect_click() -> void;
    // auto pan(double x, double y) -> void;
};

} // namespace input
} // namespace Gtk4::Librecad

#endif // GTK4_LIBRECAD_INPUT_MOUSE_HPP
