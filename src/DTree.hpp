#ifndef DTREE_HPP
#define DTREE_HPP

#include<memory>

#include"spspdef.hpp"

class ProtoSynapse;
class DTree {
public:
    DTree();
    virtual ~DTree();

    void Grow(sptr<ProtoSynapse> synapse, uint64_t time);
private:
    double growth_rate;
    uint64_t growth_window;
    qsptr<ProtoSynapse> recently_active;
};


#endif