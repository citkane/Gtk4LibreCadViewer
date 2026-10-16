#include "DxfViewer.hpp"
// #include <cad/geometry/geocircle.h>
// #include <librecad3/lckernel/cad/geometry/geocoordinate.h>
// #include <librecad3/lckernel/cad/primitive/circle.h>
// #include <librecad3/lcviewernoqt/drawitems/lcvdrawitem.h>
#include <peel/Gio/ApplicationFlags.h>
#include <peel/Gtk/Gtk.h>

using namespace peel;
using namespace Gtk;
using namespace Gtk4::Librecad;

static void build_ui(Gio::Application *application) {
    auto app = application->cast<Application>();
    auto window = ApplicationWindow::create(app);
    auto dxf_viewer = DxfViewer::create();
    auto lc = dxf_viewer->lc;

    dxf_viewer->make_default_page();
    // LCVDrawItem_CSPtr dc = lc::entity::Circle(lc::geo::Coordinate{0,
    // 0}, 60.0, nullptr);

    // lc.canvas->drawEntity(*lc.fbo.painter);
    window->set_child(std::move(dxf_viewer));
    window->set_title("Gtk4 Dxf viewer");
    window->set_default_size(800, 600);
    window->present();
}

int main(int argc, char **argv) {
    auto app = Gtk::Application::create("org.Gtk4.SVG.Viewer",
                                        Gio::Application::Flags::DEFAULT_FLAGS);
    app->connect_activate(build_ui);
    return app->run(argc, argv);
}
