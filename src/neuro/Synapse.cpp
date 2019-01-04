#include"Synapse.hpp"
#include"DTree.hpp"
/////////////////////////////////////////////////////////////////////////
// SYNAPSE INTERFACE DEFINITIONS
/////////////////////////////////////////////////////////////////////////
Synapse::Synapse() {
    
}

Synapse::Synapse(double _weight)
    : weight(_weight) {

}

Synapse::~Synapse() {
    
}

void Synapse::InitAsProto(sptr<DTree> dtree) {
    dendritic_tree = dtree;
    RegisterNewPreSpike = std::bind(&Synapse::proto_RegisterNewPreSpike, this, std::placeholders::_1);
    RegisterNewPostSpike = std::bind(&Synapse::proto_RegisterNewPostSpike, this, std::placeholders::_1);
}

void Synapse::InitAsNorm() {
    dendritic_tree = nullptr;
    RegisterNewPreSpike = std::bind(&Synapse::norm_RegisterNewPreSpike, this, std::placeholders::_1);
    RegisterNewPostSpike = std::bind(&Synapse::norm_RegisterNewPostSpike, this, std::placeholders::_1);
}

SynapseType Synapse::GetType() const { 
    return type;
}
void Synapse::SetType(SynapseType type) {
    this->type = type;
}
bool Synapse::GetActive() const {
    return active;
}
void Synapse::SetActive(bool active) {
    this->active = active;
}
double Synapse::GetSignal(uint64_t time, uint64_t delay) const {
    // Positive modulo
    // (delay+1) is to get time-1 when delay is 0, default.
    int index = ( (time-(delay+1))%signal_history_size+signal_history_size )
                % signal_history_size;
    return signal[index];

}
void Synapse::SetSignal(uint64_t time, double signal) {
    this->signal[time%signal_history_size] = signal *
            (weight*strength) /
            (std::abs(weight) + std::abs(strength));
}
void Synapse::proto_RegisterNewPreSpike(uint64_t time) {
    if(pre_spike_time) *pre_spike_time = time;
    else pre_spike_time = std::make_unique<uint64_t>(time);
    dendritic_tree->AddActivity(shared_from_this(),time);
}
void Synapse::proto_RegisterNewPostSpike(uint64_t time) {
    if(post_spike_time) *post_spike_time = time;
    else post_spike_time = std::make_unique<uint64_t>(time);
    if(pre_spike_time) {
        double diff_t = static_cast<double>(time-*pre_spike_time);
        if(diff_t<post_learn_window) {
            maturity++;
        }
    }
}
void Synapse::norm_RegisterNewPreSpike(uint64_t time) {
    if(pre_spike_time) *pre_spike_time = time;
    else pre_spike_time = std::make_unique<uint64_t>(time);

    if(post_spike_time) {
        double diff_t = static_cast<double>(time-*post_spike_time);
        if(diff_t<pre_learn_window) {
            strength += (pre_learn_rate * std::exp(-diff_t / pre_learn_window));
        }
    }
}

void Synapse::norm_RegisterNewPostSpike(uint64_t time) {
    if(post_spike_time) *post_spike_time = time;
    else post_spike_time = std::make_unique<uint64_t>(time);

    if(pre_spike_time) {
        double diff_t = static_cast<double>(time-*pre_spike_time);
        if(diff_t<post_learn_window) {
            strength += (post_learn_rate * std::exp(-diff_t / post_learn_rate));
        }
    }
}

double Synapse::GetWeight() const {
    return weight;
}

void Synapse::SetWeight(double weight) {
    this->weight = weight;
}

uint64_t Synapse::GetSignalHistorySize() const {
    return signal_history_size;
}

void Synapse::SetSignalHistorySize(uint64_t size) {
    signal_history_size = size;
    for(int i = 0; i < signal_history_size; i++) {
        signal.push_back(0.0);
    }
}

uint64_t * Synapse::GetPreSpikeTime() const {
    return pre_spike_time.get();
}

void Synapse::SetPreSpikeTime(uint64_t time) {
    *pre_spike_time = time;
}

void Synapse::ResetPreSpikeTime() {
    pre_spike_time = nullptr;
}

uint64_t * Synapse::GetPostSpikeTime() const {
    return post_spike_time.get();
}

void Synapse::SetPostSpikeTime(uint64_t time) {
    *post_spike_time = time;
}

void Synapse::ResetPostSpikeTime() {
    post_spike_time = nullptr;
}

double Synapse::GetStrength() const {
    return strength;
}

void Synapse::SetStrength(double strength) {
    this->strength = strength;
}

void Synapse::AddStrength(double delta_str) {
    strength += delta_str;
}

uint64_t Synapse::GetPostLearnWindow() const {
    return post_learn_window;
}

uint64_t Synapse::GetPreLearnWindow() const {
    return pre_learn_window;
}

void Synapse::SetPostLearnWindow(uint64_t window) {
    post_learn_window = window;
}

void Synapse::SetPreLearnWindow(uint64_t window) {
    pre_learn_window = window;
}

double Synapse::GetPostLearnRate() const {
    return post_learn_rate;
}

double Synapse::GetPreLearnRate() const {
    return pre_learn_rate;
}

void Synapse::SetPostLearnRate(double rate) {
    post_learn_rate = rate;
}

void Synapse::SetPreLearnRate(double rate) {
    pre_learn_rate = rate;
}

int Synapse::GetMaturity() {
    return maturity;
}

void Synapse::SetMaturity(int m) {
    maturity = m;
}

sptr<DTree> Synapse::GetDTree() {
    return dendritic_tree;
}

void Synapse::SetDTree(sptr<DTree> dtree) {
    dendritic_tree = dtree;
}