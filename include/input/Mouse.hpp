#ifndef GTK4_LIBRECAD_INPUT_MOUSE_HPP
#define GTK4_LIBRECAD_INPUT_MOUSE_HPP

#include "input/InputCtrl.hpp"
#include <peel/Gdk/Gdk.h>

namespace Gtk4::Librecad {
class DxfViewer;

namespace input {
using namespace peel;

class Mouse : InputCtrl {
    friend class Gtk4::Librecad::DxfViewer;

  public:
    Mouse(DxfViewer *viewer);
    ~Mouse() = default;
    auto connect() -> void;

  protected:
  private:
    auto connect_motion() -> void;
    auto connect_scroll() -> void;
    auto connect_click() -> void;
    auto pan(double x, double y) -> void;
};

} // namespace input
} // namespace Gtk4::Librecad

#endif // GTK4_LIBRECAD_INPUT_MOUSE_HPP
