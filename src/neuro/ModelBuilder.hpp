#ifndef MODEL_BUILDER_HPP
#define MODEL_BUILDER_HPP

#include<algorithm>

#include"zxlb.hpp"
#include"Options.hpp"
#include"Model.hpp"
#include"Neuron.hpp"
#include"Synapse.hpp"
#include"Layer.hpp"

void BuildInputLayer(Model * model, Options * ops, NeuronTemplates * nt);

/* Build Layer From Template 
    Creates a new layer using provided LayerTemplate
*/
void BuildLayerFromTemplate(Model * model, NeuronTemplates * nt, LayerTemplate * lt, RNG * rng);



void BuildModel_A_0(Model * model, Options * options, NeuronTemplates * nt, RNG * rng);

#endif