#include"Neuron.hpp"
#include"Synapse.hpp"


Neuron::Neuron() {
}

Neuron::Neuron(uint64_t id, sptr<NT> nt) {
    this->id = id;
    cap = nt->cap;
    vr = nt->vr;
    vt = nt->vt;
    k = nt->k;
    vpeak = nt->vpeak;
    a = nt->a;
    b = nt->b;
    c = nt->c;
    d = nt->d;
    baseline = nt->baseline;
    v = nt->c;
    u = nt->d;

    alphabase = 10.0;
    max_spike_age = alphabase*10;

    external_input = std::make_shared<double>(0.0);
}

void Neuron::Reset() {
    spike_age_buffer.clear();
}

bool Neuron::Update(uint64_t time) {
    v = v + (k * (v-vr) * (v-vt) - u +
        baseline + Input(time)) / cap;
    u = u + a * (b *(v-vr) - u);

    if(v >= vpeak) {
        v = c;
        u = u + d;
        UpdateSpikes(true);
        RegisterSpike(time);
        Output(time);
        return true;
    } 
    else {
        UpdateSpikes(false);
        Output(time);
        return false;
    }

    
}

void Neuron::UpdateSpikes(bool new_spike) {
    current_output = 0.0;

    if(new_spike) spike_age_buffer.push_back(0);

    for(std::list<int>::iterator it = spike_age_buffer.begin();
            it != spike_age_buffer.end(); ) {
        
        if((*it) > max_spike_age) {
            it = spike_age_buffer.erase(it);
        } else {
            current_output += ( (*it) / alphabase) * 
                std::exp( -( (*it) - alphabase) / alphabase);
            (*it)++;
            it++;
        }
    }
}

void Neuron::RegisterSpike(uint64_t time) {
    for(lsptr<Synapse>::iterator it = i_syn.begin();
            it != i_syn.end(); it++) {
        (*it)->RegisterNewPostSpike(time);
    }
    for(lsptr<Synapse>::iterator it = o_syn.begin();
            it != o_syn.end(); it++) {
        (*it)->RegisterNewPreSpike(time);
    }
}

void Neuron::Output(uint64_t time) {
    for(lsptr<Synapse>::iterator it = o_syn.begin();
            it != o_syn.end(); ) {
        if(!(*it)->GetActive()) {
            it = o_syn.erase(it);
        } else {
            (*it)->SetSignal(time, GetCurrentOutputNormalized());
            it++;
        }
    }
}

void Neuron::SetAlphaBase(double alphabase) {
    this->alphabase = alphabase;
    this->max_spike_age = alphabase*10.0;
}

void Neuron::AddInputSynapse(sptr<Synapse> synapse) {
    i_syn.push_back(synapse);
}
void Neuron::AddOutputSynapse(sptr<Synapse> synapse) {
    o_syn.push_back(synapse);
}   

double Neuron::Input(uint64_t time) {
    double input = *external_input;
    for(lsptr<Synapse>::iterator it = i_syn.begin(); it != i_syn.end(); ) {
        if(!(*it)->GetActive()) {
            it = i_syn.erase(it);
        } else {
            input += (*it)->GetSignal(time);
            it++;
        }
    }
    return input;
}

uint64_t Neuron::GetID() { return id; }
double Neuron::V() { return v; }
double Neuron::U() { return u; }
double Neuron::GetCurrentOutput() {
    return current_output;
}
double Neuron::GetCurrentOutputNormalized() {
    return current_output / (1.0+std::abs(current_output));
}

void Neuron::SetExternalInput(sptr<double> exin) {
    external_input = exin;
}
