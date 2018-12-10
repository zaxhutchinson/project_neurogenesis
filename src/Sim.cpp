#include"Sim.hpp"

Sim::Sim() {
    std::random_device rd;
    rng = std::mt19937_64(rd());
    quit = false;
}

void Sim::Build(int input_size) {
    LoadNeuronTemplates();
    CreateInputLayer(input_size);
    CreateInputVector(input_size);
    LinkInputs();
}

void Sim::LoadNeuronTemplates() {
    neuron_templates = std::make_unique<NeuronTemplates>();
    neuron_templates->LoadDefaultTemplates();
}

void Sim::Run() {
    uint64_t time = 0;
    while(!quit) {

        for(vsptr<Layer>::iterator it = all_layers.begin(); it != all_layers.end(); it++) {
            UpdateLayer(*it,time);
        }

        time++;
    }
}

void Sim::CreateInputLayer(int size) {
    sptr<Layer> input_layer = std::make_shared<Layer>();
    input_layer->BuildInput(neuron_templates.get(), size);
    all_layers.push_back(input_layer);

}
void Sim::CreateInputVector(int size) {
    input_vector = std::make_shared<InputVector>(size);
}

void Sim::LinkInputs() {
    vsptr<double> & inputs = input_vector->GetInputs();
    vsptr<Neuron> & neurons = all_layers[0]->GetNeurons();

    if(inputs.size() != neurons.size()) {
        return;
    } else {
        for(int i = 0; i < inputs.size(); i++) {
            neurons[i]->SetExternalInput(inputs[i]);
        }
    }
}



sptr<Layer> Sim::CreateNewLayer(int size, vsptr<Layer> inputs) {

}

void Sim::Update(uint64_t time) {
    
}
void Sim::UpdateLayer(sptr<Layer> layer, uint64_t time) {
    for(vsptr<Neuron>::iterator it = layer->neurons.begin();
            it != layer->neurons.end(); it++) {
        (*it)->Update(time);
    }

    for(lsptr<Synapse>::iterator it = layer->synapses.begin();
            it != layer->synapses.end(); ) {
        if( (*it)->GetMaturity() > config::SPIKES_TO_MATURITY) {
            (*it)->InitAsNorm();
            it = layer->synapses.erase(it);
        } else {
            it++;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Sim::Save(std::string filename) {
    std::ofstream out(filename, std::ios::binary | std::ios::out);
    cereal::BinaryOutputArchive oarchive(out);
    oarchive(*this);
}

void Sim::Load(std::string filename) {
    std::ifstream in(filename, std::ios::binary | std::ios::in);
    cereal::BinaryInputArchive iarchive(in);
    iarchive(*this);
}