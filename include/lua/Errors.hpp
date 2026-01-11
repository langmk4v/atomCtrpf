#pragma once

#include <string>

#include "CTRPluginFramework/Graphics/OSD.hpp"
#include "CTRPluginFramework/Utils/Utils.hpp"

namespace CTRPluginFramework::lua {

struct Error {
 public:
  size_t pos;
  std::string msg;

  Error(size_t pos, std::string const& msg) : pos(pos), msg(msg) {}

  void operator()() {
    OSD::Notify(Utils::Format("error at pos=%zu:", this->pos));
    OSD::Notify(this->msg);
  }
};

}  // namespace CTRPluginFramework::lua