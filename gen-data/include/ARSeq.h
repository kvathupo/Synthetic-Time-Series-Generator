#pragma once
#include <array>
#include <map>
#include <vector>
#include <boost/multiprecision/cpp_dec_float.hpp> 
#include <boost/random/normal_distribution.hpp>
#include "GaussSeq.h"
#include "utils.h"
#include "Seq.h"
using utils::my_float;


/*
 *  Generates an autoregressive process, given a mapping of lag step to 
 *  coefficient value.
 */
class ARSeq : public Seq {
protected:
    /*
     *  Member variables
     */
    std::vector<my_float> lag_coeff {};     // Lag coefficients
    std::vector<my_float> prev_val {};      // Previous values
    my_float bias {};                       // Bias term
    static GaussSeq g;                      // Error term

public:
    /*
     *  Constructors
     */
    ARSeq() = default;
    ARSeq(std::map<int, my_float>);
    ARSeq(std::map<int, my_float>, my_float);

    /*
     *  Member functions
     */
    my_float next() override;                       // Get next value in sequence and update backend
    void seed_prev_vals(std::vector<my_float>);     // Explicitly set previous values

    // get member variables
    std::vector<my_float> get_prev_val() {
        return this->prev_val;
    }

    // debugging functions
    void print_lags();
    void print_past_vals(); 
};
