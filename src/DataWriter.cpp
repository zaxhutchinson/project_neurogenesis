#include"DataWriter.hpp"

SpikeData::SpikeData(uint64_t id, uint64_t t) {
    neuron_id=id;
    time=t;
}


DataWriter::DataWriter() {
    path = config::RECDIR;
    fname = config::RECNAME;
    run = false;
}
void DataWriter::AddData(SpikeData data) {
    qlock.lock();
    data_to_write.push(data);
    qlock.unlock();
}
void DataWriter::WriteThread() {
    std::ofstream of(path+fname, std::ios::binary|std::ios::out|std::ios::app);
    while(run) {
        while(!data_to_write.empty()) {
            qlock.lock();
            SpikeData d = data_to_write.front();
            data_to_write.pop();
            qlock.unlock();
            of.write(reinterpret_cast<char*>(&d.neuron_id), sizeof(uint64_t));
            of.write(reinterpret_cast<char*>(&d.time), sizeof(uint64_t));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
void ClearUp();