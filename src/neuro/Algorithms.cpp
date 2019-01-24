#include"Algorithms.hpp"

void RussoDurst_AssemblyDetection(vec<vec<double>> spike_trains,
                                vec<double> bin_sizes,
                                vec<double> max_lags,
                                double ref_lag=2.0,
                                double alph=0.05,
                                double No_th=0,
                                double O_th=dinf,
                                double bytelimit=iinf) {

    // Number of recorded units
    int nneu = spike_trains.size();
    vec<CellAssembly> assembly_bin;
    int Dc = 100;

    #pragma omp parallel for
    for(int gg = 0; gg < bin_sizes.size(); gg++) {

        double _int = bin_sizes[gg];
        double _max_lag = max_lags[gg];

        std::cout << gg << " - testing: bin size " << _int
                    << " max tested lag " << _max_lag << std::endl;

        vec<vec<double>> tb;
        for(int i = 0; i < spike_trains.size(); i++) {

            // Find min & max
            double min = std::numeric_limits<double>::max();
            double max = std::numeric_limits<double>::min();
            for(int k = 0; k < spike_trains[i].size(); k++) {
                if(spike_trains[i][k] < min) min = spike_trains[i][k];
                if(spike_trains[i][k] > max) max = spike_trains[i][k];
            }

            // ZH: My addition so the histcounts algorithm doesn't have
            // a test case for the final bin.
            max += 1.0;

            // Build matrix
            
            vec<double> tb_i;
            for(int k = min; k <= max; k+=_int) {
                tb_i.push_back(k);
            }
            tb.push_back(tb_i);
        }

        // Build binM
        // ZH: Bumped up to a 64 bits to standardize things.
        vec<vec<uint64_t>> binM;
        for(int i = 0; i < nneu; i++) {
            int num_bins = tb[i].size()-1;
            vec<uint64_t> b;
            for(int k = 0; k < num_bins; k++) {
                b.push_back(0);
            }
            binM.push_back(b);
        }

        // Bin the spikes.
        for(int i = 0; i < nneu; i++) {
            Histcounts(spike_trains[i], tb[i], binM[i]);
        }

        if(binM[0].size() - max_lags[gg] < 100) {
            std::cout << "Warning: testing bin size " << _int
                << "The time series is too short, consider "
                << "taking a longer portion of spike train or diminish "
                << "the bin size to be tested." << std::endl;
        } else {
            
        }

    }

}

void Histcounts(vec<double> spike_train, vec<double> bin_edges, vec<uint64_t> & counts) {
    for(int i = 0; i < spike_train.size(); i++) {
        for(int k = 1; k < bin_edges.size(); k++) {
            if(spike_train[i] < bin_edges[k]) {
                counts[k-1]++;
                break;
            }
        }
    }
}