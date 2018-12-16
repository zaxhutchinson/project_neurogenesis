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

/* Words and encoding:

    A B C D E F G H I J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
    0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

    THING:
    19 7 8 13 6

    PROJECT:
    15 17 14 9 4 2 19

    BRAIN:
    1 17 0 8 13

    DEBUG:
    3 4 1 20 6

    WORLD:
    22 14 17 11 3

    WORLDWIDE:
    22 14 17 11 3 22 8 3 4

    QUEEN:
    16 20 4 4 13

    QUIET:
    16 20 8 4 19

*/

uptr<DataSet> GenerateDataSet(std::mt19937_64 & rng, vec<int> ds_ids);
void GenerateDataSet0(std::mt19937_64 & rng, DataSet * ds);

#endif