#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>

#include "GaussSeq.h"
#include "ARSeq.h"
#include "utils.h"

using utils::my_float;

int main() {
    using boost::multiprecision::cpp_bin_float_50;
    using boost::random::uniform_real_distribution;

    boost::random::mt19937 gen {};
    uniform_real_distribution<my_float> u (0, 0.25);

    // set precision of output
//    std::streamsize precision = std::numeric_limits<cpp_bin_float_50>::digits10;
//    std::cout << std::setprecision(10);

    // testing
    std::map<int, my_float> coeff {
        {1, -0.9},
    };
    ARSeq seq(coeff, 100);
    std::vector<my_float> v;
    for (auto i = 0; i < 1; i++) {
        v.push_back(u(gen));
    }

    seq.seed_prev_vals(v);
    
    seq.print_past_vals();
    for (auto i = 0; i < 100; i++) {
        seq.next();
    }
    std::cout << "After 100 iterations\n";
    seq.print_past_vals();
    
    for (auto i = 0; i < 900; i++) {
        seq.next();
    }
    std::cout << "After 1000 iterations\n";
    seq.print_past_vals();

    for (auto i = 0; i < 9000; i++) {
        seq.next();
    }
    std::cout << "After 10000 iterations\n";
    seq.print_past_vals();
    
    return 0;
}
