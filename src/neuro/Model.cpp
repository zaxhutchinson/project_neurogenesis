#include"Model.hpp"

void Model::PrintModelDetails() {

    std::cout << "Model details for " + name << std::endl
        << "Number of Layers: " << std::to_string(layers.size()) << std::endl;

    for(int i = 0; i < layers.size(); i++) {
        std::cout << "LAYER " << std::to_string(i)
            << "  " << std::to_string(layers[i]->neurons.size()) << " neurons" << std::endl;

        int mature=0;
        int proto=0;
        if(i>0) {
            for(lsptr<Synapse>::iterator it = layers[i]->synapses.begin(); it != layers[i]->synapses.end(); it++) {
                if( (*it)->IsMature()) mature++;
                else proto++;
            }
        }
        std::cout << "\tMature: " << mature << "  Proto: " << proto << std::endl;
    }


}