#ifndef MODEL_HPP
#define MODEL_HPP

#include<string>

#include"cereal/archives/binary.hpp"
#include"cereal/types/vector.hpp"
#include"cereal/types/memory.hpp"

#include"zxlb.hpp"
#include"ID.hpp"
#include"InputVector.hpp"
#include"Layer.hpp"

struct Model {
    std::string name;
    uptr<ID> layer_id;
    sptr<InputVector> input_vector;
    vsptr<Layer> layers;

    void PrintModelDetails();

    ///////////////////////////////////////////////////////////////////////////
    template<class Archive>
    void save(Archive & ar) const {
        ar(name,input_vector,layers,layer_id);
    }

    template<class Archive>
    void load(Archive & ar) {
        ar(name,input_vector,layers,layer_id);
    }
    ///////////////////////////////////////////////////////////////////////////
};

#endif