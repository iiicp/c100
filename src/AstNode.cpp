/**********************************
 * File:     AstNode.cpp.cc
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2022/1/3
 ***********************************/

#include "AstNode.h"

using namespace C100;

void ProgramNode::Accept(AstVisitor *visitor)
{
  visitor->VisitorProgramNode(this);
}

void BinaryNode::Accept(AstVisitor *visitor)
{
  visitor->VisitorBinaryNode(this);
}


void ConstantNode::Accept(AstVisitor *visitor)
{
  visitor->VisitorConstantNode(this);
}

void ExprStmtNode::Accept(AstVisitor *visitor)
{
  visitor->VisitorExprStmtNode(this);
}

void VarExprNode::Accept(AstVisitor *visitor)
{
  visitor->VisitorVarExprNode(this);
}

void AssignExprNode::Accept(AstVisitor *visitor)
{
  visitor->VisitorAssignExprNode(this);
}

void IfStmtNode::Accept(AstVisitor *visitor)
{
  visitor->VisitorIfStmtNode(this);
}

void BlockStmtNode::Accept(AstVisitor *visitor)
{
  visitor->VisitorBlockStmtNode(this);
}

void WhileStmtNode::Accept(AstVisitor *visitor)
{
  visitor->VisitorWhileStmtNode(this);
}

void DoWhileStmtNode::Accept(AstVisitor *visitor)
{
  visitor->VisitorDoWhileStmtNode(this);
}

void ForStmtNode::Accept(AstVisitor *visitor)
{
  visitor->VisitorForStmtNode(this);
}

void FunctionNode::Accept(AstVisitor *visitor) {
  visitor->VisitorFunctionNode(this);
}

void FuncCallNode::Accept(AstVisitor *visitor) {
  visitor->VisitorFuncCallNode(this);
}

void ReturnStmtNode::Accept(AstVisitor *visitor) {
  visitor->VisitorReturnStmtNode(this);
}
