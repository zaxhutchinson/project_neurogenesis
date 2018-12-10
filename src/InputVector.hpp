#ifndef INPUT_VECTOR_HPP
#define INPUT_VECTOR_HPP

#include"cereal/archives/binary.hpp"
#include"cereal/types/vector.hpp"
#include"cereal/types/memory.hpp"

#include"zxlb.hpp"

class InputVector {

public:
    InputVector();
    InputVector(int size);

    void SetInputs(vec<double> & values);
    void ZeroInputs();

    vsptr<double> & GetInputs();

    ///////////////////////////////////////////////////////////////////////////
    template<class Archive>
    void save(Archive & ar) const {
        ar(inputs);
    }

    template<class Archive>
    void load(Archive & ar) {
        ar(inputs);
    }
    ///////////////////////////////////////////////////////////////////////////

private:
    vsptr<double> inputs;
};

#endif