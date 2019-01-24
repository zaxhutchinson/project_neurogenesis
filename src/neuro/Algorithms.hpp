#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include<iostream>
#include<cstdint>
#include<limits>
#include<omp.h>
#include<algorithm>
#include<memory>

#include"zxlb.hpp"
///////////////////////////////////////////////////////////////////////////////
// Constants
const double dinf = std::numeric_limits<double>::infinity();
const uint64_t iinf = std::numeric_limits<uint64_t>::infinity();
///////////////////////////////////////////////////////////////////////////////
// Cell Assembly Struct
struct CellAssembly {
    int elements;
    vec<double> lag;
    vec<double> pr;
    vec<uint16_t> time;
    uint64_t noccurrences;
};

/* Russo-Durstewitz Algorithm for Cell Assembly Detection
    
    Russo, E., & Durstewitz, D. (2017). Cell assemblies at multiple time 
    scales with arbitrary lag constellations. eLife, 6, e19428. 
    doi:10.7554/eLife.19428

    Translated into C++ from matlab source found here:
        https://www.zi-mannheim.de/fileadmin/user_upload/redakteure/
        computationale_neurowissenschaften/Cell_assembly_detection_02.zip
*/
void RussoDurst_AssemblyDetection(vec<vec<double>> spike_trains,
                                vec<double> bin_sizes,
                                vec<double> max_lags,
                                double ref_lag=2.0,
                                double alph=0.05,
                                double No_th=0,
                                double O_th=dinf,
                                double bytelimit=iinf);


/* Histcounts by zax
    Returns the number of spikes in each bin (counts).
    If called from RussoDurst algorithm, the last element in the bin_edges vec
    is the right hand edge of the last bin, however, the algorithm creates this according
    to the max of the spike_train we're passing in, so the max is irrelevant as
    there's nothing right of it. I assume this was done in the original because matlab
    requires according to their docs that the last value be the right edge of the last bin.
*/
void Histcounts(vec<double> spike_train, vec<double> bin_edges, vec<uint64_t> & counts);

template<typename T>
void TransposeMatrix(vec<vec<T>> & maxtrix_in, vec<vec<T>> & maxtrix_out) {

}

#endif