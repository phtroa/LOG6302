#pragma once

#include "ABSNode.h"

#include <string>
#include <vector>

//Represents a class
class ClassNode : public ABSNode {
public:
  ClassNode(const std::string& name, const std::string& file,
                                    const std::string& id,
                                    int line);
  ~ClassNode();

  std::string getID() const;
  void setClassName(const std::string& name);
  std::string getClassName() const;
  void setFilePath(const std::string& name);
  std::string getFilePath() const;

  void addBaseName(const std::string& name);
  std::vector<std::string>::iterator baseBegin();
  std::vector<std::string>::iterator baseEnd();

  void acceptVisitor(ABSASTVisitor* visitor);

private:
  std::string classId;
  std::string className;
  std::string filePath;
  std::vector<std::string> basesNames;
};
