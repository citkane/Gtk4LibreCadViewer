#ifndef GTK4_LIBRECAD_CAD_HPP
#define GTK4_LIBRECAD_CAD_HPP

// #ifdef CADEntityBuilder
// #undef CADEntityBuilder
// #endif

#include "Builders.hpp"

namespace Gtk4::Librecad::cad {
class Cad {
  public:
    Cad() : builders{} {};
    ~Cad() = default;

    std::shared_ptr<Builders> builders;
};
} // namespace Gtk4::Librecad::cad

#endif // GTK4_LIBRECAD_CAD_HPP
