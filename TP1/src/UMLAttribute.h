#pragma once

#include <iostream>
#include <string>

class UMLAttribute
{
  public:
    UMLAttribute(const std::string& name,
       const std::string& type,
       int visibility);
    std::string getAsString() const;
    std::string getName() const;
  private:
    std::string attName;
    int vis;
    std::string attType;
};
