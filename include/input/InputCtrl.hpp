#ifndef GTK4_LIBRECAD_INPUT_INPUTCTRL_HPP
#define GTK4_LIBRECAD_INPUT_INPUTCTRL_HPP

#include <peel/Gdk/Gdk.h>
#include <peel/Gdk/ModifierType.h>
#include <string>
#include <unordered_map>

namespace Gtk4::Librecad {
class DxfViewer;

namespace input {
using namespace peel;

namespace Mod {
using M = Gdk::ModifierType;

inline constexpr auto NONE = M::NO_MODIFIER_MASK;
inline constexpr auto ALT = M::ALT_MASK;
inline constexpr auto BTN1 = M::BUTTON1_MASK;
inline constexpr auto BTN2 = M::BUTTON2_MASK;
inline constexpr auto BTN3 = M::BUTTON3_MASK;
inline constexpr auto BTN4 = M::BUTTON4_MASK;
inline constexpr auto BTN5 = M::BUTTON5_MASK;
inline constexpr auto CTRL = M::CONTROL_MASK;
inline constexpr auto HYPR = M::HYPER_MASK;
inline constexpr auto LOCK = M::LOCK_MASK;
inline constexpr auto META = M::META_MASK;
inline constexpr auto SHFT = M::SHIFT_MASK;
inline constexpr auto SUPR = M::SUPER_MASK;
inline constexpr auto CTRL_SHFT = CTRL | SHFT;
inline constexpr auto CTRL_ALT = CTRL | ALT;
inline constexpr auto ALT_SHFT = SHFT | ALT;
inline constexpr auto CTRL_ALT_SHFT = CTRL_ALT | SHFT;
} // namespace Mod

class InputCtrl {
    using Mod_t = Gdk::ModifierType;
    using Cursor_t = RefPtr<Gdk::Cursor>;

  public:
    InputCtrl(DxfViewer *dxf_viewer);
    ~InputCtrl() = default;

  protected:
    auto set_cursor(const char *cursor_name) -> void;

    auto modifier_to_char(Gdk::ModifierType mod) -> const char *;

    auto keyval_to_char(guint keyval) -> const char *;

    inline static std::unordered_map<std::string, Cursor_t> cursors;

    inline static struct {
        Mod_t mod;
        std::unordered_map<guint, Mod_t> mod_key_;
        int bttn;
        double x;
        double y;
        const char *cursor;
    } state{Mod::NONE, {}, 0, 0.0, 0.0, "def"};

    DxfViewer *widget;
};

} // namespace input
} // namespace Gtk4::Librecad

#endif // GTK4_LIBRECAD_INPUT_INPUTCTRL_HPP
