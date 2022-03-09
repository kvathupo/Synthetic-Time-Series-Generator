#include "ARSeq.h"
#include "GaussSeq.h"
#include "utils.h"


/*
 *  Member variables
 */
GaussSeq ARSeq::g {};       // static generator

/*
 *  Constructors and destructors
 */
ARSeq::ARSeq(std::map<int, my_float> mp) {
    int max_lag = 0;

    for (const auto& ele : mp) {
        if (ele.first > max_lag)
            max_lag = ele.first;
    }
    for (auto i = 0; i < max_lag; i++) {
        lag_coeff.push_back(mp[i + 1]);
        prev_val.push_back(0);
    }
}
ARSeq::ARSeq(std::map<int, my_float> mp, my_float bias):
    bias{bias}
{
    int max_lag = 0;

    for (const auto& ele : mp) {
        if (ele.first > max_lag)
            max_lag = ele.first;
    }
    for (auto i = 0; i < max_lag; i++) {
        lag_coeff.push_back(mp[i + 1]);
        prev_val.push_back(0);
    }
}

/*
 *  Member functions
 */
void ARSeq::print_lags() {
    for (const auto& ele : this->lag_coeff) {
        std::cout << ele << ", ";
    }
    std::cout << "\n";
}
void ARSeq::print_past_vals() {
    for (const auto& ele : this->prev_val) {
        std::cout << ele << ", ";
    }
    std::cout << "\n";
}
my_float ARSeq::next() {
    my_float result = utils::dot_product(this->prev_val, this->lag_coeff) + g.next() + this->bias;
    utils::shift_vector(this->prev_val);
    prev_val[0] = result;
    return result;
}
void ARSeq::seed_prev_vals(std::vector<my_float> v) {
    assert(v.size() == this->prev_val.size());

    this->prev_val = std::move(v);
}
