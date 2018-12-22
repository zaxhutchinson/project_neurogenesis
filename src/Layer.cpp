#include"Layer.hpp"

// int Layer::GetSize() {
//     return neurons.size();
// }

// vsptr<Neuron> & Layer::GetNeurons() {
//     return neurons;
// }

// void Layer::BuildInput(NeuronTemplates * templates, ID * neuron_id, int size) {
//     for(int i = 0; i < size; i++) {
//         sptr<Neuron> neuron = std::make_shared<Neuron>(neuron_id->GetNewID(), templates->GetNeuronTemplate("RegularSpiking"));
//         neurons.push_back(neuron);
//     }
// }

// void Layer::BuildStandard(NeuronTemplates * templates, 
//                         LayerTemplate & lt,
//                         ID * neuron_id,
//                         std::mt19937_64 & rng) {

//     std::discrete_distribution<int> layerDist(lt.conn_probs_by_layer.begin(), lt.conn_probs_by_layer.end());

//     vec<std::pair<int,int>> neuron_addrs;
//     for(int l = 0; l < lt.input_layers.size(); l++) {
//         for(int n = 0; n < lt.input_layers[l]->GetNeurons().size(); n++) {
//             neuron_addrs.push_back(std::pair<int,int>(l,n));
//         }
//     }
//     std::shuffle(neuron_addrs.begin(),neuron_addrs.end(),rng);
    
//     for(int n = 0; n < lt.num_neurons; n++) {

//         sptr<Neuron> neuron = std::make_shared<Neuron>(neuron_id->GetNewID(), templates->GetNeuronTemplate(lt.neuron_type));
        
//         for(int d = 0; d < lt.dtrees_per_neuron; d++) {
            
//             sptr<DTree> dtree = std::make_shared<DTree>();
            
//             for(int s = 0, i=0; s < lt.syn_per_dtree; s++,i=(i+1)%neuron_addrs.size()) {

//                 std::pair<int,int> addr = neuron_addrs[i];

//                 sptr<Synapse> synapse = std::make_shared<Synapse>();
//                 synapse->SetDTree(dtree);

//                 sptr<Layer> layer = lt.input_layers[addr.first];
//                 sptr<Neuron> pre = layer->neurons[addr.second];

//                 pre->AddOutputSynapse(synapse);
//                 neuron->AddInputSynapse(synapse);

//                 synapses.push_back(synapse);

//             }

//             std::shuffle(neuron_addrs.begin(), neuron_addrs.end(), rng);
//         }
        
//         neurons.push_back(neuron);
//     }
// }
    