#pragma once

#include <string>

#include <raylib.h>

#include <Core/IRenderSurface.h>
#include <Util/BitFlag.h>
#include <Util/PrimitiveTypes.h>


namespace zv
{
  class MainWindow : public IRenderSurface
  {
  protected:
    enum class eConfig : u32
    {
      Null                   = 0x00000000,
      VSyncHint              = 0x00000040,   // Set to try enabling V-Sync on GPU
      FullscreenMode         = 0x00000002,   // Set to run program in fullscreen
      WindowResizable        = 0x00000004,   // Set to allow resizable window
      WindowUndecorated      = 0x00000008,   // Set to disable window decoration (frame and buttons)
      WindowHidden           = 0x00000080,   // Set to hide window
      WindowMinimized        = 0x00000200,   // Set to minimize window (iconify)
      WindowMaximized        = 0x00000400,   // Set to maximize window (expanded to monitor)
      WindowUnfocused        = 0x00000800,   // Set to window non-focused
      WindowTopmost          = 0x00001000,   // Set to window always on top
      WindowAlwaysRun        = 0x00000100,   // Set to allow windows running while minimized
      WindowTransparent      = 0x00000010,   // Set to allow transparent framebuffer
      WindowHighDPI          = 0x00002000,   // Set to support HighDPI
      WindowMousePassthrough = 0x00004000,   // Set to support mouse passthrough, only supported when WindowUndecorated
      BorderlessWindowedMode = 0x00008000,   // Set to run program in borderless windowed mode
      MSAA4XHint             = 0x00000020,   // Set to try enabling MSAA 4X
      InterlacedHint         = 0x00010000    // Set to try enabling interlaced video format (for V3D)
    };
    using ConfigFlags = BitFlag<eConfig>;

  public:
    MainWindow() = default;
    virtual ~MainWindow() = default;

  public:
    virtual void create(const std::string& window_title) = 0;
    virtual void destroy() { CloseWindow(); }

  public:
    s32 get_render_width() const override { return GetScreenWidth(); }
    s32 get_render_height() const override { return GetScreenHeight(); }

  public:
    bool should_close() const { return WindowShouldClose(); }
    bool is_reszied() const { return IsWindowResized(); }

    // s32 screen_width() const { return GetScreenWidth(); }
    // s32 screen_height() const { return GetScreenHeight(); }

    // s32 zv::MainWindow::monitor_count() const { return GetMonitorCount(); }
    // s32 zv::MainWindow::current_monitor() const { return GetCurrentMonitor(); }
    // s32 zv::MainWindow::monitor_width(s32 monitor) const { return GetMonitorWidth(monitor); }
    // s32 zv::MainWindow::monitor_height(s32 monitor) const { return GetMonitorHeight(monitor); }

