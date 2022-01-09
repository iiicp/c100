/**********************************
 * File:     Parser.cpp.cc
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2022/1/3
 ***********************************/

#include "Parser.h"
#include "Diag.h"
#include <string>

using namespace C100;

std::shared_ptr<ProgramNode> Parser::Parse()
{
  auto node = std::make_shared<ProgramNode>();
  Locals = &node->LocalVars;
  while (Lex.CurrentToken->Kind != TokenKind::Eof) {
    node->Stmts.push_back(ParseStmt());
  }

  return node;
}

std::shared_ptr<AstNode> Parser::ParseExpr()
{
  return ParseAssignExpr();
}

std::shared_ptr<AstNode> Parser::ParseAddExpr()
{
  std::shared_ptr<AstNode> left = ParseMultiExpr();
  while (Lex.CurrentToken->Kind == TokenKind::Add
         || Lex.CurrentToken->Kind == TokenKind::Sub) {
    BinaryOperator anOperator = BinaryOperator::Add;
    if (Lex.CurrentToken->Kind == TokenKind::Sub)
      anOperator = BinaryOperator::Sub;
    Lex.GetNextToken();
    auto node = std::make_shared<BinaryNode>();
    node->BinOp = anOperator;
    node->Lhs = left;
    node->Rhs = ParseMultiExpr();
    left = node;
  }
  return left;
}

std::shared_ptr<AstNode> Parser::ParseMultiExpr()
{
  std::shared_ptr<AstNode> left = ParsePrimaryExpr();
  while (Lex.CurrentToken->Kind == TokenKind::Mul
         || Lex.CurrentToken->Kind == TokenKind::Div) {
    BinaryOperator anOperator = BinaryOperator::Mul;
    if (Lex.CurrentToken->Kind == TokenKind::Div)
      anOperator = BinaryOperator::Div;
    Lex.GetNextToken();
    auto node = std::make_shared<BinaryNode>();
    node->BinOp = anOperator;
    node->Lhs = left;
    node->Rhs = ParsePrimaryExpr();
    left = node;
  }
  return left;
}

std::shared_ptr<AstNode> Parser::ParsePrimaryExpr()
{
    if (Lex.CurrentToken->Kind == TokenKind::LParent) {
        Lex.GetNextToken();
        auto node = ParseExpr();
        Lex.ExpectToken(TokenKind::RParent);
        return node;
    }else if (Lex.CurrentToken->Kind == TokenKind::Num) {
        auto node = std::make_shared<ConstantNode>();
        node->Value = Lex.CurrentToken->Value;
        Lex.GetNextToken();
        return node;
    }else if (Lex.CurrentToken->Kind == TokenKind::Identifier) {
        auto node = std::make_shared<VarExprNode>();

        std::shared_ptr<Var> obj = FindLocalVar(Lex.CurrentToken->Content);
        if (!obj) {
          obj = MakeLocalVar(Lex.CurrentToken->Content);
        }
        node->VarObj = obj;
        Lex.GetNextToken();
        return node;
    }else {
      DiagE(Lex.SourceCode, Lex.CurrentToken->Location,
            "not support");
    }
  return nullptr;
}

std::shared_ptr<AstNode> Parser::ParseStmt()
{
  if (Lex.CurrentToken->Kind == TokenKind::If) {
    auto node = std::make_shared<IfStmtNode>();
    Lex.GetNextToken();
    Lex.ExpectToken(TokenKind::LParent);
    node->Cond = ParseExpr();
    Lex.ExpectToken(TokenKind::RParent);
    node->Then = ParseStmt();
    if (Lex.CurrentToken->Kind == TokenKind::Else) {
      Lex.GetNextToken();
      node->Else = ParseStmt();
    }
    return node;
  }
  else if (Lex.CurrentToken->Kind == TokenKind::While) {
    auto node = std::make_shared<WhileStmtNode>();
    Lex.GetNextToken();
    Lex.ExpectToken(TokenKind::LParent);
    node->Cond = ParseExpr();
    Lex.ExpectToken(TokenKind::RParent);
    node->Then = ParseStmt();
    return node;
  }
  else if (Lex.CurrentToken->Kind == TokenKind::LBrace) {
    auto node = std::make_shared<BlockStmtNode>();
    Lex.GetNextToken();
    while (Lex.CurrentToken->Kind != TokenKind::RBrace) {
      node->Stmts.push_back(ParseStmt());
    }
    Lex.ExpectToken(TokenKind::RBrace);
    return node;
  }
  else {
    auto node = std::make_shared<ExprStmtNode>();
    if (Lex.CurrentToken->Kind != TokenKind::Semicolon) {
      node->Lhs = ParseExpr();
    }
    Lex.ExpectToken(TokenKind::Semicolon);
    return node;
  }
}


std::shared_ptr<AstNode> Parser::ParseEqualExpr() {
  auto left = ParseRelationalExpr();
  while (Lex.CurrentToken->Kind == TokenKind::Equal ||
  Lex.CurrentToken->Kind == TokenKind::PipeEqual ) {
    BinaryOperator op = BinaryOperator::Equal;
    if (Lex.CurrentToken->Kind == TokenKind::PipeEqual)
      op = BinaryOperator::PipeEqual;
    Lex.GetNextToken();
    auto node = std::make_shared<BinaryNode>();
    node->BinOp = op;
    node->Lhs = left;
    node->Rhs = ParseRelationalExpr();
    left = node;
  }
  return left;
}

std::shared_ptr<AstNode> Parser::ParseRelationalExpr() {
  auto left = ParseAddExpr();
  while (Lex.CurrentToken->Kind == TokenKind::Greater ||
      Lex.CurrentToken->Kind == TokenKind::GreaterEqual ||
      Lex.CurrentToken->Kind == TokenKind::Lesser ||
      Lex.CurrentToken->Kind == TokenKind::LesserEqual) {
    BinaryOperator op = BinaryOperator::Greater;
    if (Lex.CurrentToken->Kind == TokenKind::GreaterEqual)
      op = BinaryOperator::GreaterEqual;
    else if (Lex.CurrentToken->Kind == TokenKind::Lesser)
      op = BinaryOperator::Lesser;
    else if (Lex.CurrentToken->Kind == TokenKind::LesserEqual)
      op = BinaryOperator::LesserEqual;

    Lex.GetNextToken();
    auto node = std::make_shared<BinaryNode>();
    node->BinOp = op;
    node->Lhs = left;
    node->Rhs = ParseAddExpr();
    left = node;
  }
  return left;
}

std::shared_ptr<AstNode> Parser::ParseAssignExpr()
{
  auto left = ParseEqualExpr();

  if (Lex.CurrentToken->Kind == TokenKind::Assign) {
    Lex.GetNextToken();
    auto node = std::make_shared<AssignExprNode>();
    node->Lhs = left;
    node->Rhs = ParseAssignExpr();
    return node;
  }
  return left;
}

std::shared_ptr<Var> Parser::FindLocalVar(std::string_view name) {
  if (LocalsMap.find(name) != LocalsMap.end()) {
    return LocalsMap[name];
  }
  return nullptr;
}

std::shared_ptr<Var> Parser::MakeLocalVar(std::string_view name) {
  auto obj = std::make_shared<Var>();
  obj->Name = name;
  obj->Offset = 0;
  Locals->push_front(obj);
  LocalsMap[name] = obj;
  return obj;
}

