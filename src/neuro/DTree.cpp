#include"DTree.hpp"
#include"Synapse.hpp"

DTree::DTree() {

}

DTree::DTree(double _growth_rate, uint64_t _growth_window) 
    : growth_rate(_growth_rate), growth_window(_growth_window) {

}

void DTree::AddSynapse(wptr<Synapse> synapse) {
    recently_active.push_back(synapse);
}

void DTree::AddActivity(sptr<Synapse> synapse, uint64_t time) {

    

    for(lwptr<Synapse>::iterator it = recently_active.begin();
            it != recently_active.end(); ) {
        
        uint64_t * pre_spike_time = it->lock()->GetPreSpikeTime();
        if(pre_spike_time != nullptr) {
            if(time-*pre_spike_time > growth_window) {
                it = recently_active.erase(it);
            } else {
                Grow(it->lock(),synapse,time-*pre_spike_time);
                it++;
            }
        } else {
            it++;
        }
    }

    // Add the newly spiked synapse after it has been compared to the others.
    AddSynapse(synapse);

}

void DTree::Grow(sptr<Synapse> first, sptr<Synapse> second, uint64_t diff_t) {
    double delta = growth_rate * std::exp(- static_cast<double>(diff_t) / static_cast<double>(growth_window));
    first->AddStrength(delta);
    second->AddStrength(delta);
}