#include <Config.h>
#include <Core/Application.h>
#include <Core/ApplicationCore.h>
#include <Core/Log.h>
#include <Core/Window.h>

#if ZV_DEV_TOOLS_ENABLED
#include <Editor/Editor.h>
#include <Editor/EditorMainWindow.h>
#else
#include <Game/Game.h>
#include <Game/GameMainWindow.h>
#endif


zv::Application::Application()
{
#if ZV_DEV_TOOLS_ENABLED
  m_ptr_window = std::make_unique<EditorMainWindow>();
  m_ptr_core = std::make_unique<Editor>();
#else
  m_ptr_window = std::make_unique<GameMainWindow>();
  m_ptr_core = std::make_unique<Game>();
#endif
  // m_ptr_render_core = std::make_unique<RenderCore>();
}

zv::Application::~Application()
{
}

s32 zv::Application::run()
{
#if ZV_DEV_TOOLS_ENABLED
  m_ptr_window->create(ZV_EDITOR_TITLE);
#else
  m_ptr_window->create(ZV_GAME_TITLE);
#endif

  ZV_LOG_INFO("\n\n"
    "#########################\n"
    "### ZEN VISION ENGINE ###\n"
    "#########################\n");

  // m_ptr_render_core->create(m_ptr_window.get());
  m_ptr_core->create(m_ptr_window.get());

  while (!m_ptr_window->should_close() && !m_ptr_core->quit())
  {
    m_ptr_core->run();
  }

  m_ptr_core->destroy();

  ZV_LOG_INFO(
    "\n\n#########################"
    "\n#########################"
    "\n#########################\n"
  );

  m_ptr_window->destroy();

  return 0;
}
