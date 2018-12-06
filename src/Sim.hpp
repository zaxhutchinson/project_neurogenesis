#ifndef SIM_HPP
#define SIM_HPP

#include"spspdef.hpp"
#include"Layer.hpp"

class Sim {
public:
    Sim();
    void Build();
    void Run();


private:
    vsptr<Layer> layers;
};

#endif