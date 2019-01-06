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

    config::LoadConfig("config/config.ini");
    config::PrintConfig();

    vec<std::string> args(argv+1, argv+argc);
    Options options;
    options.recname = config::RECDIR+config::RECNAME;
    options.savename = config::MODDIR+config::SAVENAME;
    options.loadname = config::MODDIR+config::LOADNAME;
    
    for(int i = 0; i < args.size(); i++) {
        if(args[i]=="-r") {
            options.record=true;
            if(i+1 < args.size() && args[i+1][0]!='-') {
                options.recname=config::RECDIR+args[++i];
            }
        }
        else if(args[i]=="-t") {
            options.train=true;
        }
        else if(args[i]=="-s") {
            options.save=true;
            if(i+1 < args.size() && args[i+1][0]!='-') {
                options.savename=config::MODDIR+args[++i];
            }
        }
        else if(args[i]=="-l") {
            options.load=true;
            if(i+1 < args.size() && args[i+1][0]!='-') {
                options.loadname=config::MODDIR+args[++i];
            }
        }
        else if(args[i]=="-b") {
            if(i+2 < args.size()) {
                options.build_id=std::stoi(args[++i]);
                options.input_size=std::stoi(args[++i]);
            } else {
                std::cout << "Invalid arguments for option -b\n"
                        << "\t-b [build id] [input size]\n";
            }
        } else if(args[i]=="-h") {
            PrintHelp();
            return 0;
        } else if(args[i]=="-d") {
            if(i+1 < args.size()) {
                std::string arg(args[++i]);
                if(arg[0]=='[') {
                    if(arg[arg.size()-1]==']') {
                        arg = arg.substr(1,arg.size()-1);
                        int dset = std::stoi(arg);
                        options.dataset_id.push_back(dset);
                    }
                    else {
                        arg = arg.substr(1);

                        int dset = std::stoi(arg);
                        options.dataset_id.push_back(dset);

                        arg = std::string(args[++i]);
                        while( arg[arg.size()-1] != ']') {
                            if(arg[0]=='-') {
                                std::cout << "Dataset list not closed with ']'.\n";
                                return 1;
                            }

                            dset = std::stoi(arg);
                            options.dataset_id.push_back(dset);
                            arg = std::string(args[++i]);
                        }
                        arg = arg.substr(0,arg.size()-1);
                        dset = std::stoi(arg);
                        options.dataset_id.push_back(dset);
                    }

                } else {
                    std::cout << "Dataset list must be contained in []\n";
                    return 1;
                }

            } else {
                std::cout << "Missing dataset list argument.\n";
                return 1;
            }
        }
    }

    

    uptr<Sim> sim = std::make_unique<Sim>();

    sim->Init(options);
    sim->Build();
    sim->Run();

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void PrintHelp() {
    std::cout << "Project Neurogenesis Help\n\n";
    std::cout << "\t-r <filename> \n\t\tRecord model output\n\n";
    std::cout << "\t-t \n\t\ttrain the model\n\n";
    std::cout << "\t-s <filename> \n\t\tSave the model when done\n\n";
    std::cout << "\t-l <filename> \n\t\tLoad the model <filename>\n\n";
    std::cout << "\t-b <model id> <input size>\n\t\t Designate input size. -l overrides -b.\n\n";
}