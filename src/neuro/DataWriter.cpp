#include"DataWriter.hpp"
SpikeData::SpikeData() {
    layer_id=0;
    neuron_id=0;
    time=0;
}
SpikeData::SpikeData(uint64_t _layer_id, uint64_t _neuron_id, uint64_t t) {
    neuron_id=_neuron_id;
    layer_id=_layer_id;
    time=t;
}
SpikeData::SpikeData(const SpikeData & other) {
    neuron_id = other.neuron_id;
    layer_id = other.layer_id;
    time = other.time;
}
SpikeData& SpikeData::operator=(const SpikeData & rhs) {
    if(this != &rhs) {
        layer_id = rhs.layer_id;
        neuron_id = rhs.neuron_id;
        time = rhs.time;
    }
    return *this;
}

DataWriter::DataWriter() {
    run = false;
}
void DataWriter::AddData(SpikeData data) {
    qlock.lock();
    data_to_write.push(data);
    qlock.unlock();
}
void DataWriter::WriteThread() {
    std::cout << "WRITING DATA TO: " << fname << std::endl;
    std::ofstream of(fname, std::ios::binary|std::ios::out|std::ios::app);
    while(run || !data_to_write.empty()) {
        while(!data_to_write.empty()) {
            qlock.lock();
            SpikeData d = data_to_write.front();
            data_to_write.pop();
            qlock.unlock();
            of.write(reinterpret_cast<char*>(&d.layer_id), sizeof(uint64_t));
            of.write(reinterpret_cast<char*>(&d.neuron_id), sizeof(uint64_t));
            of.write(reinterpret_cast<char*>(&d.time), sizeof(uint64_t));
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    of.close();
}

void DataWriter::Start(std::string savename) {
    fname = savename;
    run=true;
    while(t_write.joinable()) ;
    t_write = std::thread(&DataWriter::WriteThread, this);
}
void DataWriter::Stop() {
    run=false;
    if(t_write.joinable()) {
        t_write.join();
    }
}