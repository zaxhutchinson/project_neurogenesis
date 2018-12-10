#ifndef LAYER_HPP
#define LAYER_HPP

#include<random>

#include"cereal/archives/binary.hpp"
#include"cereal/types/vector.hpp"
#include"cereal/types/memory.hpp"

#include"zxlb.hpp"
#include"NTemplate.hpp"
#include"DTree.hpp"
#include"Neuron.hpp"
#include"Synapse.hpp"

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
};

struct Layer {
    
    vsptr<Neuron> neurons;
    lsptr<Synapse> synapses;

    ///////////////////////////////////////////////////////////////////////////
    template<class Archive>
    void save(Archive & ar) const {
        ar(neurons,synapses);
    }

    template<class Archive>
    void load(Archive & ar) {
        ar(neurons,synapses);
    }
    ///////////////////////////////////////////////////////////////////////////

    int GetSize();
    vsptr<Neuron> & GetNeurons();

    ///////////////////////////////////////////////////////////////////////////
    void BuildInput(NeuronTemplates * templates, int size);

    void BuildStandard(NeuronTemplates * templates, 
                        LayerTemplate & lt,
                        std::mt19937_64 & rng);
};

#endif