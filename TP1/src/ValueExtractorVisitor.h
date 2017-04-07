#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/ASTContext.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Lex/Lexer.h>

#include "VarInStament.h"

class ValueExtractorVisitor : public clang::RecursiveASTVisitor<ValueExtractorVisitor>
{
public:
  ValueExtractorVisitor();
  bool VisitDeclRefExpr(clang::DeclRefExpr *S);

  VarInStament getAllVar() const;
private:
  VarInStament vars;
  std::set<std::string> visited;
};
