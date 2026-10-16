#include "input/Mouse.hpp"
#include "DxfViewer.hpp"
#include "input/InputCtrl.hpp"
#include <peel/Gdk/ModifierType.h>

using namespace Gtk4::Librecad::input;

Mouse::Mouse(DxfViewer *dxf_viewer) : InputCtrl(dxf_viewer) {}
auto Mouse::connect() -> void {
    connect_motion();
    connect_scroll();
    connect_click();
}

auto Mouse::connect_motion() -> void {
    using namespace Gtk;

    auto ctrl_motion = EventControllerMotion::create();
    widget->add_controller(ctrl_motion);

    ctrl_motion->connect_motion(
        [this](EventControllerMotion *, double x, double y) -> void {
            if (state.mod == Mod::SHFT) {
                pan(x, y);
            }
            state.x = x;
            state.y = y;
        });
}

auto Mouse::connect_scroll() -> void {
    using namespace Gtk;
    using Flags = EventControllerScroll::Flags;

    auto ctrl_scroll = EventControllerScroll::create(Flags::VERTICAL);
    widget->add_controller(ctrl_scroll);

    ctrl_scroll->connect_scroll(
        [this](EventControllerScroll *ctrl, double, double gtk_y) -> bool {
            auto factor = (gtk_y < 0) ? 1.1 : 0.9;
            auto lc = widget->lc;

            lc.canvas->zoom(*lc.fbo.painter, factor, true, state.x, state.y);
            widget->queue_draw();
            return true;
        });
}

auto Mouse::connect_click() -> void {
    using namespace Gtk;

    auto ctrl_click = GestureClick::create();
    widget->add_controller(ctrl_click);

    ctrl_click->set_button(0);
    ctrl_click->connect_pressed(
        [this](GestureClick *ctrl, int count, double, double) {
            // state.mod = ctrl->get_current_event_state();
            // state.bttn = ctrl->get_current_button();
        });

    ctrl_click->connect_released([this](GestureClick *, int, double, double) {
        // state.mod = Gdk::ModifierType::NO_MODIFIER_MASK;
        // state.bttn = 0;
    });
}

auto Mouse::pan(double x, double y) -> void {
    // if (state.mod != Mod::SHFT)
    //     return;

    // set_cursor("grabbing");
    auto lc = widget->lc;
    lc.canvas->pan(*lc.fbo.painter, x - state.x, y - state.y);
    widget->queue_draw();
}
