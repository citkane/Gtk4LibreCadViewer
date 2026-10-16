#ifndef GTK4_LIBRECAD_CAD_BUILDERS_HPP
#define GTK4_LIBRECAD_CAD_BUILDERS_HPP

// #ifdef CADEntityBuilder
// #undef CADEntityBuilder
// #endif

#include <cad/builders/circle.h>

namespace Gtk4::Librecad::cad {
using namespace lc::builder;
class Builders {
  public:
    Builders() {};
    ~Builders() = default;

    auto Circle() -> CircleBuilder * { return new CircleBuilder(); };
};
} // namespace Gtk4::Librecad::cad

#endif // GTK4_LIBRECAD_CAD_BUILDERS_HPP
