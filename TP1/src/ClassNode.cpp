#include "ClassNode.h"

#include "ABSASTVisitor.h"

ClassNode::ClassNode(const std::string& name, const std::string& file,
                                              const std::string& id)
 : className(name), filePath(file), classId(id)
{
}

std::string ClassNode::getID() const
{
  return classId;
}

void ClassNode::setClassName(const std::string& name)
{
  className = name;
}

std::string ClassNode::getClassName() const
{
  return className;
}

void ClassNode::setFilePath(const std::string& file)
{
  filePath = file;
}

std::string ClassNode::getFilePath() const
{
  return filePath;
}

void ClassNode::addBaseName(const std::string& name)
{
  basesNames.push_back(name);
}

std::vector<std::string>::iterator ClassNode::baseBegin()
{
  return basesNames.begin();
}
std::vector<std::string>::iterator ClassNode::baseEnd()
{
  return basesNames.end();
}

void ClassNode::acceptVisitor(ABSASTVisitor* visitor)
{
  visitor->visitPre(this);
  for (int i = 0; i < children.size(); i++) {
    children[i]->acceptVisitor(visitor);
  }
  visitor->visitPost(this);
}
