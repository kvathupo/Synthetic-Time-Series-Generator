#pragma once
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <type_traits>
#include <cassert>
#include <string>
#include <memory>
#include <stdexcept>
#include <boost/multiprecision/cpp_dec_float.hpp> 
#include <boost/random/normal_distribution.hpp>

/*
 *  Standard utility functions and typedefs
 */
namespace utils {

typedef boost::multiprecision::cpp_dec_float_50 my_float;
typedef boost::random::normal_distribution<my_float> normal;


constexpr int TIME_STEP = 100;      // Number of time-steps in each dataset
constexpr int FEAT_COUNT = 25;      // Number of features in each dataset
constexpr int SALIENT_IND = 10;     // Index of the salient feature, across all datasets (same as in deepAR training)
constexpr int N_SAMPLE = 1000;      // Number of datasets per type 
const my_float NORM_VAL = 1;        // Value to which sequences are normalized


/*
 *  Utility functions
 */
// shift vector to right by 1
template<typename T,
    typename = typename std::enable_if<std::is_constructible<T>::value, T>::type>
void shift_vector(std::vector<T>& v) {
    T temp {};
    T prev_val {};

    for (std::size_t i = 0; i < v.size(); i++) {
        temp = v[i];
        v[i] = prev_val;
        prev_val = temp;
    }
}

template<typename T>
T dot_product(const std::vector<T>& v1, const std::vector<T>& v2) {
    assert(v1.size() == v2.size());

    T result = 0;
    for (std::size_t i = 0; i < v1.size(); i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

}
