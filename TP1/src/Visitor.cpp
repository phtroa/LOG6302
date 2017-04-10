#include "Visitor.h"

  Visitor::Visitor(clang::ASTContext &context,
     std::shared_ptr<ASTTree> ast,
     std::shared_ptr<MetaTree> info)
      : context_(context), myAst(ast), infoTree(info), inMethod(false), ifDepth(0) {
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

bool Visitor::extractLocationInfo(const clang::FullSourceLoc& location,
                                  std::string& filname, unsigned int& line_number,
                                   unsigned int& col_number)
{
  filname = "Unknown";
  line_number = 0;
  col_number = 0;
  if (context_.getSourceManager().getFileEntryForID(location.getFileID()) != nullptr) {
    filname   = context_.getSourceManager().getFileEntryForID(location.getFileID())->getName();
    line_number = location.getSpellingLineNumber();
    col_number = location.getSpellingColumnNumber();

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
  if (!extractLocationInfo(location, file_path, line_number, col_number)) {
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
  if (infoTree->isMethodIn(classID, methodID)) {
    inMethod = false;
    return true; //has already been added to the AST
  }
  infoTree->addMethodIn(classID, methodID);

  std::shared_ptr<ABSNode> parent = infoTree->getPtrToClass(classID);
  std::cout<<"[debug] className \""<< className <<"\"\n";
  std::shared_ptr<ABSNode> myNode(new MethodNode(methodName, file_path,
                                                line_number, D->getAccess()));
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

  std::string  id = computeID(D) + className;
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (!extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout<<"[LOG6302] Traverse de la classe \""<< className
             << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  //Since We are building only one tree, we need to verify if we have already
  //encounter the class
  std::shared_ptr<ABSNode> myNode;
  if (!infoTree->isClassIn(id)) {
    myNode = std::shared_ptr<ABSNode>(new ClassNode(className, file_path, id, line_number));
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
/*
bool Visitor::TraverseCallExpr(clang::CallExpr *S)
{
  if (!inMethod) {
    return true;
  }

  std::cout << "in CallExpr" << std::endl;
  clang::FullSourceLoc location = context_.getFullLoc(S->getLocStart());

  std::string name;
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (!extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cerr << "got nullptr in TraverseCallExpr" << std::endl;
  }

  //We extract the name
  clang::Expr* callee = S->getCallee();
  ValueExtractorVisitor valCalleeVisitor;
  valCalleeVisitor.TraverseStmt(callee);
  VarInStament varsOfCallee = valCalleeVisitor.getAllVar();
  for (int i = 0; i < varsOfCallee.getNumValues(); i++) {
    name = varsOfCallee.getValue(i);
  }


  //we look for the arg
  VarInStament vars;
  for (int i = 0; i < S->getNumArgs(); i++) {
    ValueExtractorVisitor valVisitor;
    VarInStament varsVis = valVisitor.getAllVar();
    for (int i = 0; i < varsVis.getNumValues(); i++) {
      vars.addValue(varsVis.getValue(i));
    }
  }

  std::shared_ptr<ABSNode> myNode(new FuncCall(name, line_number));
  myNode->setVars(vars);
  myAst->linkParentToChild(currNode, myNode); //we link to the class

  return true;
}*/

bool Visitor::TraverseNamespaceDecl(clang::NamespaceDecl *D)
{
  if (isHeaderSystem(D)) {
    return true;
  }

  std::string namespaceName = D->getNameAsString();
  clang::FullSourceLoc location = context_.getFullLoc(D->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout<<"[LOG6302] Traverse de la namespace \""<< namespaceName
             << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  std::shared_ptr<ABSNode> myNode;
  std::string namespaceId = computeID(D);
  if (!infoTree->isNamespaceIn(namespaceId)) {
    myNode = std::shared_ptr<ABSNode>(new NamespaceNode(namespaceName,
                                                      namespaceId, line_number));
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

  clang::FullSourceLoc location = context_.getFullLoc(D->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout<<"[LOG6302] Traverse d'un attribut : \"" << attName << " visibilité : " << visStr
             << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  InfoType iType = extractedFinalType(D->getType());
  if (iType.isRelatedToClassType())
    std::cout<<"Il est une autre classe: \"" << iType.getRefClassId() <<  "\"\n";

  if (!infoTree->isClassIn(classID)) {
    std::cerr << "Erreur dans Attribut, classe : " << className << " inconnue " << std::endl;
  }
  std::shared_ptr<ABSNode> myClassNode = infoTree->getPtrToClass(classID); //the class is always present in the AST before the attribut

  clang::QualType qualReturn = D->getType();
  std::string attType = qualReturn.getAsString();
  std::shared_ptr<ABSNode> myNode(new AttributeNode(attName, iType,
                                                    line_number, D->getAccess()));
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

  clang::FullSourceLoc location = context_.getFullLoc(D->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout<<"LOG6302] Traverse de la variable \""<< varName
             << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  std::shared_ptr<ABSNode> myNode(new VarNode(varName, line_number, false));
  if (D->hasInit()) {
    static_cast<VarNode*>(myNode.get())->setInit(true);
  }
  myAst->linkParentToChild(currNode, myNode);

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseVarDecl(D);
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin traverse de la variable \""<< varName <<"\"\n";

  return true;
}

bool Visitor::isInIf() const {
  return ifDepth > 0;
}
/**********************/
/* If traverse        */
/**********************/
bool Visitor::TraverseIfStmt(clang::IfStmt *S) {
  if (!inMethod) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(S->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout << "[LOG6302] Traverse d'une condition : \" if ("<<GetStatementString(S->getCond())<<")"
    << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  std::shared_ptr<ABSNode> myNode(new IfNode(line_number));
  ValueExtractorVisitor valVisitor;
  valVisitor.TraverseStmt(S->getCond());
  myNode->setVars(valVisitor.getAllVar());
  myAst->linkParentToChild(currNode, myNode);

  currNode = myNode;
  ifDepth++;
  clang::RecursiveASTVisitor<Visitor>::TraverseIfStmt(S);
  ifDepth--;
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin Traverse d'une condition : \" if ("<<GetStatementString(S->getCond())<<") \"\n";

  return true;
}

bool Visitor::TraverseBinAssign(clang::BinaryOperator *Bop) {
  std::cout << "[LOG6302] Traverse d'une assignation : " << std::endl;
  if (!inMethod || !Bop->isAssignmentOp()) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(Bop->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout<< " in file " << file_path << " at " << line_number <<"\"\n";
  }

  //Since we are in an assignation, the LHS must be a DeclRefExpr
  auto lhs = clang::dyn_cast_or_null<clang::DeclRefExpr>(Bop->getLHS());
  std::string varName;
  if (lhs != nullptr) {
    varName = lhs->getDecl()->getNameAsString();
  }
  std::shared_ptr<ABSNode> myNode(new AssignNode(varName, line_number));
  ValueExtractorVisitor valVisitor;
  valVisitor.TraverseStmt(Bop->getRHS());
  myNode->setVars(valVisitor.getAllVar());
  myAst->linkParentToChild(currNode, myNode);

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseBinaryOperator(Bop);
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin Traverse d'une assignation : " << std::endl;

  return true;
}

bool Visitor::TraverseUnaryPostInc(clang::UnaryOperator* Stmt) {
  std::cout << "[LOG6302] Traverse d'une assignation UnaryOperator : " << std::endl;
  if (!inMethod) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(Stmt->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout<< " in file " << file_path << " at " << line_number <<"\"\n";
  }

  //Since we are in an assignation, the LHS must be a DeclRefExpr
  auto lhs = clang::dyn_cast_or_null<clang::DeclRefExpr>(Stmt->getSubExpr());
  if (lhs != nullptr) {
    std::string varName;
    varName = lhs->getDecl()->getNameAsString();
    std::shared_ptr<ABSNode> myNode(new AssignNode(varName, line_number));
    myAst->linkParentToChild(currNode, myNode);
    currNode = myNode;
    clang::RecursiveASTVisitor<Visitor>::TraverseUnaryOperator(Stmt);
    currNode = myNode->getParent();
  }
  else {
    clang::RecursiveASTVisitor<Visitor>::TraverseUnaryOperator(Stmt);
  }

  std::cout<<"[LOG6302] Fin Traverse d'une assignation UnaryOperator: " << std::endl;

  return true;

}

bool Visitor::TraverseUnaryPostDec(clang::UnaryOperator* Stmt) {
  std::cout << "[LOG6302] Traverse d'une assignation UnaryOperator : " << std::endl;
  if (!inMethod) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(Stmt->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout<< " in file " << file_path << " at " << line_number <<"\"\n";
  }

  //Since we are in an assignation, the LHS must be a DeclRefExpr
  auto lhs = clang::dyn_cast_or_null<clang::DeclRefExpr>(Stmt->getSubExpr());
  if (lhs != nullptr) {
    std::string varName;
    varName = lhs->getDecl()->getNameAsString();
    std::shared_ptr<ABSNode> myNode(new AssignNode(varName, line_number));
    myAst->linkParentToChild(currNode, myNode);
    currNode = myNode;
    clang::RecursiveASTVisitor<Visitor>::TraverseUnaryOperator(Stmt);
    currNode = myNode->getParent();
  }
  else {
    clang::RecursiveASTVisitor<Visitor>::TraverseUnaryOperator(Stmt);
  }

  std::cout<<"[LOG6302] Fin Traverse d'une assignation UnaryOperator: " << std::endl;

  return true;

}

bool Visitor::TraverseUnaryPreInc(clang::UnaryOperator* Stmt) {
  std::cout << "[LOG6302] Traverse d'une assignation UnaryOperator : " << std::endl;
  if (!inMethod) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(Stmt->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout<< " in file " << file_path << " at " << line_number <<"\"\n";
  }

  //Since we are in an assignation, the LHS must be a DeclRefExpr
  auto lhs = clang::dyn_cast_or_null<clang::DeclRefExpr>(Stmt->getSubExpr());
  if (lhs != nullptr) {
    std::string varName;
    varName = lhs->getDecl()->getNameAsString();
    std::shared_ptr<ABSNode> myNode(new AssignNode(varName, line_number));
    myAst->linkParentToChild(currNode, myNode);
    currNode = myNode;
    clang::RecursiveASTVisitor<Visitor>::TraverseUnaryOperator(Stmt);
    currNode = myNode->getParent();
  }
  else {
    clang::RecursiveASTVisitor<Visitor>::TraverseUnaryOperator(Stmt);
  }

  std::cout<<"[LOG6302] Fin Traverse d'une assignation UnaryOperator: " << std::endl;

  return true;

}

bool Visitor::TraverseUnaryPreDec(clang::UnaryOperator* Stmt) {
  std::cout << "[LOG6302] Traverse d'une assignation UnaryOperator : " << std::endl;
  if (!inMethod) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(Stmt->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout<< " in file " << file_path << " at " << line_number <<"\"\n";
  }

  //Since we are in an assignation, the LHS must be a DeclRefExpr
  auto lhs = clang::dyn_cast_or_null<clang::DeclRefExpr>(Stmt->getSubExpr());
  if (lhs != nullptr) {
    std::string varName;
    varName = lhs->getDecl()->getNameAsString();
    std::shared_ptr<ABSNode> myNode(new AssignNode(varName, line_number));
    myAst->linkParentToChild(currNode, myNode);
    currNode = myNode;
    clang::RecursiveASTVisitor<Visitor>::TraverseUnaryOperator(Stmt);
    currNode = myNode->getParent();
  }
  else {
    clang::RecursiveASTVisitor<Visitor>::TraverseUnaryOperator(Stmt);
  }

  std::cout<<"[LOG6302] Fin Traverse d'une assignation UnaryOperator: " << std::endl;

  return true;

}

/**********************/
/* switch traverse    */
/**********************/
bool Visitor::TraverseSwitchStmt(clang::SwitchStmt *S) {
  if (!inMethod) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(S->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout << "[LOG6302] Traverse d'une condition : \" switch ("<<GetStatementString(S->getCond())<<") \"\n"
    << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  std::shared_ptr<ABSNode> myNode(new SwitchNode(line_number));
  myAst->linkParentToChild(currNode, myNode);

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseSwitchStmt(S);
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin Traverse d'une condition : \" switch ("<<GetStatementString(S->getCond())<<") \"\n";

  return true;
}

/**********************/
/* switch traverse    */
/**********************/
bool Visitor::TraverseCaseStmt (clang::CaseStmt  *S) {
  if (!inMethod) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(S->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout << "[LOG6302] Traverse d'un case"
    << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  std::shared_ptr<ABSNode> myNode(new CaseNode(line_number));
  myAst->linkParentToChild(currNode, myNode);

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseCaseStmt(S);
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin Traverse d'un case" << std::endl;

  return true;
}

bool Visitor::TraverseDefaultStmt (clang::DefaultStmt  *S) {
  if (!inMethod) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(S->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout << "[LOG6302] Traverse d'un case"
    << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  std::shared_ptr<ABSNode> myNode(new CaseNode(line_number));
  myAst->linkParentToChild(currNode, myNode);

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseDefaultStmt(S);
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin Traverse d'un case" << std::endl;

  return true;
}

/**********************/
/* break traverse     */
/**********************/
bool Visitor::TraverseBreakStmt(clang::BreakStmt *S) {
  if (!inMethod) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(S->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout << "[LOG6302] Traverse d'un saut : break"
    << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  std::shared_ptr<ABSNode> myNode(new BreakNode(line_number));
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

  clang::FullSourceLoc location = context_.getFullLoc(S->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout << "[LOG6302] Traverse d'un saut : continue"
    << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  std::shared_ptr<ABSNode> myNode(new ContinueNode(line_number));
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

  clang::FullSourceLoc location = context_.getFullLoc(S->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout << "[LOG6302] Traverse d'une boucle : \"for\"("<<GetStatementString(S->getCond())<<")\n"
    << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  clang::Expr* incr;
  std::shared_ptr<ABSNode> myNode(new ForNode(line_number));
  myNode->setVars(extractVars(S->getCond()));
  myAst->linkParentToChild(currNode, myNode);

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseStmt(S->getBody());
  clang::RecursiveASTVisitor<Visitor>::TraverseStmt(S->getInc());
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin Traverse d'une boucle : \" for\"\n";

  return true;
}

VarInStament Visitor::extractVars(clang::Stmt *S) const
{
  ValueExtractorVisitor valVisitor;
  valVisitor.TraverseStmt(S);
  return valVisitor.getAllVar();
}

/**********************/
/* while traverse           */
/**********************/
bool Visitor::TraverseWhileStmt(clang::WhileStmt *S) {
  if (!inMethod) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(S->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout << "[LOG6302] Traverse d'une boucle : while("<<GetStatementString(S->getCond())<<")\n"
    << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  std::shared_ptr<ABSNode> myNode(new WhileNode(line_number));
  myNode->setVars(extractVars(S->getCond()));
  myAst->linkParentToChild(currNode, myNode);

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseWhileStmt(S);
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin Traverse d'une boucle : \" while\"\n";

  return true;
}

bool Visitor::TraverseDoStmt(clang::DoStmt *S) {
  if (!inMethod) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(S->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout << "[LOG6302] Traverse d'une boucle : Dowhile("<<GetStatementString(S->getCond())<<")\n"
    << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  std::shared_ptr<ABSNode> myNode(new DoWhileNode(line_number));
  myAst->linkParentToChild(currNode, myNode);

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseDoStmt(S);
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin Traverse d'une boucle : \" Dowhile\"\n";

  return true;
}

/**********************/
/* return traverse           */
/**********************/
bool Visitor::TraverseReturnStmt(clang::ReturnStmt *S) {
  if (!inMethod) {
    return true;
  }

  clang::FullSourceLoc location = context_.getFullLoc(S->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout << "[LOG6302] Traverse d'un return"
    << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  std::shared_ptr<ABSNode> myNode(new ReturnNode(line_number));
  ValueExtractorVisitor valVisitor;
  valVisitor.TraverseStmt(S);
  myNode->setVars(valVisitor.getAllVar());
  myAst->linkParentToChild(currNode, myNode);

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseReturnStmt(S);
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin Traverse d'un return" << std::endl;

  return true;
}

/**********************/
/* ifBlock traverse           */
/**********************/
bool Visitor::TraverseCompoundStmt(clang::CompoundStmt *S) {
  if (!isInIf()) {
    return clang::RecursiveASTVisitor<Visitor>::TraverseCompoundStmt(S);
  }

  clang::FullSourceLoc location = context_.getFullLoc(S->getLocStart());
  std::string  file_path("Unknown");
  unsigned int line_number(0);
  unsigned int col_number(0);
  if (extractLocationInfo(location, file_path, line_number, col_number)) {
    std::cout << "[LOG6302] Traverse d'un block condition"
    << " in file " << file_path << " at " << line_number <<"\"\n";
  }

  std::shared_ptr<ABSNode> myNode(new BlockNode(line_number));
  myAst->linkParentToChild(currNode, myNode);

  currNode = myNode;
  clang::RecursiveASTVisitor<Visitor>::TraverseCompoundStmt(S);
  currNode = myNode->getParent();

  std::cout<<"[LOG6302] Fin Traverse d'un  block condition" << std::endl;

  return true;
}
