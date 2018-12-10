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

class Sim {
public:
    Sim();
    void Build(int input_size);
    void Run();

    void LoadNeuronTemplates();

    void CreateInputLayer(int size);
    void CreateInputVector(int size);
    void LinkInputs();  // Vector and Layer must have been created.

    sptr<Layer> CreateNewLayer(int size, vsptr<Layer> inputs);


    void Update(uint64_t time);
    void UpdateLayer(sptr<Layer> layer, uint64_t time);


    void Save(std::string filename);
    void Load(std::string filename);
    ///////////////////////////////////////////////////////////////////////////
    template<class Archive>
    void save(Archive & ar) const {
        ar(input_vector, all_layers);
    }

    template<class Archive>
    void load(Archive & ar) {
        ar(input_vector, all_layers);
        LoadNeuronTemplates();
    }
    ///////////////////////////////////////////////////////////////////////////

private:
    std::mt19937_64 rng;
    bool quit;
    sptr<InputVector> input_vector;
    vsptr<Layer> all_layers;
    uptr<NeuronTemplates> neuron_templates;
};

#endif