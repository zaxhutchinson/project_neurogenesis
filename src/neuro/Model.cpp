#include"Model.hpp"

void Model::PrintModelDetails() {

    std::cout << "Model details for " + name << std::endl
        << "Number of Layers: " << std::to_string(layers.size()) << std::endl;

    for(int i = 0; i < layers.size(); i++) {
        std::cout << "LAYER " << std::to_string(i)
            << "  " << std::to_string(layers[i]->neurons.size()) << " neurons" << std::endl;

        // if(i==1) {
        //     for(int j = 0; j < layers[i]->synapses.size(); j++)  {
        //         for(lsptr<Synapse>::iterator it = layers[i]->synapses.begin(); it != layers[i]->synapses.end(); it++) {
        //             if((*it)->GetStrength() > 0.0) {
        //                 std::cout << "STRENGTH: " << std::to_string((*it)->GetStrength()) << std::endl;
        //             }
        //         }
        //     }
        // }
    }


}