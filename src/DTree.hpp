#ifndef DTREE_HPP
#define DTREE_HPP

#include<memory>
#include<cmath>

#include"spspdef.hpp"

class Synapse;
class DTree {
public:
    DTree();

    void AddSynapse(sptr<Synapse> synapse);

    void AddActivity(sptr<Synapse> synapse, uint64_t time);
    void Grow(sptr<Synapse> first, sptr<Synapse> second, uint64_t diff_t);
private:
    double growth_rate;
    uint64_t growth_window;
    lsptr<Synapse> recently_active;
};


#endif