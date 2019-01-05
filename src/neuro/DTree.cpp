#include"DTree.hpp"
#include"Synapse.hpp"

DTree::DTree() {

}

void DTree::AddSynapse(wptr<Synapse> synapse) {
    recently_active.push_back(synapse);
}

void DTree::AddActivity(sptr<Synapse> synapse, uint64_t time) {

    for(lwptr<Synapse>::iterator it = recently_active.begin();
            it != recently_active.end(); ) {
        
        sptr<Synapse> syn = it->lock();
        
        uint64_t * pre_spike_time = syn->GetPreSpikeTime();
        if(pre_spike_time != nullptr) {
            if(*pre_spike_time > growth_window) {
                it = recently_active.erase(it);
            } else {
                Grow(syn,synapse,time-*pre_spike_time);
                it++;
            }
        }
    }

}

void DTree::Grow(sptr<Synapse> first, sptr<Synapse> second, uint64_t diff_t) {
    double delta = growth_rate * std::exp(- diff_t / growth_window);
    first->AddStrength(delta);
    second->AddStrength(delta);
}