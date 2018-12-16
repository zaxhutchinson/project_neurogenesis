#include"Sim.hpp"

Sim::Sim() {
    std::random_device rd;
    rng = std::mt19937_64(rd());
    quit = false;
    neuron_id=std::make_unique<ID>();
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

void Sim::Run(Options ops) {
    // Copy the options
    options=ops;

    // Generate the input dataset.
    dataset = GenerateDataSet(rng, options.dataset_id);

    // Set time and timing stuff
    uint64_t time = 0;
    int ds_counter = 0;
    uint64_t next_dataset_start=time;
    uint64_t next_dataset_stop=time+options.stimulus_duration;

    // Start recording if necessary.
    if(options.record) writer.Start(options.recname);

    while(!quit) {

        if(time==next_dataset_stop) {
            std::cout << "STOPPING DS: " << ds_counter << std::endl;
            input_vector->ZeroInputs();
            if(ds_counter<dataset->Size()) {
                ds_counter++;
                next_dataset_start=time+options.between_duration;
                next_dataset_stop=next_dataset_start+options.stimulus_duration;
            }
            else {
                quit=true;
                continue;
            }
        }

        if(time==next_dataset_start) {
            std::cout << "STARTING DS: " << ds_counter << std::endl;
            Data& data = dataset->GetData(ds_counter);
            for(int i = 0; i < data.positions.size(); i++) {
                input_vector->SetInput(data.positions[i],data.signals[i]);
            }
        }

        Update(time);

        time++;

        
    }

    // Stop recording if necessary
    if(options.record) writer.Stop();
}

void Sim::CreateInputLayer(int size) {
    sptr<Layer> input_layer = std::make_shared<Layer>();
    input_layer->BuildInput(neuron_templates.get(), neuron_id.get(), size);
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

int Sim::GetNumberOfLayers() {
    return all_layers.size();
}

void Sim::Update(uint64_t time) {
    for(int i = 0; i < all_layers.size(); i++) {
        UpdateLayer(all_layers[i], time);
    }    
}
void Sim::UpdateLayer(sptr<Layer> layer, uint64_t time) {
    for(vsptr<Neuron>::iterator it = layer->neurons.begin();
            it != layer->neurons.end(); it++) {
        if((*it)->Update(time)) {
            writer.AddData(SpikeData((*it)->GetID(), time));
        }
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
