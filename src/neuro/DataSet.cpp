#include"DataSet.hpp"


void DataSet::AddData(Data data) {
    data_set.push_back(data);
}
Data & DataSet::GetData(int i) {
    return data_set[i];
}
int DataSet::Size() {
    return data_set.size();
}
///////////////////////////////////////////////////////////////////////////////

uptr<DataSet> GenerateDataSet(std::mt19937_64 & rng, vec<int> ds_ids) {
    uptr<DataSet> ds = std::make_unique<DataSet>();
    for(int i = 0; i < ds_ids.size(); i++) {
        switch(ds_ids[i]) {
            case 0:
                GenerateDataSet0(rng, ds.get()); break;
        }
    }
    return std::move(ds);
}

void GenerateDataSet0(std::mt19937_64 & rng, DataSet * ds) {
    
    
    for(int i = 0; i < 10; i++) {
        Data data;
        for(int j= 0; j < 10; j++) {
            data.positions.push_back(i+10*j);
            data.signals.push_back(100.0);
        }
        ds->AddData(data);
    }
}