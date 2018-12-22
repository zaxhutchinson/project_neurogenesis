#ifndef MODEL_BUILDER_HPP
#define MODEL_BUILDER_HPP

#include"zxlb.hpp"
#include"Options.hpp"
#include"Model.hpp"
#include"Neuron.hpp"
#include"Synapse.hpp"
#include"Layer.hpp"

void BuildInputLayer(Model * model, Options & ops, NeuronTemplates * nt);



#endif