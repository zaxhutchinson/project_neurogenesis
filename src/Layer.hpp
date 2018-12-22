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
    vsptr<Layer> input_layers;
    vec<double> conn_probs_by_layer;
    std::string neuron_type;
    int num_neurons;
    int dtrees_per_neuron;
    int syn_per_dtree;

    int latinh_num_neurons;
    double latinh_conn_prob;
    std::string latinh_neuron_type;
};

struct Layer {
    
    vsptr<Neuron> neurons;
    lsptr<Synapse> synapses;
    vsptr<Layer> layers;

    ///////////////////////////////////////////////////////////////////////////
    template<class Archive>
    void save(Archive & ar) const {
        ar(neurons,synapses,layers);
    }

    template<class Archive>
    void load(Archive & ar) {
        ar(neurons,synapses,layers);
    }
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    
};



#endif