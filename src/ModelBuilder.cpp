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