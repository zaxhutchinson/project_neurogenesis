/*
Synapse.cpp
Zachary Hutchinson

Provides a series of Synapse classes to model different types of 
connections.

Synapse class itself is an interface following the NVI pattern. Its
client is the Neuron class, or, said another way, the interface's 
functionality provides the necessary information to the Neuron class.
*/

#ifndef SYNAPSE_HPP
#define SYNAPSE_HPP

#include<cmath>
#include<functional>

#include"cereal/archives/binary.hpp"
#include"cereal/types/vector.hpp"
#include"cereal/types/memory.hpp"

#include"zxlb.hpp"

////////////////////////////////////////////////////////////////////
// ENUM
////////////////////////////////////////////////////////////////////

enum class SynapseType {
    SIMPLE,
    PROTO,
    STDP,
};

////////////////////////////////////////////////////////////////////
// INTERFACE
////////////////////////////////////////////////////////////////////
class DTree;
class Synapse : public std::enable_shared_from_this<Synapse> {
public:
    Synapse();
    virtual ~Synapse();
    Synapse(Synapse const &) = delete;
    Synapse & operator=(Synapse const &) = delete;

    void InitAsProto(sptr<DTree> dtree);
    void InitAsNorm();

    SynapseType GetType() const;
    void SetType(SynapseType type);
    bool GetActive() const;
    void SetActive(bool active);
    double GetSignal(uint64_t time, uint64_t delay=0) const;
    void SetSignal(uint64_t time, double signal);
    void proto_RegisterNewPreSpike(uint64_t time);
    void proto_RegisterNewPostSpike(uint64_t time);
    void norm_RegisterNewPreSpike(uint64_t time);
    void norm_RegisterNewPostSpike(uint64_t time);

    double GetWeight() const;
    void SetWeight(double weight);
    uint64_t GetTime() const;
    void SetTime(uint64_t time);
    uint64_t GetSignalHistorySize() const;
    void SetSignalHistorySize(uint64_t size);
    uint64_t * GetPreSpikeTime() const;
    void SetPreSpikeTime(uint64_t time);
    void ResetPreSpikeTime();
    uint64_t * GetPostSpikeTime() const;
    void SetPostSpikeTime(uint64_t time);
    void ResetPostSpikeTime();

    double GetStrength() const;
    void SetStrength(double strength);
    void AddStrength(double delta_str);
    uint64_t GetPostLearnWindow() const;
    void SetPostLearnWindow(uint64_t window);
    uint64_t GetPreLearnWindow() const;
    void SetPreLearnWindow(uint64_t window);
    double GetPostLearnRate() const;
    void SetPostLearnRate(double rate);
    double GetPreLearnRate() const;
    void SetPreLearnRate(double rate);

    int GetMaturity();
    void SetMaturity(int m);

    sptr<DTree> GetDTree();
    void SetDTree(sptr<DTree> dtree);

    std::function<void(uint64_t)> RegisterNewPreSpike;
    std::function<void(uint64_t)> RegisterNewPostSpike;

    ///////////////////////////////////////////////////////////////////////////
    template<class Archive>
    void save(Archive & ar) const {
        ar(type, active, weight, signal_history_size,
            strength, post_learn_window, pre_learn_window,
            post_learn_rate, pre_learn_rate,
            dendritic_tree, maturity);
    }

    template<class Archive>
    void load(Archive & ar) {
        ar(type, active, weight, signal_history_size,
            strength, post_learn_window, pre_learn_window,
            post_learn_rate, pre_learn_rate,
            dendritic_tree, maturity);

        for(int i = 0; i < signal_history_size; i++) {
            signal.push_back(0.0);
        }
        pre_spike_time=nullptr;
        post_spike_time=nullptr;
    }
    ///////////////////////////////////////////////////////////////////////////

private:
    SynapseType type;
    bool active;
    double weight;
    uint64_t signal_history_size;
    vec<double> signal;
    uptr<uint64_t> pre_spike_time;
    uptr<uint64_t> post_spike_time;
    double strength;
    uint64_t post_learn_window;
    uint64_t pre_learn_window;
    double post_learn_rate;
    double pre_learn_rate;
    sptr<DTree> dendritic_tree;
    int maturity;

};



#endif