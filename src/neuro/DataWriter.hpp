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
    SpikeData();
    SpikeData(uint64_t _layer_id, uint64_t _neuron_id, uint64_t t);
    SpikeData(const SpikeData & other);
    SpikeData& operator=(const SpikeData & rhs);
    uint64_t time;
    uint64_t neuron_id;
    uint64_t layer_id;
};

class DataWriter {
public:
    DataWriter();

    void WriteModelMetadata(vec<uint64_t> & layer_sizes);

    void AddData(SpikeData data);
    void WriteThread();

    void Start(std::string savename, vec<uint64_t> & layer_sizes);
    void Stop();
private:
    std::string fname;
    bool run;
    std::queue<SpikeData> data_to_write;
    std::mutex qlock;
    std::thread t_write;
};
#endif