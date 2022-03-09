#include <cmath>
#include <string>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <boost/multiprecision/cpp_dec_float.hpp> 
#include "ARPoly.h"
#include "GaussSeq.h"
#include "utils.h"
using utils::my_float;


/*
 *  Constructors and destructors
 */
ARPoly::ARPoly(std::map<int, my_float> mp, std::map<int, my_float> powers):
    ARSeq(mp),
    powers{powers}
{}
ARPoly::ARPoly(std::map<int, my_float> mp, std::map<int, my_float> powers, my_float bias):
    ARSeq(mp, bias),
    powers{powers}
{}

/*
 *  Member functions
 */
my_float ARPoly::next() {
    namespace mp = boost::multiprecision;
    std::vector<my_float> copy_prev = prev_val;

    for (const auto& ele : powers) {
        float possible_val = mp::pow(prev_val[ele.first - 1], ele.second).convert_to<float>();
        if (std::fpclassify(possible_val == FP_NAN) {
            throw std::runtime_error("Exponentiation returns complex value!");
        }
        if (std::fabs(possible_val - std::numeric_limits<float>::max()) < std::numeric_limits<float>::epsilon()) {
            throw std::runtime_error("Exponentiation returns infinite value!");
        }
        // subtract one since the zero-index is the previous value
        copy_prev[ele.first - 1] = mp::pow(prev_val[ele.first - 1], ele.second);
    }
    // Since the lag coefficients are only non-zero at non-zero constants, take the dot-product
    my_float result = utils::dot_product(copy_prev, lag_coeff) + g.next() + bias;
    utils::shift_vector(prev_val);
    prev_val[0] = result;
    return result;
}
