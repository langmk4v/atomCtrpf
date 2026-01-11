#include "CTRPluginFramework.hpp"

#include "lua.hpp"

namespace CTRPluginFramework {

auto entry_test(MenuEntry* e) -> void {

  auto ctx = static_cast<lua::EntryContext*>(e->GetArg());

  ctx->eval();

  if (Controller::IsKeyPressed(Key::X)) {

    std::string msg;

    for (auto tok = ctx->get_token(); !tok->is_eof(); tok = tok->next) {
      msg += tok->get_strview();
      msg += " ";
    }

    (MessageBox(msg))();
  }

  if (Controller::IsKeyPressed(Key::L)) {
    OSD::Notify(Utils::Format("%08X", (u32)ctx));
  }

}

auto init_menu(PluginMenu& menu) -> void {

  menu.Append(lua::make_entry("test.zlua", new MenuEntry("test", entry_test)));

}

auto test() -> void {
  auto src = lua::SourceFile("test.zlua");

  auto lexer = src.lexer;

  auto token = lexer->lex();

  delete token;
}

auto main() -> int {
  PluginMenu menu{"CTRPF"};

  menu.SynchronizeWithFrame(true);

  init_menu(menu);

  return menu.Run();
}

}  // namespace CTRPluginFramework