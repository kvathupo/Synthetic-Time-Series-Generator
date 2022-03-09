#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>

#include "GaussSeq.h"
#include "ARSeq.h"

using utils::my_float;

int main() {
    using boost::multiprecision::cpp_bin_float_50;

    // set precision of output
//    std::streamsize precision = std::numeric_limits<cpp_bin_float_50>::digits10;
//    std::cout << std::setprecision(10);

    // testing
    std::map<int, my_float> coeff {
        {3, 0.5},
        {20, 20},
    };
    ARSeq seq(coeff, 1);
    seq.print_lags();
    std::vector<my_float> v;
    for (auto i = 0; i < 20; i++) {
        v.push_back(0);
    }
    v[2] = 2;
    v[19] = 3;

    seq.seed_prev_vals(v);
    
    seq.print_past_vals();
    for (auto i = 0; i < 100; i++) {
        seq.next();
    }
    seq.print_past_vals();
    
    
    return 0;
}
