#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "DatasetAR.h"
#include "DatasetARX.h"
#include "GaussSeq.h"
#include "ARSeq.h"
#include "ARPoly.h"
#include "utils.h"
using utils::my_float;
using boost::multiprecision::cpp_bin_float_50;
using boost::random::uniform_real_distribution;


int main() {
    boost::random::mt19937 gen {};
    uniform_real_distribution<my_float> u(-1, 1);

    // prepare 
    std::map<int, my_float> coeff {
        {3, 0.2},
        {20, 0.5},
    };
    std::map<int, my_float> coeff_2 {
        {3, 0.75},
        {20, -0.9},
    };
    std::vector<my_float> v_seed(20);

    // Stationary AR process
    for (auto type = 0; type < 5; type++) {
        for (auto samp = 0; samp < utils::N_SAMPLE; samp++) {
            // Seed differently
            for (auto i = 0; i < 20; i++) {
                v_seed[i] = u(gen);
            }
            ARSeq targ_seq(coeff, u(gen));
            targ_seq.seed_prev_vals(v_seed);

            DatasetAR dat("./ARStat/ARStat-" + std::to_string(type) + 
                "/Sample-" + std::to_string(samp), targ_seq, type);
            dat.write_csv();
        }
    }

    // Non-stationary AR process
    for (auto type = 0; type < 5; type++) {
        for (auto samp = 0; samp < utils::N_SAMPLE; samp++) {
            // Seed differently
            for (auto i = 0; i < 20; i++) {
                v_seed[i] = u(gen);
            }
            ARSeq targ_seq(coeff_2, u(gen));
            targ_seq.seed_prev_vals(v_seed);

            DatasetAR dat("./ARNStat/ARNStat-" + std::to_string(type) + 
                "/Sample-" + std::to_string(samp), targ_seq, type);
            dat.write_csv();
        }
    }

    // Non-stationary ARX process
    for (auto type = 1; type < 5; type++) {
        for (auto samp = 0; samp < utils::N_SAMPLE; samp++) {
            DatasetARX dat("./ARXNStat/ARXNStat-" + std::to_string(type) + 
                "/Sample-" + std::to_string(samp), type);
            dat.write_csv();
        }
    }
    return 0;
}
