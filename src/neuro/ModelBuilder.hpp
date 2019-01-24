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


/* Numbers
    <model name> <neurons> <dtrees_per_neuron> <syn_per_dtree>
*/

/* Model A_0
    Input layer: 100
    Layer 1: 400, 3, 5 
*/
void BuildModel_A_0(Model * model, Options * options, NeuronTemplates * nt, RNG * rng);

/* Model A_1
    Input Layer: 100
    Layer 1: 400, 3, 5
    Layer 2: 100, 5, 10
*/
void BuildModel_A_1(Model * model, Options * options, NeuronTemplates * nt, RNG * rng);

#endif