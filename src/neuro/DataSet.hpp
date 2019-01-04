#ifndef DATASET_HPP
#define DATASET_HPP



#include<random>

#include"zxlb.hpp"

struct Data {
    vec<int> positions;
    vec<double> signals;
};

struct DataSet {
    vec<Data> data_set;

    void AddData(Data data);
    Data & GetData(int i);
    int Size();
};

uptr<DataSet> GenerateDataSet(std::mt19937_64 & rng, vec<int> ds_ids);

/* Data Set 0
    Every 10th - Data looks like
    - 0 10 20 ... 90
    - 1 11 21 ... 91
    - ...
    - 9 19 29 ... 99
*/
void GenerateDataSet0(std::mt19937_64 & rng, DataSet * ds);

#endif