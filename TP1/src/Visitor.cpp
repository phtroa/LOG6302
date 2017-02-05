#include "Visitor.h"

  Visitor::Visitor(clang::ASTContext &context,
     std::shared_ptr<ASTTree> ast,
     std::shared_ptr<MetaTree> info)
      : context_(context), myAst(ast), infoTree(info) {
    currNode = ast->getRoot();
  }

  std::shared_ptr<ASTTree> Visitor::getAST() {
    return myAst;
  }

  void Visitor::setAST(std::shared_ptr<ASTTree> ast) {
    myAst = ast;
  }

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

  inMethod = true;

  clang::FullSourceLoc location = context_.getFullLoc(D->getLocStart());

  std::string  file_path   = context_.getSourceManager().getFileEntryForID(location.getFileID())->getName();
  unsigned int line_number = location.getSpellingLineNumber();
  std::string methodName = D->getNameAsString();

  std::cout
    <<"[LOG6302] Traverse de la méthode \""
    << methodName
    <<"\" ("
    << file_path
    << ":"
    <<line_number
    <<")\n";

  //We need to test if the method has already been visited
  std::string className = D->getParent()->getNameAsString();
  if (infoTree->isMethodIn(className, methodName)) {
    return true; //has already been added to the AST
  }


  //Create a new node
  if (!infoTree->isClassIn(className)) {
    std::cerr << "ERRROR method's Class is unknown" << std::endl;
    return false;
  }
  std::shared_ptr<ABSNode> parent = infoTree->getPtrToClass(className);
  std::shared_ptr<ABSNode> myNode(new MethodNode(methodName));
  myAst->linkParentToChild(parent, myNode);
  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseCXXMethodDecl(D);
  currNode = parent;

  std::cout<<"[LOG6302] Fin traverse de la méthode \""<< methodName <<"\"\n";

  inMethod = false;
  infoTree->addMethodIn(className, methodName);

  return true;
}

/**********************/
/* classe traverse    */
/**********************/
bool Visitor::TraverseCXXRecordDecl(clang::CXXRecordDecl *D) {
  std::string className(D->getNameAsString());
  std::cout<<"[LOG6302] Traverse de la classe \""<< className <<"\"\n";

  clang::FullSourceLoc location = context_.getFullLoc(D->getLocStart());

  std::string  file_path("");
  if (context_.getSourceManager().getFileEntryForID(location.getFileID()) != nullptr)
    file_path = context_.getSourceManager().getFileEntryForID(location.getFileID())->getName();

  std::shared_ptr<ABSNode> myNode;

  //Since We are building only one tree, we need to verify if we have already
  //encounter the class
  if (!infoTree->isClassIn(className)) {
    myNode = std::shared_ptr<ABSNode>(new ClassNode(className, file_path));
    //We add the class to the Tree information
    infoTree->addPtrToClass(className, myNode);
    myAst->linkParentToChild(currNode, myNode);
  }
  else {
    myNode = infoTree->getPtrToClass(className);
  }

  std::shared_ptr<ABSNode> parent(currNode);
  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseCXXRecordDecl(D);
  currNode = parent;

  std::cout<<"[LOG6302] Fin traverse de la classe \""<< className <<"\"\n";

  return true;
}

/**********************/
/* variable traverse  */
/**********************/
bool Visitor::TraverseVarDecl(clang::VarDecl *D) {
  if (!inMethod) {
    return true;
  }

  std::cout<<"[LOG6302] Traverse de la variable \""<<D->getNameAsString()<<"\"\n";

  std::shared_ptr<ABSNode> myNode(new VarNode());
  myAst->linkParentToChild(currNode, myNode);
  std::shared_ptr<ABSNode> parent(currNode);
  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseVarDecl(D);
  currNode = parent;

  std::cout<<"[LOG6302] Fin traverse de la variable \""<<D->getNameAsString()<<"\"\n";

  return true;
}

