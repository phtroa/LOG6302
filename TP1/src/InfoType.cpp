#include "InfoType.h"

InfoType::InfoType() : referToClass(false)
{
}

InfoType::InfoType(const std::string& typeName)
: currTypeName(typeName), referToClass(false)
{
}

InfoType::InfoType(const std::string& typeName, const std::string& classId)
: currTypeName(typeName), referToClass(true), refClassId(classId)
{
}

bool InfoType::isRelatedToClassType() const
{
  return referToClass;
}

std::string InfoType::getRefClassId() const
{
  return refClassId;
}

std::string InfoType::getType() const
{
  return currTypeName;
}
