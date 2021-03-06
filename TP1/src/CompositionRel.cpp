#include "CompositionRel.h"

  CompositionRel::CompositionRel(const std::string& arrh) : arrowhead(arrh)
  {
  }

  void CompositionRel::dump(std::ostream& o) const
  {
    if (allLinks.size() <= 0)
      return;

    o << "edge [" << std::endl;
    o << "\t " << "arrowhead = " << "\"" << arrowhead << "\"" << std::endl;
    o << "]" << std::endl;
    for (auto it = allLinks.begin(); it != allLinks.end(); it++) {
      o << it->first << " -> " << it->second << std::endl;
    }
  }
