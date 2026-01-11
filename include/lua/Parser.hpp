#pragma once

#include "ASTFwd.hpp"

namespace CTRPluginFramework::lua {

struct SourceFile;

class Parser {
  SourceFile* source;

 public:
  Parser(SourceFile* source)
    : source(source)
  {
  }

  ast::Tree* parse();
};

}  // namespace CTRPluginFramework::lua