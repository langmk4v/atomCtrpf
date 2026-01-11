#pragma once

#include <vector>

#include "Token.hpp"

#include "ASTFwd.hpp"

namespace CTRPluginFramework::lua::ast {

enum class Kind {
  Expr,
  Assign,
  Stmt,
  Func,
};

enum class ExprKind {
  Var,
  CallFunc,
  Add,
  Sub,
};

enum class StmtKind {
  If,
  For,
  Do,
  Break,
  Return,
};

struct Tree {
  Kind kind;
  Token* token;

  virtual ~Tree() = default;

protected:
  Tree(Kind kind, Token* token)
    : kind(kind),
      token(token)
  {
  }
};

struct Expr : public Tree {
  ExprKind kind;

  virtual ~Expr() = default;

protected:
  Expr(ExprKind kind, Token* token)
    : Tree(Kind::Expr, token),
      kind(kind)
  {
  }
};

struct Stmt : public Tree {

};

struct Variable final : public Expr {
  StringID name;

  Variable(Token* token)
    : Expr(ExprKind::Var, token),
      name(token->str)
  {
  }
};

struct Terms final : public Expr {
  std::vector<Expr*> terms;

  ~Terms();

  Terms(ExprKind kind, Expr* base)
    : Expr(kind, base->token),
      terms({ base })
  {
  }
};

struct Assign final : public Tree {
  Token*  dest;
  Expr*   source;

  ~Assign();

  Assign(Token* dest, Expr* source, Token* op)
    : Tree(Kind::Assign, op),
      dest(dest),
      source(source)
  {
  }
};

struct Func final : public Tree {
  Token*  name_tok;
  std::vector<Token*> args;
  Token*  result_type;


  ~Func();

  Func(Token* decl)
    : Tree(Kind::Func, decl)
  {
  }
};

}