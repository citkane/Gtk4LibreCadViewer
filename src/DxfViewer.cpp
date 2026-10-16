#include "DxfViewer.hpp"
#include "input/InputCtrl.hpp"

PEEL_CLASS_IMPL(Gtk4::Librecad::DxfViewer, "Gtk4LibrecadDxfViewer",
                peel::Gtk::DrawingArea)
using namespace Gtk4::Librecad;
using namespace peel;

void DxfViewer::init(Class *) {
    using lc::storage::DocumentImpl;
    using lc::storage::StorageManagerImpl;
    using lc::viewer::DocumentCanvas;

    lc_init = 0;
    lc.storage = std::make_shared<StorageManagerImpl>();
    lc.document = std::make_shared<DocumentImpl>(lc.storage);
    lc.canvas = std::make_shared<DocumentCanvas>(lc.document);
    lc.cad = std::make_shared<cad::Cad>();

    input_mouse = std::make_shared<input::Mouse>(this);
    input_keyboard = std::make_shared<input::Keyboard>(this);
    input_mouse->connect();
    input_keyboard->connect();

    set_focusable(true);
    set_hexpand(true);
    set_vexpand(true);
    update_fbo(1, 1);

    set_draw_func([this](Gtk::DrawingArea *, cairo_t *ctx, int w, int h) {
        auto surface = lc.fbo.painter->getCairoSurface();
        cairo_set_source_surface(ctx, surface, 0, 0);
        // GTK does 2 init passes before rendering,
        // so we tally and wait before setting the default.
        if (lc_init < 2) {
            default_display_area();
            lc_init++;
        }

        lc.canvas->render(*lc.fbo.painter, VIEWER_BACKGROUND);
        lc.canvas->render(*lc.fbo.painter, VIEWER_DOCUMENT);
        cairo_paint(ctx);
    });

    connect_resize([this](DrawingArea *, int w, int h) {
        lc.canvas->newDeviceSize(w, h);
        lc.fbo.painter.reset();
        update_fbo(w, h);
    });

    connect_destroy([this](Widget *) { lc.fbo.painter.reset(); });
}

auto DxfViewer::update_fbo(int w, int h) -> void {
    auto surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h);
    auto ctx = cairo_create(surface);
    lc.fbo.painter = std::make_shared<painter_t>(surface, ctx);
}

auto DxfViewer::default_display_area() -> void {
    using lc::geo::Area;
    using lc::geo::Coordinate;
    auto display_area = Area{Coordinate(-50.0, -50.0), Coordinate(50.0, 50.0)};

    lc.canvas->setDisplayArea(*lc.fbo.painter, display_area);
}

auto DxfViewer::make_default_page() -> void {
    using lc::viewer::drawable::Grid;

    auto l_minor = lc::Color(0.8, 0.8, 0.8);
    auto l_major = lc::Color(0.4, 0.4, 0.4);
    auto background_colour = lc::Color{0.85, 0.85, 0.85, 1.0};
    lc.canvas->setPainterBgColor(background_colour);
    lc.grid = std::make_shared<Grid>(20, l_minor, l_major);
    lc.canvas->background().connect<Grid, &Grid::draw>(lc.grid.get());
};

// =============================
// peel GObject intitialiser
// =============================
inline void DxfViewer::Class::init() {}
FloatPtr<DxfViewer> DxfViewer::create() {
    auto viewer = Object::create<DxfViewer>();
    return viewer;
}
