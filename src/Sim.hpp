#ifndef SIM_HPP
#define SIM_HPP

#include<random>
#include<fstream>

#include"cereal/archives/binary.hpp"
#include"cereal/types/vector.hpp"
#include"cereal/types/memory.hpp"

#include"zxlb.hpp"
#include"Config.hpp"
#include"Layer.hpp"
#include"InputVector.hpp"
#include"ID.hpp"
#include"DataWriter.hpp"
#include"Options.hpp"
#include"DataSet.hpp"

class Sim {
public:
    Sim();
    void Build(int input_size);
    void Run(Options ops);

    void LoadNeuronTemplates();

    void CreateInputLayer(int size);
    void CreateInputVector(int size);
    void LinkInputs();  // Vector and Layer must have been created.

    sptr<Layer> CreateNewLayer(int size, vsptr<Layer> inputs);
    int GetNumberOfLayers();


    void Update(uint64_t time);
    void UpdateLayer(sptr<Layer> layer, uint64_t time);


    
    ///////////////////////////////////////////////////////////////////////////
    template<class Archive>
    void save(Archive & ar) const {
        ar(input_vector,all_layers,neuron_id);
    }

    template<class Archive>
    void load(Archive & ar) {
        ar(input_vector, all_layers,neuron_id);
        LoadNeuronTemplates();
    }
    ///////////////////////////////////////////////////////////////////////////

private:
    std::mt19937_64 rng;
    bool quit;
    sptr<InputVector> input_vector;
    vsptr<Layer> all_layers;
    uptr<NeuronTemplates> neuron_templates;
    uptr<ID> neuron_id;
    DataWriter writer;
    Options options;
    uptr<DataSet> dataset;
};

#endif