#pragma once

#include <vector>
#include <string>

class VarInStament
{
public:
  VarInStament();
  void addValue(const std::string & varName);

  int getNumValues() const;
  std::string getValue(int i) const;

  bool hasValue() const;
  
private:
  std::vector<std::string> values;
};
