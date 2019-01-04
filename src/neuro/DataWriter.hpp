#ifndef DATA_WRITER_HPP
#define DATA_WRITER_HPP

#include<string>
#include<mutex>
#include<thread>
#include<fstream>
#include<iomanip>
#include<cstdint>
#include<queue>

#include"zxlb.hpp"
#include"Config.hpp"

struct SpikeData {
    SpikeData(uint64_t id, uint64_t t);
    uint64_t time;
    uint64_t neuron_id;
};

class DataWriter {
public:
    DataWriter();
    void AddData(SpikeData data);
    void WriteThread();

    void Start(std::string savename);
    void Stop();
    //void ClearUp();
private:
    std::string path;
    std::string fname;
    bool run;
    std::queue<SpikeData> data_to_write;
    std::mutex qlock;
    std::thread t_write;
};
#endif