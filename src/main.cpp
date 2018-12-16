#include<iostream>
#include<memory>

#include"cereal/cereal.hpp"
#include"cereal/archives/binary.hpp"
#include"cereal/types/memory.hpp"

#include"zxlb.hpp"
#include"Config.hpp"
#include"Sim.hpp"
#include"Options.hpp"


void Save(std::string filename, sptr<Sim> sim);
sptr<Sim> Load(std::string filename);

int main(int argc, char** argv) {

    vec<std::string> args(argv+1, argv+argc);
    Options options;
    for(int i = 0; i < args.size(); i++) {
        if(args[i]=="-r") {
            options.record=true;
            options.recname=args[++i];
        }
        else if(args[i]=="-t") {
            options.train=true;
        }
        else if(args[i]=="-s") {
            if(i+1 < args.size()) {
                options.savename=args[++i];
                options.save=true;
            }
        }
        else if(args[i]=="-l") {
            if(i+1 < args.size()) {
                options.loadname=args[++i];
                options.load=true;
            }
        }
        else if(args[i]=="-i") {
            if(i+1 < args.size()) {
                options.input_size=std::stoi(args[++i]);
            }
        }
    }

    config::LoadConfig("config/config.ini");
    config::PrintConfig();

    sptr<Sim> sim = nullptr;
    if(options.load) {
        sim = Load(config::RECDIR+options.loadname);
    } else {
        sim = std::make_shared<Sim>();
        sim->Build(options.input_size);
    }

    
    sim->Run(options);
    

    if(options.save) {
        Save(config::RECDIR+options.savename, sim);
    }


    return 0;
}

void Save(std::string filename, sptr<Sim> sim) {
    std::cout << "SAVING TO: " << filename << std::endl;
    std::ofstream out(filename, std::ios::binary | std::ios::out);
    cereal::BinaryOutputArchive oarchive(out);
    oarchive(sim);
}

sptr<Sim> Load(std::string filename) {
    sptr<Sim> sim;
    std::cout << "LOADING FROM: " << filename << std::endl;
    std::ifstream in(filename, std::ios::binary | std::ios::in);
    cereal::BinaryInputArchive iarchive(in);
    iarchive(sim);
    return sim;
}