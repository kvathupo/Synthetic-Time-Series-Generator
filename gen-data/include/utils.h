#pragma once
#include <numeric>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <cassert>
#include <boost/multiprecision/cpp_dec_float.hpp> 
#include <boost/random/normal_distribution.hpp>


/*
 *  Custom template traits
 */
namespace chcks {
template <typename T>
struct is_boost_float {
    static const bool value = false;
};

template <unsigned N>
struct is_boost_float<boost::multiprecision::number<boost::multiprecision::backends::cpp_dec_float<N>>> {
    static const bool value = true;
};
}

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
template<typename T>
void shift_vector(std::vector<T>& v) {
    std::rotate(v.rbegin(), v.rbegin() + 1, v.rend());
}

template<typename T, typename = typename std::enable_if<
    std::is_arithmetic<T>::value || chcks::is_boost_float<T>::value, 
    void>::type>
T dot_product(const std::vector<T>& v1, const std::vector<T>& v2) {
    assert(v1.size() == v2.size())
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), T(0));
}

}
