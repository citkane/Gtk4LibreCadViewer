#include "input/Keyboard.hpp"
#include "DxfViewer.hpp"
#include "input/InputCtrl.hpp"
#include <peel/Gdk/ModifierType.h>

using namespace Gtk4::Librecad::input;

Keyboard::Keyboard(DxfViewer *dxf_viewer) : InputCtrl(dxf_viewer) {}
auto Keyboard::connect() -> void { connect_press(); }

auto Keyboard::connect_press() -> void {
    using Ctrl = Gtk::EventControllerKey;
    using Mod_t = Gdk::ModifierType;

    auto ctrl_keys = Ctrl::create();
    widget->add_controller(ctrl_keys);

    ctrl_keys->connect_key_pressed(
        [this](Ctrl *ctrl, guint keyval, guint keycode, Mod_t mod) {
            auto mod_bit = keyval_to_modifier(keyval);
            if (mod_bit != Mod::NONE) {
                state.mod_key_[keycode] = mod_bit;
                state.mod |= mod_bit;
            }
            if (state.mod == Mod::SHFT) {
                set_cursor("grab");
            } else {
                set_cursor("def");
            }
            // auto key = keyval_to_char(keyval);
            // auto mod_char = modifier_to_char(state.mod);
            // g_message("key: %s, mod: %s", key, mod_char);
            return false;
        });

    ctrl_keys->connect_key_released(
        [this](Ctrl *ctrl, guint keyval, guint keycode, Mod_t mod) {
            if (state.mod_key_.erase(keycode)) {
                state.mod = Mod::NONE;
                for (const auto &entry : state.mod_key_)
                    state.mod |= entry.second;
            }
            if (state.mod == Mod::SHFT) {
                set_cursor("grab");
            } else {
                set_cursor("def");
            }
            // auto key = keyval_to_char(keyval);
            // auto mod_char = modifier_to_char(state.mod);
            // g_message("key: %s, mod: %s", key, mod_char);
        });
}

auto Keyboard::keyval_to_modifier(guint keyval) -> Gdk::ModifierType {
    switch (keyval) {
    case GDK_KEY_Shift_L:
    case GDK_KEY_Shift_R:
        return Mod::SHFT;
    case GDK_KEY_Control_L:
    case GDK_KEY_Control_R:
        return Mod::CTRL;
    case GDK_KEY_Alt_L:
    case GDK_KEY_Alt_R:
        return Mod::ALT;
    case GDK_KEY_Super_L:
    case GDK_KEY_Super_R:
        return Mod::SUPR;
    case GDK_KEY_Meta_L:
    case GDK_KEY_Meta_R:
        return Mod::META;
    case GDK_KEY_Hyper_L:
    case GDK_KEY_Hyper_R:
        return Mod::HYPR;
    default:
        return Mod::NONE;
    }
}
