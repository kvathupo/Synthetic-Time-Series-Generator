#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>

#include "DatasetAR.h"
#include "GaussSeq.h"
#include "ARSeq.h"
#include "utils.h"

using utils::my_float;

int main() {
    using boost::multiprecision::cpp_bin_float_50;
    using boost::random::uniform_real_distribution;

    boost::random::mt19937 gen {};
    uniform_real_distribution<my_float> u (0, 4);

    // prepare target
    std::map<int, my_float> coeff {
        {3, 0.2},
        {20, 0.5},
    };
    std::vector<my_float> v;
    for (auto i = 0; i < 20; i++) {
        v.push_back(u(gen));
    }

    // AR process
    ARSeq targ_seq(coeff, 0);
    targ_seq.seed_prev_vals(v);

    // Dataset write
    DatasetAR dat_0("testing_zero_background", targ_seq, 0);
    DatasetAR dat_1("testing_one_background", targ_seq, 1);
    DatasetAR dat_2("testing_two_background", targ_seq, 2);
    DatasetAR dat_3("testing_three_background", targ_seq, 3);
    DatasetAR dat_4("testing_four_background", targ_seq, 4);

    dat_0.write_csv();
    dat_1.write_csv();
    dat_2.write_csv();
    dat_3.write_csv();
    dat_4.write_csv();
    
    return 0;
}
