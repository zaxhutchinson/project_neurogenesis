/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Config.cpp
 * Author: zax
 *
 * Created on August 16, 2017, 8:01 AM
 */

#include "Config.hpp"

namespace config {
    //////////////////////////////////////////////////////////////////////////
    // GENERAL
    long GLOBAL_SEED;
    int SPIKES_TO_MATURITY;

    //////////////////////////////////////////////////////////////////////////
    // SYNAPSE
}

bool config::LoadConfig(std::string filename) {

    INIReader reader(filename);

    if(reader.ParseError() < 0) {
        std::cerr << "Cannot load " << filename << std::endl;
        return false;
    }
    //////////////////////////////////////////////////////////////////////////
    // GENERAL
    GLOBAL_SEED = reader.GetInteger("general","global_seed",-1);

    //////////////////////////////////////////////////////////////////////////
    // SYNAPSE
    SPIKES_TO_MATURITY = 100;

    return true;
}

void config::PrintConfig() {
    std::cout << "======================================================\n";
    std::cout << "                 CONFIG DATA\n";
    std::cout << "======================================================\n";

    std::cout << "\n*** GENERAL ***\n"
            << "GLOBAL SEED: " << GLOBAL_SEED 
            << std::endl;

    std::cout << "\n*** MAP ***\n"
            << "SPIKES_TO_MATURITY: " << SPIKES_TO_MATURITY
            << std::endl;



    std::cout << "======================================================\n\n";

}
