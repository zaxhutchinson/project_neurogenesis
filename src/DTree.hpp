#ifndef DTREE_HPP
#define DTREE_HPP

#include<memory>

#include"spspdef.hpp"
#include"Synapse.hpp"

struct DTreeNode {
    sptr<Synapse> synapse;
    double maturity;
};

class DTree {
public:
    DTree();
    virtual ~DTree();
private:
    lsptr<DTreeNode> nodes;
};


#endif