#include "lua/AST.hpp"

namespace CTRPluginFramework::lua::ast {

Terms::~Terms() {
  for (auto& t : this->terms)
    delete t;
}


Assign::~Assign() {
  if (this->dest) delete this->dest;
  if (this->source) delete this->source;
}

}