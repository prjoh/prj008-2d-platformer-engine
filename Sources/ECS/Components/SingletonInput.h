#pragma once

#include <raylib.h>

#include <ECS/Component.h>
#include <Math/Vector2.h>


namespace zv { class CommandSystem; }

namespace zv
{
  // Keyboard keys (US keyboard layout)
  // NOTE: Use GetKeyPressed() to allow redefining
  // required keys for alternative layouts
  enum class eKeyboardKey : s32 {
    None            = 0,        // Key: None, used for no key pressed
    // Alphanumeric keys
    Apostrophe      = 39,       // Key: '
    Comma           = 44,       // Key: ,
    Minus           = 45,       // Key: -
    Period          = 46,       // Key: .
    Slash           = 47,       // Key: /
    Zero            = 48,       // Key: 0
    One             = 49,       // Key: 1
    Two             = 50,       // Key: 2
    Three           = 51,       // Key: 3
    Four            = 52,       // Key: 4
    Five            = 53,       // Key: 5
    Six             = 54,       // Key: 6
    Seven           = 55,       // Key: 7
    Eight           = 56,       // Key: 8
    Nine            = 57,       // Key: 9
    Semicolon       = 59,       // Key: ;
    Equal           = 61,       // Key: =
    A               = 65,       // Key: A | a
    B               = 66,       // Key: B | b
    C               = 67,       // Key: C | c
    D               = 68,       // Key: D | d
    E               = 69,       // Key: E | e
    F               = 70,       // Key: F | f
    G               = 71,       // Key: G | g
    H               = 72,       // Key: H | h
    I               = 73,       // Key: I | i
    J               = 74,       // Key: J | j
    K               = 75,       // Key: K | k
    L               = 76,       // Key: L | l
    M               = 77,       // Key: M | m
    N               = 78,       // Key: N | n
    O               = 79,       // Key: O | o
    P               = 80,       // Key: P | p
    Q               = 81,       // Key: Q | q
    R               = 82,       // Key: R | r
    S               = 83,       // Key: S | s
    T               = 84,       // Key: T | t
    U               = 85,       // Key: U | u
    V               = 86,       // Key: V | v
    W               = 87,       // Key: W | w
    X               = 88,       // Key: X | x
    Y               = 89,       // Key: Y | y
    Z               = 90,       // Key: Z | z
    LeftBracket    = 91,       // Key: [
    Backslash       = 92,       // Key: '\'
    RightBracket   = 93,       // Key: ]
    Grave           = 96,       // Key: `
    // Function keys
    Space           = 32,       // Key: Space
    Escape          = 256,      // Key: Esc
    Enter           = 257,      // Key: Enter
    Tab             = 258,      // Key: Tab
    Backspace       = 259,      // Key: Backspace
    Insert          = 260,      // Key: Ins
    Delete          = 261,      // Key: Del
    Right           = 262,      // Key: Cursor right
    Left            = 263,      // Key: Cursor left
    Down            = 264,      // Key: Cursor down
    Up              = 265,      // Key: Cursor up
    PageUp         = 266,      // Key: Page up
    PageDown       = 267,      // Key: Page down
    Home            = 268,      // Key: Home
    End             = 269,      // Key: End
    CapsLocks       = 280,      // Key: Caps lock
    ScrollLock     = 281,      // Key: Scroll down
    NumLock        = 282,      // Key: Num lock
    PrintScreen    = 283,      // Key: Print screen
    Pause           = 284,      // Key: Pause
    F1              = 290,      // Key: F1
    F2              = 291,      // Key: F2
    F3              = 292,      // Key: F3
    F4              = 293,      // Key: F4
    F5              = 294,      // Key: F5
    F6              = 295,      // Key: F6
    F7              = 296,      // Key: F7
    F8              = 297,      // Key: F8
    F9              = 298,      // Key: F9
    F10             = 299,      // Key: F10
    F11             = 300,      // Key: F11
    F12             = 301,      // Key: F12
    LeftShift      = 340,      // Key: Shift left
    LeftControl    = 341,      // Key: Control left
    LeftAlt        = 342,      // Key: Alt left
    LeftSuper      = 343,      // Key: Super left
    RightShift     = 344,      // Key: Shift right
    RightControl   = 345,      // Key: Control right
    RightAlt       = 346,      // Key: Alt right
    RightSuper     = 347,      // Key: Super right
    KBMenu         = 348,      // Key: KB menu
    // Keypad keys
    KeyPad0            = 320,      // Key: Keypad 0
    KeyPad1            = 321,      // Key: Keypad 1
    KeyPad2            = 322,      // Key: Keypad 2
    KeyPad3            = 323,      // Key: Keypad 3
    KeyPad4            = 324,      // Key: Keypad 4
    KeyPad5            = 325,      // Key: Keypad 5
    KeyPad6            = 326,      // Key: Keypad 6
    KeyPad7            = 327,      // Key: Keypad 7
    KeyPad8            = 328,      // Key: Keypad 8
    KeyPad9            = 329,      // Key: Keypad 9
    KeyPadDecimal      = 330,      // Key: Keypad .
    KeyPadDivide       = 331,      // Key: Keypad /
    KeyPadMultiply     = 332,      // Key: Keypad *
    KeyPadSubtract     = 333,      // Key: Keypad -
    KeyPadAdd          = 334,      // Key: Keypad +
    KeyPadEnter        = 335,      // Key: Keypad Enter
    KeyPadEqual        = 336,      // Key: Keypad =
    // Android key buttons
    Back            = 4,        // Key: Android back button
    Menu            = 82,       // Key: Android menu button
    VolumeUp       = 24,       // Key: Android volume up button
    VolumeDown     = 25        // Key: Android volume down button
  };

