#ifndef SIM_HPP
#define SIM_HPP

#include<random>
#include<fstream>

#include"cereal/cereal.hpp"
#include"cereal/archives/binary.hpp"
#include"cereal/types/vector.hpp"
#include"cereal/types/memory.hpp"

#include"zxlb.hpp"
#include"Config.hpp"
#include"Model.hpp"
#include"DataWriter.hpp"
#include"Options.hpp"
#include"DataSet.hpp"
#include"ModelBuilder.hpp"

class Sim {
public:
    Sim();
    void Start(Options & ops);
    void Build(Options & ops);
    void Run(Options ops);

    void LoadNeuronTemplates();

    void Update(uint64_t time);
    void UpdateLayer(sptr<Layer> layer, uint64_t time);

    void Save(std::string filename, sptr<Model> model);
    sptr<Model> Load(std::string filename);   

private:
    RNG rng;
    bool quit;
    uptr<NeuronTemplates> neuron_templates;
    DataWriter writer;
    Options options;
    uptr<DataSet> dataset;
    sptr<Model> model;
};

#endif