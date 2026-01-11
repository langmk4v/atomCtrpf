#include <filesystem>

#include "CTRPluginFramework.hpp"

#include "lua/SourceFile.hpp"
#include "lua/Lexer.hpp"
#include "lua/Parser.hpp"

namespace CTRPluginFramework::lua {

SourceFile::SourceFile(std::string const& path)
  : path(path),
    data(),
    imports(),
    file(path),
    lexer(new Lexer(this)),
    parser(new Parser(this)),
    token(nullptr),
    parsed_tree(nullptr)
{
}

SourceFile::~SourceFile() {
  if (this->lexer) delete this->lexer;
  if (this->parser) delete this->parser;
}

bool SourceFile::read() {

  if (!this->file.IsOpen()) {
    (MessageBox("fail"))();
    return false;
  }

  auto reader = LineReader(this->file);

  std::string line;

  while (reader(line)) {
    line.push_back('\n');
    this->data.append(line);
  }

  return true;
}

}  // namespace CTRPluginFramework::lua