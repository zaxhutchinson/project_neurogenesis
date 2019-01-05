#ifndef DTREE_HPP
#define DTREE_HPP

#include<memory>
#include<cmath>

#include"cereal/archives/binary.hpp"
#include"cereal/types/list.hpp"
#include"cereal/types/memory.hpp"

#include"zxlb.hpp"

class Synapse;
class DTree {
public:
    DTree();

    void AddSynapse(wptr<Synapse> synapse);

    void AddActivity(sptr<Synapse> synapse, uint64_t time);
    void Grow(sptr<Synapse> first, sptr<Synapse> second, uint64_t diff_t);

    ///////////////////////////////////////////////////////////////////////////
    template<class Archive>
    void save(Archive & ar) const {
        ar(growth_rate, growth_window, recently_active);
    }

    template<class Archive>
    void load(Archive & ar) {
        ar(growth_rate, growth_window, recently_active);
    }
    ///////////////////////////////////////////////////////////////////////////
private:
    double growth_rate;
    uint64_t growth_window;
    lwptr<Synapse> recently_active;
};


#endif