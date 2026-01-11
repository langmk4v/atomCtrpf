#include "CTRPluginFramework.hpp"

#include "lua.hpp"

namespace CTRPluginFramework {

auto entry_test(MenuEntry* e) -> void {

  auto ctx = static_cast<lua::EntryContext*>(e->GetArg());

  ctx->eval();

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