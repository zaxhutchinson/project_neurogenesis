#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include<string>

struct Options {
    bool record=false;
    std::string recname="pc_rec";
    bool load=false;
    std::string savename="pn_save";
    bool save=false;
    std::string loadname="pn_save";
    bool train=false;
    int build_id=0;
    int input_size=100;
    uint64_t stimulus_duration=1000;
    uint64_t between_duration=1000;
    vec<int> dataset_id={0};
};

#endif