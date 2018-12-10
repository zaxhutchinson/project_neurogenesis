#include<iostream>

#include"zxlb.hpp"
#include"Config.hpp"
#include"Sim.hpp"

int main(int argc, char** argv) {

    vec<std::string> args(argv+1, argv+argc);

    config::LoadConfig("config/config.ini");
    config::PrintConfig();

    Sim sim;
    sim.Build(100);

    return 0;
}