#include "Visitor.h"

/**********************/
/* C++ Class traverse */
/**********************/
bool Visitor::VisitCXXRecordDecl(clang::CXXRecordDecl *D) {
  std::cout<<"[LOG6302] Visite de la classe \""<<D->getNameAsString()<<"\"\n";
  return true;
}

/**********************/
/* variable traverse */
/**********************/
bool Visitor::VisitVarDecl(clang::VarDecl *VD) {
  std::cout<<"[LOG6302] Visite de la variable \""<<VD->getNameAsString()<<"\"\n";

  return true;
}

/**********************/
/* If visit           */
/**********************/
bool Visitor::VisitIfStmt(clang::IfStmt *S) {
  std::cout<<"[LOG6302] Visite d'une condition : \" if ("<<GetStatementString(S->getCond())<<") \"\n";
  return true;
}

/**********************/
/* switch visit           */
/**********************/
bool Visitor::VisitSwitchStmt(clang::SwitchStmt *S) {
  std::cout<<"[LOG6302] Visite d'une condition : \" switch ("<<GetStatementString(S->getCond())<<") \"\n";
  return true;
}

/**********************/
/* break visit           */
/**********************/
bool Visitor::VisitBreakStmt(clang::BreakStmt *S) {
  std::cout<<"[LOG6302] Visite d'un saut : \" break\"\n";
  return true;
}

/**********************/
/* continue visit           */
/**********************/
bool Visitor::VisitContinueStmt(clang::ContinueStmt *S) {
  std::cout<<"[LOG6302] Visite d'un saut : \" continue\"\n";
  return true;
}

/**********************/
/* for visit           */
/**********************/
bool Visitor::VisitForStmt(clang::ForStmt *S) {
  std::cout<<"[LOG6302] Visite d'une boucle : \"for\"("<<GetStatementString(S->getCond())<<")\n";
  return true;
}

/**********************/
/* while visit           */
/**********************/
bool Visitor::VisitWhileStmt(clang::WhileStmt *S) {
  std::cout<<"[LOG6302] Visite d'une boucle : \"while\"("<<GetStatementString(S->getCond())<<")\n";
  return true;
}

/***********************/
/* C++ Method traverse */
/***********************/
bool Visitor::TraverseCXXMethodDecl(clang::CXXMethodDecl *D) {

  if (!D->isThisDeclarationADefinition()) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(D->getLocStart());

  std::string  file_path   = context_.getSourceManager().getFileEntryForID(location.getFileID())->getName();
  unsigned int line_number = location.getSpellingLineNumber();

  std::cout
    <<"[LOG6302] Traverse de la méthode \""
    <<D->getNameAsString()
    <<"\" ("
    << file_path
    << ":"
    <<line_number
    <<")\n";

  clang::RecursiveASTVisitor<Visitor>::TraverseCXXMethodDecl(D);

  std::cout<<"[LOG6302] Fin traverse de la méthode \""<<D->getNameAsString()<<"\"\n";

  return true;
}
