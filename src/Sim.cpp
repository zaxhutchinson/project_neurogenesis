#include"Sim.hpp"

Sim::Sim() {
    std::random_device rd;
    rng = std::mt19937_64(rd());
    quit = false;
}

void Sim::LoadNeuronTemplates() {
    neuron_templates = std::make_unique<NeuronTemplates>();
    neuron_templates->LoadDefaultTemplates();
}

void Sim::Start(Options & ops) {
    LoadNeuronTemplates();

    if(ops.load) {
        model = Load(config::RECDIR+ops.loadname);
    } else {    
        Build(ops);
    }
}

void Sim::Build(Options & ops) {
    model = std::make_unique<Model>();
    model->name = ops.savename;
    model->neuron_id = std::make_unique<ID>();
    BuildInputLayer(model.get(), ops, neuron_templates.get());
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

            model->input_vector->ZeroInputs();

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
                model->input_vector->SetInput(data.positions[i],data.signals[i]);
            }
        }

        Update(time);

        time++;

        
    }

    // Stop recording if necessary
    if(options.record) writer.Stop();

    // Save the model if necessary
    if(options.save) Save(options.savename,model);
}

void Sim::Update(uint64_t time) {
    for(vsptr<Layer>::iterator it = model->layers.begin();
            it != model->layers.end(); it++) {
        UpdateLayer(*it, time);
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

    // Update child layers
    for(vsptr<Layer>::iterator it = layer->layers.begin();
            it != layer->layers.end(); it++) {
        UpdateLayer(*it, time);
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


void Sim::Save(std::string filename, sptr<Model> model) {
    std::cout << "SAVING TO: " << filename << std::endl;
    std::ofstream out(filename, std::ios::binary | std::ios::out);
    cereal::BinaryOutputArchive oarchive(out);
    oarchive(model);
}

sptr<Model> Sim::Load(std::string filename) {
    sptr<Model> model;
    std::cout << "LOADING FROM: " << filename << std::endl;
    std::ifstream in(filename, std::ios::binary | std::ios::in);
    cereal::BinaryInputArchive iarchive(in);
    iarchive(model);
    return model;
}