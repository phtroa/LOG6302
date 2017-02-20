#include "Visitor.h"

  Visitor::Visitor(clang::ASTContext &context,
     std::shared_ptr<ASTTree> ast,
     std::shared_ptr<MetaTree> info)
      : context_(context), myAst(ast), infoTree(info), inMethod(false) {
    currNode = ast->getRoot();
  }

  std::shared_ptr<ASTTree> Visitor::getAST() {
    return myAst;
  }

  void Visitor::setAST(std::shared_ptr<ASTTree> ast) {
    myAst = ast;
  }

bool Visitor::isHeaderSystem(clang::Decl* D) const
{
  clang::FullSourceLoc location = context_.getFullLoc(D->getLocation());
  if (context_.getSourceManager().isInSystemHeader(D->getLocation())
    || context_.getSourceManager().isInExternCSystemHeader(D->getLocation())) {
    return true;
  }

  return false;
}
/***********************/
/* C++ Method traverse */
/***********************/
bool Visitor::TraverseCXXMethodDecl(clang::CXXMethodDecl *D) {
  if (!D->isThisDeclarationADefinition() || isHeaderSystem(D)) {
    return true;
  }

  inMethod = true;

  clang::FullSourceLoc location = context_.getFullLoc(D->getLocStart());

  //In case something went wrong during the compilation
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (context_.getSourceManager().getFileEntryForID(location.getFileID()) != nullptr) {
    file_path   = context_.getSourceManager().getFileEntryForID(location.getFileID())->getName();
    line_number = location.getSpellingLineNumber();
    col_number = location.getSpellingColumnNumber();
  }
  else {
    std::cerr << "got nullptr in CXXMethodDecl" << std::endl;
  }
  std::string methodName = D->getNameAsString();
  std::string methodID(methodName);
  //We create an id unique to the method
  //c++ standard states that two method cannot have the
  //same name and argument type
  for (int i = 0; i < D->getNumParams(); i++) {
    clang::QualType type = D->getParamDecl(i)->getOriginalType();
    methodID = methodID + type.getAsString();
  }
  clang::QualType qualReturn = D->getResultType();
  std::string returnType = qualReturn.getAsString();

  std::cout
    <<"[LOG6302] Traverse de la méthode \""
    << methodName
    <<"\" ("
    << file_path
    << ":"
    << line_number
    << ","
    << col_number
    << " id: "
    << methodID
    << " return Type :"
    << returnType
    <<")\n";


  //We need to test if the method has already been visited
  clang::FullSourceLoc locationClass = context_.getFullLoc(D->getParent()->getLocStart());
  std::string className = D->getParent()->getNameAsString();
  std::string classID = computeID(D->getParent()) + className;
  //classID = className;
  if (infoTree->isMethodIn(classID, methodID)) {
    inMethod = false;
    return true; //has already been added to the AST
  }
  infoTree->addMethodIn(classID, methodID);

  std::shared_ptr<ABSNode> parent = infoTree->getPtrToClass(classID);
  std::cout<<"[debug] className \""<< className <<"\"\n";
  std::shared_ptr<ABSNode> myNode(new MethodNode(methodName, file_path, D->getAccess()));
  MethodNode* myNodeRaw = static_cast<MethodNode*>(myNode.get());
  myNodeRaw->setReturnType(returnType);
  for (auto it = D->param_begin(); it != D->param_end(); it++) {
    clang::QualType type = (*it)->getOriginalType();
    myNodeRaw->addArgType(type.getAsString());
  }

  if (parent == nullptr)
      std::cout << "nullptr in method!!" << '\n';
  myAst->linkParentToChild(parent, myNode);
  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseCXXMethodDecl(D);
  currNode = parent;

  std::cout<<"[LOG6302] Fin traverse de la méthode \""<< methodName <<"\"\n";

  inMethod = false;

  return true;
}


void Visitor::completeBaseList(clang::CXXRecordDecl *D, std::shared_ptr<ABSNode> classNode)
{
  ClassNode* myNodeRaw = static_cast<ClassNode*>(classNode.get());
  for (auto it = D->bases_begin(); it != D->bases_end(); it++) {
    clang::CXXRecordDecl* pbase = it->getType()->getAsCXXRecordDecl();
    if (pbase != nullptr) {
      std::string baseName = computeID(pbase) + pbase->getNameAsString();
      myNodeRaw->addBaseName(baseName);
    }
  }
}

/**********************/
/* classe traverse    */
/**********************/
bool Visitor::TraverseCXXRecordDecl(clang::CXXRecordDecl *D)
{
  if (D->getNameAsString().empty() || isHeaderSystem(D))
    return true;

  std::string className(D->getNameAsString());
  std::cout<<"[LOG6302] Traverse de la classe \""<< className <<"\"\n";

  clang::FullSourceLoc location = context_.getFullLoc(D->getLocStart());

  std::string  file_path("");
  std::string  id = computeID(D) + className;
  if (context_.getSourceManager().getFileEntryForID(location.getFileID()) != nullptr) {
    file_path = context_.getSourceManager().getFileEntryForID(location.getFileID())->getName();
    std::cout<<"[LOG6302] Traverse de la classe \""<< className << "(id = )"
             << " in file " << file_path << " at " << location.getSpellingLineNumber() <<"\"\n";
  }

  //Since We are building only one tree, we need to verify if we have already
  //encounter the class
  std::shared_ptr<ABSNode> myNode;
  if (!infoTree->isClassIn(id)) {
    myNode = std::shared_ptr<ABSNode>(new ClassNode(className, file_path, id));
    infoTree->addPtrToClass(id, myNode);
    if (D->hasDefinition()) {
      completeBaseList(D, myNode);
      infoTree->initializedClass(id, true);
    }
    else {
      infoTree->initializedClass(id, false);
    }
    //We add the class to the Tree information
    myAst->linkParentToChild(currNode, myNode);
  }
  else {
    myNode = infoTree->getPtrToClass(id);
    if (D->hasDefinition() && !infoTree->isInitialised(id)) {
      completeBaseList(D, myNode);
      infoTree->initializedClass(id, true);
    }
  }
  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseCXXRecordDecl(D);
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin traverse de la classe \""<< className <<"\"\n";

  return true;
}

