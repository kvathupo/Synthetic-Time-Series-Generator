#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "DatasetAR.h"
#include "DatasetPoly.h"
#include "GaussSeq.h"
#include "ARSeq.h"
#include "ARPoly.h"
#include "utils.h"
using utils::my_float;
using boost::multiprecision::cpp_bin_float_50;
using boost::random::uniform_real_distribution;


int main() {
    boost::random::mt19937 gen {};
    uniform_real_distribution<my_float> u(0.001, 1);

    // prepare 
    std::map<int, my_float> coeff_3 {
        {1, 0.4},
        {3, -20},
    };
    std::map<int, my_float> pow_3 {
        {1, 3},
        {3, 2},
    };
    std::map<int, my_float> coeff_4 {
        {1, 0.4},
        {3, 0.1},
    };
    std::map<int, my_float> pow_4 {
        {1, 7},
        {3, 0.5},
    };
    std::vector<my_float> v_seed_three(3);

    // Non-stationary, non-linear AR process 1
    for (auto type = 0; type < 5; type++) {
        for (auto samp = 0; samp < utils::N_SAMPLE; samp++) {
            // Seed differently
            for (auto i = 0; i < 3; i++) {
                v_seed_three[i] = u(gen);
            }
            ARPoly targ_seq(coeff_3, pow_3, u(gen));
            targ_seq.seed_prev_vals(v_seed_three);

            DatasetPoly dat("./ARPoly-1/ARPoly-1-" + std::to_string(type) + 
                "/Sample-" + std::to_string(samp), targ_seq, type);
            dat.write_csv();
        }
    }

    // Non-stationary, non-linear AR process 2 
    for (auto type = 0; type < 5; type++) {
        for (auto samp = 0; samp < utils::N_SAMPLE; samp++) {
            // Seed differently
            for (auto i = 0; i < 3; i++) {
                v_seed_three[i] = u(gen);
            }
            ARPoly targ_seq(coeff_4, pow_4, u(gen));
            targ_seq.seed_prev_vals(v_seed_three);

            DatasetPoly dat("./ARPoly-2/ARPoly-2-" + std::to_string(type) + 
                "/Sample-" + std::to_string(samp), targ_seq, type);
            dat.write_csv();
        }
    }

    return 0;
}