/**********************/
/* If traverse        */
/**********************/
bool Visitor::TraverseIfStmt(clang::IfStmt *S) {
  if (!inMethod) {
    return true;
  }

  std::cout<<"[LOG6302] Traverse d'une condition : \" if ("<<GetStatementString(S->getCond())<<") \"\n";

  std::shared_ptr<ABSNode> myNode(new CondNode());
  myAst->linkParentToChild(currNode, myNode);
  std::shared_ptr<ABSNode> parent(currNode);
  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseIfStmt(S);
  currNode = parent;

  std::cout<<"[LOG6302] Fin Traverse d'une condition : \" if ("<<GetStatementString(S->getCond())<<") \"\n";

  return true;
}

/**********************/
/* switch traverse    */
/**********************/
bool Visitor::TraverseSwitchStmt(clang::SwitchStmt *S) {
  if (!inMethod) {
    return true;
  }

  std::cout<<"[LOG6302] Traverse d'une condition : \" switch ("<<GetStatementString(S->getCond())<<") \"\n";

  std::shared_ptr<ABSNode> myNode(new CondNode());
  myAst->linkParentToChild(currNode, myNode);
  std::shared_ptr<ABSNode> parent(currNode);
  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseSwitchStmt(S);
  currNode = parent;

  std::cout<<"[LOG6302] Fin Traverse d'une condition : \" switch ("<<GetStatementString(S->getCond())<<") \"\n";

  return true;
}

/**********************/
/* break traverse     */
/**********************/
bool Visitor::TraverseBreakStmt(clang::BreakStmt *S) {
  if (!inMethod) {
    return true;
  }

  std::cout<<"[LOG6302] Traverse d'un saut : \" break\"\n";

  std::shared_ptr<ABSNode> myNode(new JumpNode());
  myAst->linkParentToChild(currNode, myNode);
  std::shared_ptr<ABSNode> parent(currNode);
  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseBreakStmt(S);
  currNode = parent;

  std::cout<<"[LOG6302] Fin Traverse d'un saut : \" break\"\n";

  return true;
}

/**********************/
/* continue traverse           */
/**********************/
bool Visitor::TraverseContinueStmt(clang::ContinueStmt *S) {
  if (!inMethod) {
    return true;
  }

  std::cout<<"[LOG6302] Traverse d'un saut : \" continue\"\n";

  std::shared_ptr<ABSNode> myNode(new JumpNode());
  myAst->linkParentToChild(currNode, myNode);
  std::shared_ptr<ABSNode> parent(currNode);
  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseContinueStmt(S);
  currNode = parent;

  std::cout<<"[LOG6302] Fin Traverse d'un saut : \" continue\"\n";

  return true;
}

/**********************/
/* for traverse           */
/**********************/
bool Visitor::TraverseForStmt(clang::ForStmt *S) {
  if (!inMethod) {
    return true;
  }

  std::cout<<"[LOG6302] Traverse d'une boucle : \"for\"("<<GetStatementString(S->getCond())<<")\n";

  std::shared_ptr<ABSNode> myNode(new LoopNode());
  myAst->linkParentToChild(currNode, myNode);
  std::shared_ptr<ABSNode> parent(currNode);
  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseForStmt(S);
  currNode = parent;

  std::cout<<"[LOG6302] Fin Traverse d'une boucle : \" for\"\n";

  return true;
}

/**********************/
/* while traverse           */
/**********************/
bool Visitor::TraverseWhileStmt(clang::WhileStmt *S) {
  if (!inMethod) {
    return true;
  }

  std::cout<<"[LOG6302] Traverse d'une boucle : \"while\"("<<GetStatementString(S->getCond())<<")\n";

  std::shared_ptr<ABSNode> myNode(new LoopNode());
  myAst->linkParentToChild(currNode, myNode);
  std::shared_ptr<ABSNode> parent(currNode);
  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseWhileStmt(S);
  currNode = parent;

  std::cout<<"[LOG6302] Fin Traverse d'une boucle : \" while\"\n";

  return true;
}
