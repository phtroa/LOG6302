#include "DDGraphBuilder.h"

  void DDGraphBuilder::build(const CFG* graphIN, CFG & graphOUT,
     const std::vector<std::set<int>> & reachingDef,
       std::map<std::string,std::set<int>> & varnameToDef)
  {
    //fill the new graph and we convert lign numbers to id
    std::map<int,int> ligneToId;
    for (size_t i = 0; i < graphIN->getSize(); i++) {
      std::shared_ptr<CFGNode> node = graphIN->getNode(i);
      graphOUT.addNode(node);
      ligneToId[node->getLineNumber()] = node->getId();
    }

    //compute the definitions use at node i
    std::set<int> def;
    std::vector<std::set<int>> defUse(graphIN->getSize());
    for (int i = 0; i < graphIN->getSize(); i++) {
      VarInStament vars = graphIN->getNode(i)->getVars();
      std::set<int> allCurrUse = reachingDef[i];
      for (int j = 0; j < vars.getNumValues(); j++) {
        std::set<int> allCurrDef = varnameToDef[vars.getValue(j)];
        //intersection de toutes les definition de j avec celles présentes en i
        std::set_intersection(allCurrDef.begin(), allCurrDef.end(),
                          allCurrUse.begin(), allCurrUse.end(),
                                      inserter(def, def.end()));
      }
      defUse[i] = def;
      def.clear();
    }

    //create vertices def-Use
    for (int i = 0; i < graphIN->getSize(); i++) {
      for (auto it = defUse[i].begin(); it != defUse[i].end(); it++) {
        graphOUT.addVertice(ligneToId[*it], i);
        graphOUT.addReverseVertice(i, ligneToId[*it]);
      }
    }

  }
