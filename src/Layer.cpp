#include"Layer.hpp"

int Layer::GetSize() {
    return neurons.size();
}

vsptr<Neuron> & Layer::GetNeurons() {
    return neurons;
}

void Layer::BuildInput(NeuronTemplates * templates, ID * neuron_id, int size) {
    for(int i = 0; i < size; i++) {
        sptr<Neuron> neuron = std::make_shared<Neuron>(neuron_id->GetNewID(), templates->GetNeuronTemplate("RegularSpiking"));
        neurons.push_back(neuron);
    }
}

void Layer::BuildStandard(NeuronTemplates * templates, 
                        LayerTemplate & lt,
                        ID * neuron_id,
                        std::mt19937_64 & rng) {

        std::discrete_distribution<int> layerDist(lt.conn_probs_by_layer.begin(), lt.conn_probs_by_layer.end());
        
        for(int n = 0; n < lt.num_neurons; n++) {

            sptr<Neuron> neuron = std::make_shared<Neuron>(neuron_id->GetNewID(), templates->GetNeuronTemplate(lt.neuron_type));

            for(int d = 0; d < lt.dtrees_per_neuron; d++) {

                sptr<DTree> dtree = std::make_shared<DTree>();

                for(int s = 0; s < lt.syn_per_dtree; s++) {

                    sptr<Synapse> synapse = std::make_shared<Synapse>();
                    synapse->SetDTree(dtree);

                    int layer_index = layerDist(rng);
                    sptr<Layer> layer = lt.input_layers[layer_index];
                    std::uniform_int_distribution<int> nDist(0,layer->neurons.size()-1);
                    int neuron_index = nDist(rng);
                    sptr<Neuron> pre = layer->neurons[neuron_index];

                    pre->AddOutputSynapse(synapse);
                    neuron->AddInputSynapse(synapse);

                    synapses.push_back(synapse);
                }

            }

            neurons.push_back(neuron);

        }

    }