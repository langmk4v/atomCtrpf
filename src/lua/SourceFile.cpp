#include <iostream>
#include <fstream>
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
  std::string line;

  std::ifstream ifs{this->path};

  if (ifs.fail()) {
    (MessageBox("fail"))();
    return false;
  }

  while (std::getline(ifs, line)) {
    line.push_back('\n');
    this->data.append(line);
  }

  return true;
}

}  // namespace CTRPluginFramework::lua