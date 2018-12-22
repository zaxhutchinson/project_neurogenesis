#include<iostream>
#include<memory>

#include"zxlb.hpp"
#include"Config.hpp"
#include"Sim.hpp"
#include"Options.hpp"

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

    uptr<Sim> sim = std::make_unique<Sim>();

    sim->Start(options);
    sim->Build(options);
    sim->Run(options);

    return 0;
}

