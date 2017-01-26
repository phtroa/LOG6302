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

/**********************/
/* classe traverse    */
/**********************/
bool Visitor::TraverseCXXRecordDecl(clang::CXXRecordDecl *D) {
  std::cout<<"[LOG6302] Traverse de la classe \""<<D->getNameAsString()<<"\"\n";

  clang::RecursiveASTVisitor<Visitor>::TraverseCXXRecordDecl(D);

  std::cout<<"[LOG6302] Fin traverse de la classe \""<<D->getNameAsString()<<"\"\n";

  return true;
}

/**********************/
/* variable traverse  */
/**********************/
bool Visitor::TraverseVarDecl(clang::VarDecl *D) {
  std::cout<<"[LOG6302] Traverse de la variable \""<<D->getNameAsString()<<"\"\n";

  clang::RecursiveASTVisitor<Visitor>::TraverseVarDecl(D);

  std::cout<<"[LOG6302] Fin traverse de la variable \""<<D->getNameAsString()<<"\"\n";

  return true;
}

/**********************/
/* If traverse        */
/**********************/
bool Visitor::TraverseIfStmt(clang::IfStmt *S) {
  std::cout<<"[LOG6302] Traverse d'une condition : \" if ("<<GetStatementString(S->getCond())<<") \"\n";

  clang::RecursiveASTVisitor<Visitor>::TraverseIfStmt(S);

  std::cout<<"[LOG6302] Fin Traverse d'une condition : \" if ("<<GetStatementString(S->getCond())<<") \"\n";

  return true;
}

/**********************/
/* switch traverse    */
/**********************/
bool Visitor::TraverseSwitchStmt(clang::SwitchStmt *S) {
  std::cout<<"[LOG6302] Traverse d'une condition : \" switch ("<<GetStatementString(S->getCond())<<") \"\n";

  clang::RecursiveASTVisitor<Visitor>::TraverseSwitchStmt(S);

  std::cout<<"[LOG6302] Fin Traverse d'une condition : \" switch ("<<GetStatementString(S->getCond())<<") \"\n";

  return true;
}

/**********************/
/* break traverse     */
/**********************/
bool Visitor::TraverseBreakStmt(clang::BreakStmt *S) {
  std::cout<<"[LOG6302] Traverse d'un saut : \" break\"\n";

  clang::RecursiveASTVisitor<Visitor>::TraverseBreakStmt(S);

  std::cout<<"[LOG6302] Fin Traverse d'un saut : \" break\"\n";

  return true;
}

/**********************/
/* continue traverse           */
/**********************/
bool Visitor::TraverseContinueStmt(clang::ContinueStmt *S) {
  std::cout<<"[LOG6302] Traverse d'un saut : \" continue\"\n";

  clang::RecursiveASTVisitor<Visitor>::TraverseContinueStmt(S);

  std::cout<<"[LOG6302] Fin Traverse d'un saut : \" continue\"\n";

  return true;
}

/**********************/
/* for traverse           */
/**********************/
bool Visitor::TraverseForStmt(clang::ForStmt *S) {
  std::cout<<"[LOG6302] Traverse d'une boucle : \"for\"("<<GetStatementString(S->getCond())<<")\n";

  clang::RecursiveASTVisitor<Visitor>::TraverseForStmt(S);

  std::cout<<"[LOG6302] Fin Traverse d'une boucle : \" for\"\n";

  return true;
}

/**********************/
/* while traverse           */
/**********************/
bool Visitor::TraverseWhileStmt(clang::WhileStmt *S) {
  std::cout<<"[LOG6302] Traverse d'une boucle : \"while\"("<<GetStatementString(S->getCond())<<")\n";

  clang::RecursiveASTVisitor<Visitor>::TraverseWhileStmt(S);

  std::cout<<"[LOG6302] Fin Traverse d'une boucle : \" while\"\n";

  return true;
}