InfoType Visitor::extractedFinalType(const clang::QualType& type)
{
  clang::QualType baseType(type);
  while(baseType->isArrayType()) {
    std::cout << "in array type " << type.getAsString() << '\n';
    baseType = baseType->getAsArrayTypeUnsafe()->getElementType();
  }
  while(baseType->isPointerType()) {
    baseType = baseType->getPointeeType();
  }

  clang::CXXRecordDecl* D = baseType->getAsCXXRecordDecl(); //is in fact dyn_cast_or_null<CXXRecordDecl>(getAsTagDecl());

  if (D != nullptr && !D->getNameAsString().empty()
                   && infoTree->isClassIn(computeID(D) + D->getNameAsString())) {
    return InfoType(type.getAsString(), computeID(D) + D->getNameAsString());
  }

  return InfoType(type.getAsString());
}

std::string Visitor::computeID(const clang::DeclContext* D) const
{
  std::string id;
  D = D->getEnclosingNamespaceContext();
  while (!D->isTranslationUnit()) {
    if (D->isNamespace()) {
      id = (static_cast<const clang::NamespaceDecl*>(D))->getNameAsString() + id;
    }
    D = D->getParent();
  }

  return id;
}

bool Visitor::TraverseNamespaceDecl(clang::NamespaceDecl *D)
{
  if (isHeaderSystem(D)) {
    return true;
  }
  std::shared_ptr<ABSNode> myNode;
  std::string namespaceName = D->getNameAsString();
  std::string namespaceId = computeID(D);
  if (!infoTree->isNamespaceIn(namespaceId)) {
    myNode = std::shared_ptr<ABSNode>(new NamespaceNode(namespaceName, namespaceId));
    //We add the class to the Tree information
    infoTree->addPtrToNamespace(namespaceId, myNode);
    myAst->linkParentToChild(currNode, myNode);
  }
  else {
    myNode = infoTree->getPtrToNamespace(namespaceId);
  }

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseNamespaceDecl(D);
  currNode = myNode->getParent();

  return true;
}

/**********************/
/* attributes traverse     */
/**********************/
bool Visitor::TraverseFieldDecl(clang::FieldDecl *D) {
  if (isHeaderSystem(D)) {
    return true;
  }

  std::string attName = D->getNameAsString();
  std::string className = D->getParent()->getNameAsString();
  std::string classID = computeID(D->getParent()) + className;
  //classID = className;
  if (attName.empty()) {
    std::cerr << "Attribut with empty name" << std::endl;
  }
  else if (infoTree->isAttributIn(classID, attName)) {
    return true;
  }
  infoTree->addAttributIn(classID, attName);

  std::string visStr;
  switch (D->getAccess()) {
    case 0:
      visStr = "public";
      break;
    case 1:
      visStr = "protected";
      break;
    case 2:
      visStr = "private";
      break;
    case 3:
      visStr = "none";
      break;
  }
  std::cout<<"[LOG6302] Traverse d'un attribut : \"" << attName << " visibilité : " << visStr << "\"\n";

  InfoType iType = extractedFinalType(D->getType());
  if (iType.isRelatedToClassType())
    std::cout<<"Il est une autre classe: \"" << iType.getRefClassId() <<  "\"\n";

  if (!infoTree->isClassIn(classID)) {
    std::cerr << "Erreur dans Attribut, classe : " << className << " inconnue " << std::endl;
  }
  std::shared_ptr<ABSNode> myClassNode = infoTree->getPtrToClass(classID); //the class is always present in the AST before the attribut

  clang::QualType qualReturn = D->getType();
  std::string attType = qualReturn.getAsString();
  std::shared_ptr<ABSNode> myNode(new AttributeNode(attName, iType, D->getAccess()));
  myAst->linkParentToChild(myClassNode, myNode); //we link to the class

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseFieldDecl(D);
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin Traverse d'un attribut : \"" << attName << "\"\n";

  return true;
}

/**********************/
/* variable traverse  */
/**********************/
bool Visitor::TraverseVarDecl(clang::VarDecl *D) {
  if (!inMethod || isHeaderSystem(D)) {
    return true;
  }

  std::string varName = D->getNameAsString();
  std::cout<<"[LOG6302] Traverse de la variable \""<< varName <<"\"\n";

  std::shared_ptr<ABSNode> myNode(new VarNode(varName));
  myAst->linkParentToChild(currNode, myNode);

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseVarDecl(D);
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin traverse de la variable \""<< varName <<"\"\n";

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

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseIfStmt(S);
  currNode = myNode->getParent();

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

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseSwitchStmt(S);
  currNode = myNode->getParent();

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

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseBreakStmt(S);
  currNode = myNode->getParent();

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

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseContinueStmt(S);
  currNode = myNode->getParent();

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

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseForStmt(S);
  currNode = myNode->getParent();

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

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseWhileStmt(S);
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin Traverse d'une boucle : \" while\"\n";

  return true;
}