  // Mouse buttons
  enum class eMouseButton : s32 {
    Left    = 0,       // Mouse button left
    Right   = 1,       // Mouse button right
    Middle  = 2,       // Mouse button middle (pressed wheel)
    Side    = 3,       // Mouse button side (advanced mouse device)
    Extra   = 4,       // Mouse button extra (advanced mouse device)
    Forward = 5,       // Mouse button forward (advanced mouse device)
    Back    = 6,       // Mouse button back (advanced mouse device)
  };

  // Mouse cursor
  enum class eMouseCursor : s32 {
    Default       = 0,     // Default pointer shape
    Arrow         = 1,     // Arrow shape
    IBeam         = 2,     // Text writing cursor shape
    Crosshair     = 3,     // Cross shape
    PointingHand = 4,     // Pointing hand cursor
    ResizeEW     = 5,     // Horizontal resize/move arrow shape
    ResizeNS     = 6,     // Vertical resize/move arrow shape
    ResizeNWSE   = 7,     // Top-left to bottom-right diagonal resize/move arrow shape
    ResizeNESW   = 8,     // The top-right to bottom-left diagonal resize/move arrow shape
    ResizeAll    = 9,     // The omnidirectional resize/move cursor shape
    NotAllowed   = 10     // The operation-not-allowed shape
  };

  // Gamepad buttons
  enum class eGamepadButton : s32 {
    Unknown = 0,         // Unknown button, just for error checking
    LeftFaceUp,        // Gamepad left DPAD up button
    LeftFaceRight,     // Gamepad left DPAD right button
    LeftFaceDown,      // Gamepad left DPAD down button
    LeftFaceLeft,      // Gamepad left DPAD left button
    RightFaceUp,       // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
    RightFaceRight,    // Gamepad right button right (i.e. PS3: Square, Xbox: X)
    RightFaceDown,     // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
    RightFaceLeft,     // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
    LeftTrigger1,      // Gamepad top/back trigger left (first), it could be a trailing button
    LeftTrigger2,      // Gamepad top/back trigger left (second), it could be a trailing button
    RightTrigger1,     // Gamepad top/back trigger right (one), it could be a trailing button
    RightTrigger2,     // Gamepad top/back trigger right (second), it could be a trailing button
    MiddleLeft,         // Gamepad center buttons, left one (i.e. PS3: Select)
    Middle,              // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
    MiddleRight,        // Gamepad center buttons, right one (i.e. PS3: Start)
    LeftThumb,          // Gamepad joystick pressed button left
    RightThumb          // Gamepad joystick pressed button right
  };

  // Gamepad axis
  enum class eGamepadAxis : s32 {
    LeftX        = 0,     // Gamepad left stick X axis
    LeftY        = 1,     // Gamepad left stick Y axis
    RightX       = 2,     // Gamepad right stick X axis
    RightY       = 3,     // Gamepad right stick Y axis
    LeftTrigger  = 4,     // Gamepad back trigger left, pressure level: [1..-1]
    RightTrigger = 5      // Gamepad back trigger right, pressure level: [1..-1]
  };

