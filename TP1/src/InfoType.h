#pragma once

#include <string>

class InfoType
{
  public:
    InfoType();
    InfoType(const std::string& typeName);
    InfoType(const std::string& typeName, const std::string& classId);

    bool isRelatedToClassType() const;
    std::string getRefClassId() const ;

    std::string getType() const;

  private:
    bool referToClass;
    std::string currTypeName;
    std::string refClassId;
};
