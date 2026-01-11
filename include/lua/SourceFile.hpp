#pragma once

#include <vector>

#include "Token.hpp"
#include "ASTFwd.hpp"

namespace CTRPluginFramework::lua {

class Lexer;
class Parser;

struct SourceFile {
  std::string path;

  std::string data;

  std::vector<SourceFile*> imports;

  Lexer* lexer;
  Parser* parser;

  Token* token;
  ast::Tree* parsed_tree;

  auto read() -> bool;

  auto get_line_range(size_t pos) -> std::pair<size_t, size_t>;

  auto length() -> size_t const { return this->data.length(); }

  SourceFile(std::string const& path);
  ~SourceFile();
};

}  // namespace CTRPluginFramework::lua