  class SingletonInput final : public SingletonComponent
  {
    friend class CommandSystem;

  public:
    SingletonInput() { m_type = eSingletonComponentType::SingletonInput; }
    ~SingletonInput() = default;

  private:
    // TODO: Call location unclear!!!
    void create(const ComponentArgs* pArgs = nullptr) override {}

  public:
    // Input-related functions: gamepads
    bool is_gamepad_available(s32 gamepad_id) const { return IsGamepadAvailable(gamepad_id); }                                                  // Check if a gamepad is available
    auto gamepad_name(s32 gamepad_id) const -> const std::string_view { return GetGamepadName(gamepad_id); }                                    // Get gamepad internal name id
    bool controller_button_pressed(s32 gamepad_id, eGamepadButton button) const { return IsGamepadButtonPressed(gamepad_id, (s32)button); }     // Check if a gamepad button has been pressed once
    bool controller_button_released(s32 gamepad_id, eGamepadButton button) const { return IsGamepadButtonReleased(gamepad_id, (s32)button); }   // Check if a gamepad button has been released once
    bool controller_button_down(s32 gamepad_id, eGamepadButton button) const { return IsGamepadButtonDown(gamepad_id, (s32)button); }           // Check if a gamepad button is being pressed
    bool controller_button_up(s32 gamepad_id, eGamepadButton button) const { return IsGamepadButtonUp(gamepad_id, (s32)button); }               // Check if a gamepad button is NOT being pressed
    f32 controller_axis(s32 gamepad_id, eGamepadAxis axis) const { return GetGamepadAxisMovement(gamepad_id, (s32)axis); }                      // Get axis movement value for a gamepad axis

    // Input-related functions: keyboard
    bool pressed(eKeyboardKey key_code) const { return IsKeyPressed((s32)key_code); }    // Check if a key has been pressed once
    bool released(eKeyboardKey key_code) const { return IsKeyReleased((s32)key_code); }  // Check if a key has been released once
    bool down(eKeyboardKey key_code) const { return IsKeyDown((s32)key_code); }          // Check if a key is being pressed
    bool up(eKeyboardKey key_code) const { return IsKeyUp((s32)key_code); }              // Check if a key is NOT being pressed

    // Input-related functions: mouse
    bool pressed(eMouseButton mouse_button) const { return IsMouseButtonPressed((s32)mouse_button); }    // Check if a mouse button has been pressed once
    bool released(eMouseButton mouse_button) const { return IsMouseButtonReleased((s32)mouse_button); }  // Check if a mouse button has been released once
    bool down(eMouseButton mouse_button) const { return IsMouseButtonDown((s32)mouse_button); }          // Check if a mouse button is being pressed
    bool up(eMouseButton mouse_button) const { return IsMouseButtonUp((s32)mouse_button); }              // Check if a mouse button is NOT being pressed
    s32 mouse_x() const { return GetMouseX(); }                                                        // Get mouse position X
    s32 mouse_y() const { return GetMouseY(); }                                                        // Get mouse position Y
    zv::Vector2 mouse_position() const { return zv::Vector2(GetMousePosition()); }                     // Get mouse position XY
    zv::Vector2 mouse_delta() const { return zv::Vector2(GetMouseDelta()); }                           // Get mouse delta between frames
    zv::Vector2 mouse_wheel() const { return zv::Vector2(GetMouseWheelMoveV()); }                      // Get mouse wheel movement for both X and Y
    void set_mouse_position(s32 x, s32 y) { SetMousePosition(x, y); }                                  // Set mouse position XY
    void set_mouse_scale(f32 scale_x, f32 scale_y) { SetMouseScale(scale_x, scale_y); }                    // Set mouse scaling
    void set_mouse_cursor(eMouseCursor cursor) { SetMouseCursor((s32)cursor); }                        // Set mouse cursor

    // Cursor-related functions
    void show_cursor() { ShowCursor(); }                             // Shows cursor
    void hide_cursor() { HideCursor(); }                             // Hides cursor
    bool is_cursor_hidden() const { return IsCursorHidden(); }       // Check if cursor is not visible
    void enable_cursor() { EnableCursor(); }                         // Enables cursor (unlock cursor)
    void disable_cursor() { DisableCursor(); }                       // Disables cursor (lock cursor)
    bool is_cursor_on_screen() const { return IsCursorOnScreen(); }  // Check if cursor is on the screen
  };
}
