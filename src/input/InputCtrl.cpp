#include "input/InputCtrl.hpp"
#include "DxfViewer.hpp"
#include <peel/Gdk/ModifierType.h>

using namespace Gtk4::Librecad::input;

InputCtrl::InputCtrl(DxfViewer *dxf_viewer) {
    widget = dxf_viewer;

    auto def = widget->get_cursor();
    auto grabbing = Gdk::Cursor::create_from_name("grabbing", def);
    auto grab = Gdk::Cursor::create_from_name("grab", def);
    cursors = {{"def", def}, {"grabbing", grabbing}, {"grab", grab}};
}

auto InputCtrl::set_cursor(const char *cursor_name) -> void {
    if (cursor_name == state.cursor)
        return;

    auto it = cursors.find(cursor_name);
    if (it == cursors.end()) {
        g_warning("Cursor name %s not found.", cursor_name);
        return;
    }
    state.cursor = cursor_name;
    widget->set_cursor(it->second);
    widget->queue_draw();
}

auto InputCtrl::keyval_to_char(guint keyval) -> const char * {
    gunichar ch = gdk_keyval_to_unicode(keyval);
    if (ch == 0)
        return {};

    gchar buf[6];
    gint len = g_unichar_to_utf8(ch, buf);
    std::string text(buf, len);
    return text.c_str();
};

auto InputCtrl::modifier_to_char(Gdk::ModifierType mod) -> const char * {
    using namespace Mod;
    switch (mod) {
    case ALT:
        return "ALT";
    case BTN1:
        return "BTN1";
    case BTN2:
        return "BTN2";
    case BTN3:
        return "BTN3";
    case BTN4:
        return "BTN4";
    case BTN5:
        return "BTN5";
    case CTRL:
        return "CTRL";
    case HYPR:
        return "HYPR";
    case LOCK:
        return "LOCK";
    case META:
        return "META";
    case SHFT:
        return "SHFT";
    case SUPR:
        return "SUPR";
    case ALT_SHFT:
        return "ALT_SHFT";
    case CTRL_SHFT:
        return "CTRL_SHFT";
    case CTRL_ALT:
        return "CTRL_ALT";
    case CTRL_ALT_SHFT:
        return "CTRL_ALT_SHFT";
    default:
        return "NONE";
    }
}
