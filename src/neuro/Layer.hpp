#ifndef LAYER_HPP
#define LAYER_HPP

#include<random>
#include<utility>
#include<algorithm>

#include"cereal/archives/binary.hpp"
#include"cereal/types/list.hpp"
#include"cereal/types/vector.hpp"
#include"cereal/types/memory.hpp"

#include"zxlb.hpp"
#include"NTemplate.hpp"
#include"DTree.hpp"
#include"Neuron.hpp"
#include"Synapse.hpp"
#include"ID.hpp"

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
struct Layer;
struct LayerTemplate {
    uint64_t layer_id;
    vsptr<Layer> input_layers;
    vec<double> conn_probs_by_layer;
    std::string neuron_type;
    int num_neurons;
    int dtrees_per_neuron;
    double dtree_growth_rate;
    uint64_t dtree_growth_window;
    int syn_per_dtree;
    double syn_weight;
};

/* Layer
    Provides structure to the network.
    Keeps a weak_ptr to any layers to which its neurons provide input (children)
        but these links are not used to update the model.
*/
struct Layer {
    uint64_t id;
    vsptr<Neuron> neurons;
    lsptr<Synapse> synapses;
    vwptr<Layer> layers;   

    ///////////////////////////////////////////////////////////////////////////
    template<class Archive>
    void save(Archive & ar) const {
        ar(id,neurons,synapses,layers);
    }

    template<class Archive>
    void load(Archive & ar) {
        ar(id,neurons,synapses,layers);
    }
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    
};



#endif