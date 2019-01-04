#include"ModelBuilder.hpp"


void BuildInputLayer(Model * model, Options & ops, NeuronTemplates * nt) {
    // Create the input layer
    sptr<Layer> input_layer = std::make_shared<Layer>();
    
    // Create the input vector
    model->input_vector = std::make_shared<InputVector>(ops.input_size);

    // Build the neurons & link to input vector
    for(int i = 0; i < ops.input_size; i++) {
        sptr<Neuron> neuron = std::make_shared<Neuron>(model->neuron_id->GetNewID(),
                                                    nt->GetNeuronTemplate("RegularSpiking"));
        neuron->SetExternalInput(model->input_vector->GetInput(i));
        input_layer->neurons.push_back(neuron);
    }

    model->layers.push_back(input_layer);

}

void BuildLayerFromTemplate(Model * model, NeuronTemplates * nt, LayerTemplate & lt, RNG * rng) {

    // Create new layer
    sptr<Layer> new_layer = std::make_shared<Layer>();

    // Create an address book of all neurons in all layers
    // to prevent adding synapses to the same DTree with
    // the same presynaptic neuron.
    vec<tuple<int,int>> neuron_addresses;
    for(int i = 0; i < lt.input_layers.size(); i++) {
        for(int k = 0; k < lt.input_layers[i]->neurons.size(); k++) {
            neuron_addresses.push_back(tuple<int,int>(i,k));
        }
    }
    std::shuffle(neuron_addresses.begin(),neuron_addresses.end(),*rng);

    // Distribution to pick layers.
    std::discrete_distribution<int> layerDist(lt.conn_probs_by_layer.begin(), lt.conn_probs_by_layer.end());

    // For each new Neuron
    for(int n = 0; n < lt.num_neurons; n++) {

        sptr<Neuron> neuron = std::make_shared<Neuron>(model->neuron_id->GetNewID(), nt->GetNeuronTemplate(lt.neuron_type));

        // For each DT
        for(int t = 0; t < lt.dtrees_per_neuron; t++) {

            sptr<DTree> dtree = std::make_shared<DTree>();

            for(int s = 0; s < lt.syn_per_dtree; s++) {
                tuple<int,int> addr = neuron_addresses[s];

                sptr<Synapse> syn = std::make_shared<Synapse>(lt.syn_weight);
                syn->InitAsProto(dtree);

                sptr<Layer> layer = lt.input_layers[addr.first];
                sptr<Neuron> pre = layer->neurons[addr.second];

                pre->AddOutputSynapse(syn);
                neuron->AddInputSynapse(syn);

                new_layer->synapses.push_back(syn);

            }
            std::shuffle(neuron_addresses.begin(),neuron_addresses.end(),*rng);

        }

        new_layer->neurons.push_back(neuron);

    }

    for(int l = 0; l < lt.input_layers.size(); l++) {
        lt.input_layers[l]->layers.push_back(new_layer);
    }

    model->layers.push_back(new_layer);

}