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
    DTree(double _growth_rate, uint64_t _growth_window);

    int GetMaxMatureSynapses();
    void SetMaxMatureSynapses(int ms);
    int GetCurMatureSynapses();
    void SetCurMatureSynapses(int ms);
    void AddMatureSynapse();

    bool IsActive();
    void SetActive(bool act);

    void AddSynapse(wptr<Synapse> synapse);

    void AddActivity(sptr<Synapse> synapse, uint64_t time);
    void Grow(sptr<Synapse> first, sptr<Synapse> second, uint64_t diff_t);

    ///////////////////////////////////////////////////////////////////////////
    template<class Archive>
    void save(Archive & ar) const {
        ar(growth_rate, growth_window, recently_active, max_mature_synapses, cur_mature_synapses, active);
    }

    template<class Archive>
    void load(Archive & ar) {
        ar(growth_rate, growth_window, recently_active, max_mature_synapses, cur_mature_synapses, active);
    }
    ///////////////////////////////////////////////////////////////////////////
private:
    double growth_rate;
    uint64_t growth_window;
    lwptr<Synapse> recently_active;
    int max_mature_synapses;
    int cur_mature_synapses;
    bool active;
};


#endif