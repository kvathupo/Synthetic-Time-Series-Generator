/*
 *  Test if the compiler-generated copy-assignment works as intended
 *  (deep-copy).
 */

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
//     set precision of output
//    std::streamsize precision = std::numeric_limits<cpp_bin_float_50>::digits10;
//    std::cout << std::setprecision(10);


    // prep
    std::map<int, my_float> coeff {
        {3, 0.5},
        {20, 20},
    };
    std::map<int, my_float> coeff_2 {
        {1, 2},
        {2, 3},
    };
    std::vector<my_float> v;
    for (auto i = 0; i < 20; i++) {
        v.push_back(0);
    }
    v[2] = 2;
    v[19] = 3;

    // decl
    ARSeq seq_1(coeff, 2);
    seq_1.seed_prev_vals(v);

    ARSeq seq_2(coeff_2, 1);

    std::cout << "Pre-copy lags (seq 2)\n";
    seq_2.print_lags();
    std::cout << "Pre-copy past values (seq 2)\n";
    seq_2.print_past_vals();

    seq_2 = seq_1;
    
    for (auto i = 0; i < 100; i++) {
        seq_1.next();
    }

    std::cout << "Lags (seq 1)\n";
    seq_1.print_lags();
    std::cout << "Past values (seq 1)\n";
    seq_1.print_past_vals();
    
    std::cout << "Lags (seq 2)\n";
    seq_2.print_lags();
    std::cout << "Past values (seq 2)\n";
    seq_2.print_past_vals();
    
    return 0;
}
