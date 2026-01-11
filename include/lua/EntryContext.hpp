#pragma once

#include <CTRPluginFramework/Menu/MenuEntry.hpp>

#include "SourceFile.hpp"
#include "Parser.hpp"
#include "Eval.hpp"

namespace CTRPluginFramework::lua {

struct EntryContext {
  SourceFile source;
  ASTEvaluator evaluator;

  auto is_parsed() -> bool {
    return this->source.parsed_tree != nullptr;
  }

  auto lex() -> void {
    this->source.token = this->source.lexer->lex();
  }

  auto parse() -> void {
    this->source.parsed_tree = this->source.parser->parse();
  }

  auto eval() -> void {
    this->evaluator.eval(this->source.parsed_tree);
  }

  EntryContext(std::string const& path)
    : source(path),
      evaluator(&source)
  {
  }
};

static auto make_entry(std::string const& path, MenuEntry* e) -> MenuEntry* {

  auto* ctx = new EntryContext(path);

  ctx->lex();
  ctx->parse();

  e->SetArg(ctx);

  return e;
}

}