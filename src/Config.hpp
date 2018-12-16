/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Config.hpp
 * Author: zax
 *
 * Created on August 16, 2017, 8:01 AM
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include<string>
#include<iostream>
#include<memory>
#include<random>

#include"INIReader.h"

namespace config {
    //////////////////////////////////////////////////////////////////////////
    // GENERAL
    extern long GLOBAL_SEED;
    
    //////////////////////////////////////////////////////////////////////////
    // SYNAPSE
    extern int SPIKES_TO_MATURITY;

    //////////////////////////////////////////////////////////////////////////
    // SERIALIZATION
    extern std::string RECDIR;
    extern std::string RECNAME;

    //////////////////////////////////////////////////////////////////////////
    // FUNCTIONS
    bool LoadConfig(std::string filename);
    void PrintConfig();

};

#endif /* CONFIG_HPP */
