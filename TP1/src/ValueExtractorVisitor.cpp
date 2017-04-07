#include "ValueExtractorVisitor.h"

ValueExtractorVisitor::ValueExtractorVisitor()
{
}

bool ValueExtractorVisitor::VisitDeclRefExpr(clang::DeclRefExpr *S)
{
  std::string varName;
  varName = S->getDecl()->getNameAsString();
  if (visited.find(varName) == visited.end()) {
    vars.addValue(varName);
    visited.insert(varName);
  }

  return true;
}

VarInStament ValueExtractorVisitor::getAllVar() const
{
  return vars;
}
