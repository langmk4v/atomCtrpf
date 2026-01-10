#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework {

auto main() -> int {
  PluginMenu menu{"CTRPF"};

  menu.SynchronizeWithFrame(true);

  return menu.Run();
}

}  // namespace CTRPluginFramework