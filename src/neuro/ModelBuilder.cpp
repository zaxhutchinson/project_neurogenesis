#include"ModelBuilder.hpp"


void BuildInputLayer(Model * model, Options * ops, NeuronTemplates * nt) {
    // Create the input layer
    sptr<Layer> input_layer = std::make_shared<Layer>();
    input_layer->id=model->layer_id->GetNewID();
    
    // Create the input vector
    model->input_vector = std::make_shared<InputVector>(ops->input_size);

    // Build the neurons & link to input vector
    for(int i = 0; i < ops->input_size; i++) {
        sptr<Neuron> neuron = std::make_shared<Neuron>(input_layer->neuron_ids.GetNewID(),
                                                    nt->GetNeuronTemplate("RegularSpiking"));
        neuron->SetExternalInput(model->input_vector->GetInput(i));
        input_layer->neurons.push_back(neuron);
    }

    model->layers.push_back(input_layer);

}

void BuildLayerFromTemplate(Model * model, NeuronTemplates * nt, LayerTemplate * lt, RNG * rng) {

    // Create new layer
    sptr<Layer> new_layer = std::make_shared<Layer>();
    new_layer->id=model->layer_id->GetNewID();

    // Create an address book of all neurons in all layers
    // to prevent adding synapses to the same DTree with
    // the same presynaptic neuron.
    vec<tuple<int,int>> neuron_addresses;
    for(int i = 0; i < lt->input_layers.size(); i++) {
        for(int k = 0; k < lt->input_layers[i]->neurons.size(); k++) {
            neuron_addresses.push_back(tuple<int,int>(i,k));
        }
    }

    std::shuffle(neuron_addresses.begin(),neuron_addresses.end(),*rng);

    // Distribution to pick layers.
    std::discrete_distribution<int> layerDist(lt->conn_probs_by_layer.begin(), lt->conn_probs_by_layer.end());

    // For each new Neuron
    for(int n = 0; n < lt->num_neurons; n++) {

        sptr<Neuron> neuron = std::make_shared<Neuron>(new_layer->neuron_ids.GetNewID(), nt->GetNeuronTemplate(lt->neuron_type));

        // For each DT
        for(int t = 0; t < lt->dtrees_per_neuron; t++) {

            sptr<DTree> dtree = std::make_shared<DTree>(lt->dtree_growth_rate, lt->dtree_growth_window);
            dtree->SetMaxMatureSynapses(lt->dtree_max_mature_synapses);

            for(int s = 0; s < lt->syn_per_dtree; s++) {

                tuple<int,int> addr = neuron_addresses[s];

                sptr<Synapse> syn = std::make_shared<Synapse>(lt->syn_weight);
                syn->AddDTree(dtree);
                syn->InitAsProto();
                syn->SetMaturityThreshold(lt->syn_maturity_threshold);

                sptr<Layer> layer = lt->input_layers[addr.first];
                sptr<Neuron> pre = layer->neurons[addr.second];

                pre->AddOutputSynapse(syn);
                neuron->AddInputSynapse(syn);

                new_layer->synapses.push_back(syn);

            }
            std::shuffle(neuron_addresses.begin(),neuron_addresses.end(),*rng);

        }

        new_layer->neurons.push_back(neuron);

    }

    for(int l = 0; l < lt->input_layers.size(); l++) {
        lt->input_layers[l]->layers.push_back(new_layer);
    }

    std::cout << "NUM SYN: " << new_layer->synapses.size() << std::endl;

    model->layers.push_back(new_layer);

}


void BuildModel_A_0(Model * model, Options * options, NeuronTemplates * nt, RNG * rng) {

    // Build the input layer
    BuildInputLayer(model,options,nt);

    // Build the first layer.
    LayerTemplate lt_1;
    lt_1.layer_id=1;
    lt_1.input_layers.push_back(model->layers[0]);
    lt_1.conn_probs_by_layer.push_back(1.0);
    lt_1.num_neurons=400;
    lt_1.dtrees_per_neuron=3;
    lt_1.dtree_growth_rate=1.0;
    lt_1.dtree_growth_window=50;
    lt_1.syn_per_dtree=5;
    lt_1.neuron_type="RegularSpiking";
    lt_1.syn_weight=100.0;

    BuildLayerFromTemplate(model,nt,&lt_1,rng);
}

void BuildModel_A_1(Model * model, Options * options, NeuronTemplates * nt, RNG * rng) {

    // Build the input layer
    BuildInputLayer(model,options,nt);

    // Build the first layer.
    LayerTemplate lt_1;
    lt_1.layer_id=1;
    lt_1.input_layers.push_back(model->layers[0]);
    lt_1.conn_probs_by_layer.push_back(1.0);
    lt_1.num_neurons=1000;
    lt_1.dtrees_per_neuron=4;
    lt_1.dtree_growth_rate=1.0;
    lt_1.dtree_growth_window=25;
    lt_1.syn_per_dtree=2;
    lt_1.neuron_type="RegularSpiking";
    lt_1.syn_weight=200.0;
    lt_1.syn_maturity_threshold=100;
    lt_1.dtree_max_mature_synapses=lt_1.syn_per_dtree;

    BuildLayerFromTemplate(model,nt,&lt_1,rng);

    // Build the second layer.
    LayerTemplate lt_2;
    lt_2.layer_id=2;
    lt_2.input_layers.push_back(model->layers[1]);
    lt_2.conn_probs_by_layer.push_back(1.0);
    lt_2.num_neurons=100;
    lt_2.dtrees_per_neuron=10;
    lt_2.dtree_growth_rate=1.0;
    lt_2.dtree_growth_window=100;
    lt_2.syn_per_dtree=2;
    lt_2.neuron_type="RegularSpiking";
    lt_2.syn_weight=160.0;
    lt_2.syn_maturity_threshold=100;
    lt_2.dtree_max_mature_synapses=lt_2.syn_per_dtree;

    BuildLayerFromTemplate(model,nt,&lt_2,rng);

    // Build the second layer.
    LayerTemplate lt_3;
    lt_3.layer_id=3;
    lt_3.input_layers.push_back(model->layers[2]);
    lt_3.conn_probs_by_layer.push_back(1.0);
    lt_3.num_neurons=100;
    lt_3.dtrees_per_neuron=10;
    lt_3.dtree_growth_rate=1.0;
    lt_3.dtree_growth_window=500;
    lt_3.syn_per_dtree=2;
    lt_3.neuron_type="RegularSpiking";
    lt_3.syn_weight=120.0;
    lt_3.syn_maturity_threshold=100;
    lt_3.dtree_max_mature_synapses=lt_3.syn_per_dtree;

    BuildLayerFromTemplate(model,nt,&lt_3,rng);

}