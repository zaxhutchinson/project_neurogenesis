#include<iostream>
#include<memory>

#include"zxlb.hpp"
#include"Config.hpp"
#include"Sim.hpp"
#include"Options.hpp"
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void PrintHelp();


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {

    vec<std::string> args(argv+1, argv+argc);
    Options options;
    options.recname = config::RECDIR+config::RECNAME;
    options.savename = config::MODDIR+config::SAVENAME;
    options.loadname = config::MODDIR+config::LOADNAME;
    
    for(int i = 0; i < args.size(); i++) {
        if(args[i]=="-r") {
            options.record=true;
        }
        else if(args[i]=="-t") {
            options.train=true;
        }
        else if(args[i]=="-s") {
            options.save=true;
        }
        else if(args[i]=="-l") {
            options.load=true;
        }
        else if(args[i]=="-i") {
            if(i+1 < args.size()) {
                options.input_size=std::stoi(args[++i]);
            }
        } else if(args[i]=="-h") {
            PrintHelp();
            return 0;
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

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void PrintHelp() {
    std::cout << "Project Neurogenesis Help\n\n";
    std::cout << "\t-r <filename> \n\t\tRecord model output\n\n";
    std::cout << "\t-t \n\t\ttrain the model\n\n";
    std::cout << "\t-s <filename> \n\t\t Save the model when done\n\n";
    std::cout << "\t-l <filename> \n\t\t Load the model <filename>\n\n";
    std::cout << "\t-i \n\t\t Designate input size\n\n";
}