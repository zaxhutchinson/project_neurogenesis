#ifndef ID_HPP
#define ID_HPP

#include"cereal/archives/binary.hpp"

#include"zxlb.hpp"

class ID {
public:
    ID();
    uint64_t GetNewID();
    ///////////////////////////////////////////////////////////////////////////
    template<class Archive>
    void save(Archive & ar) const {
        ar(id);
    }

    template<class Archive>
    void load(Archive & ar) {
        ar(id);
    }
    ///////////////////////////////////////////////////////////////////////////
private:
    uint64_t id;
};

#endif