    // void zv::MainWindow::set_window_monitor(s32 monitor) { SetWindowMonitor(monitor); }
    // void zv::MainWindow::set_window_position(s32 x, s32 y) { SetWindowPosition(x, y); }
    // void zv::MainWindow::set_window_size(s32 width, s32 height) { SetWindowSize(width, height); }

// RLAPI void SetWindowIcon(Image image);                            // Set icon for window (single image, RGBA 32bit, only PLATFORM_DESKTOP)
// RLAPI const char *GetMonitorName(int monitor);                    // Get the human-readable, UTF-8 encoded name of the specified monitor

/*
// Window-related functions
RLAPI void InitWindow(int width, int height, const char *title);  // Initialize window and OpenGL context
RLAPI void CloseWindow(void);                                     // Close window and unload OpenGL context
RLAPI bool WindowShouldClose(void);                               // Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
RLAPI bool IsWindowReady(void);                                   // Check if window has been initialized successfully
RLAPI bool IsWindowFullscreen(void);                              // Check if window is currently fullscreen
RLAPI bool IsWindowHidden(void);                                  // Check if window is currently hidden (only PLATFORM_DESKTOP)
RLAPI bool IsWindowMinimized(void);                               // Check if window is currently minimized (only PLATFORM_DESKTOP)
RLAPI bool IsWindowMaximized(void);                               // Check if window is currently maximized (only PLATFORM_DESKTOP)
RLAPI bool IsWindowFocused(void);                                 // Check if window is currently focused (only PLATFORM_DESKTOP)
RLAPI bool IsWindowResized(void);                                 // Check if window has been resized last frame
RLAPI bool IsWindowState(unsigned int flag);                      // Check if one specific window flag is enabled
RLAPI void SetWindowState(unsigned int flags);                    // Set window configuration state using flags (only PLATFORM_DESKTOP)
RLAPI void ClearWindowState(unsigned int flags);                  // Clear window configuration state flags
RLAPI void ToggleFullscreen(void);                                // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
RLAPI void ToggleBorderlessWindowed(void);                        // Toggle window state: borderless windowed (only PLATFORM_DESKTOP)
RLAPI void MaximizeWindow(void);                                  // Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
RLAPI void MinimizeWindow(void);                                  // Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
RLAPI void RestoreWindow(void);                                   // Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
RLAPI void SetWindowIcon(Image image);                            // Set icon for window (single image, RGBA 32bit, only PLATFORM_DESKTOP)
RLAPI void SetWindowIcons(Image *images, int count);              // Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)
RLAPI void SetWindowTitle(const char *title);                     // Set title for window (only PLATFORM_DESKTOP and PLATFORM_WEB)
RLAPI void SetWindowPosition(int x, int y);                       // Set window position on screen (only PLATFORM_DESKTOP)
RLAPI void SetWindowMonitor(int monitor);                         // Set monitor for the current window
RLAPI void SetWindowMinSize(int width, int height);               // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
RLAPI void SetWindowMaxSize(int width, int height);               // Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
RLAPI void SetWindowSize(int width, int height);                  // Set window dimensions
RLAPI void SetWindowOpacity(float opacity);                       // Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)
RLAPI void SetWindowFocused(void);                                // Set window focused (only PLATFORM_DESKTOP)
RLAPI void *GetWindowHandle(void);                                // Get native window handle
RLAPI int GetScreenWidth(void);                                   // Get current screen width
RLAPI int GetScreenHeight(void);                                  // Get current screen height
RLAPI int GetRenderWidth(void);                                   // Get current render width (it considers HiDPI)
RLAPI int GetRenderHeight(void);                                  // Get current render height (it considers HiDPI)
RLAPI int GetMonitorCount(void);                                  // Get number of connected monitors
RLAPI int GetCurrentMonitor(void);                                // Get current connected monitor
RLAPI Vector2 GetMonitorPosition(int monitor);                    // Get specified monitor position
RLAPI int GetMonitorWidth(int monitor);                           // Get specified monitor width (current video mode used by monitor)
RLAPI int GetMonitorHeight(int monitor);                          // Get specified monitor height (current video mode used by monitor)
RLAPI int GetMonitorPhysicalWidth(int monitor);                   // Get specified monitor physical width in millimetres
RLAPI int GetMonitorPhysicalHeight(int monitor);                  // Get specified monitor physical height in millimetres
RLAPI int GetMonitorRefreshRate(int monitor);                     // Get specified monitor refresh rate
RLAPI Vector2 GetWindowPosition(void);                            // Get window position XY on monitor
RLAPI Vector2 GetWindowScaleDPI(void);                            // Get window scale DPI factor
RLAPI const char *GetMonitorName(int monitor);                    // Get the human-readable, UTF-8 encoded name of the specified monitor
RLAPI void SetClipboardText(const char *text);                    // Set clipboard text content
RLAPI const char *GetClipboardText(void);                         // Get clipboard text content
RLAPI void EnableEventWaiting(void);                              // Enable waiting for events on EndDrawing(), no automatic event polling
RLAPI void DisableEventWaiting(void);                             // Disable waiting for events on EndDrawing(), automatic events polling
*/
  };
}
