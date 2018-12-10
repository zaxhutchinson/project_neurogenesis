/*
Neuron.hpp
by Zachary Hutchinson

Implementation of the Inzhikevich neuron model with some added functionality.

*/
#ifndef NEURON_HPP
#define NEURON_HPP

#include<iostream>
#include<string>
#include<memory>
#include<functional>
#include<random>
#include<limits>
#include<list>

#include"cereal/archives/binary.hpp"
#include"cereal/types/vector.hpp"
#include"cereal/types/list.hpp"
#include"cereal/types/memory.hpp"

#include"NTemplate.hpp"
#include"Synapse.hpp"
#include"zxlb.hpp"

class Neuron {

public:
    Neuron();
    Neuron(sptr<NT> nt); // Ctor to use

    // Places a neuron object back into its original state.
    // Does nothing to associated synapse objects.
    void Reset();

    // Update state
    void Update(uint64_t time);
    void UpdateSpikes(bool new_spike);  // Called by Update
    void RegisterSpike(uint64_t time);  // Called by Update

    void SetAlphaBase(double alphabase);

    void AddInputSynapse(sptr<Synapse> synapse);
    void AddOutputSynapse(sptr<Synapse> synapse);

    // Sums synaptic input signals
    double Input(uint64_t time);

    // Sends current output to all output synapses
    void Output(uint64_t time);

    // Get current v, u, and output
    double V();
    double U();
    double GetCurrentOutput();

    void SetExternalInput(sptr<double> exin);

    ///////////////////////////////////////////////////////////////////////////
    template<class Archive>
    void save(Archive & ar) const {
        ar(cap,vr,vt,k,vpeak,a,b,c,d,baseline,external_input,
            alphabase, max_spike_age, i_syn, o_syn);
    }

    template<class Archive>
    void load(Archive & ar) {
        ar(cap,vr,vt,k,vpeak,a,b,c,d,baseline,external_input,
            alphabase, max_spike_age, i_syn, o_syn);
        current_output=0.0;
        v=c;
        u=d;
    }
    ///////////////////////////////////////////////////////////////////////////

private:
    double v;
    double u;
    double cap;
    double vr;
    double vt;
    double k;
    double vpeak;
    double a;
    double b;
    double c;
    double d;
    double baseline;
    sptr<double> external_input;

    double alphabase;

    std::list<int> spike_age_buffer;
    int max_spike_age;
    double current_output;

    lsptr<Synapse> i_syn;
    lsptr<Synapse> o_syn;
};

#endif