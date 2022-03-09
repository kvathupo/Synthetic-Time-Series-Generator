#pragma once
#include <array>
#include <map>
#include <vector>
#include <boost/multiprecision/cpp_dec_float.hpp> 
#include <boost/random/normal_distribution.hpp>
#include "GaussSeq.h"
#include "utils.h"
#include "ARSeq.h"
using utils::my_float;


/*
 *  Generates an autoregressive process, given a mapping of lag step to 
 *  coefficient value.
 */
class ARPoly : public ARSeq {
    /*
     *  Member variables
     */
    std::map<int, my_float> powers {};         // Polynomial degrees 

public:
    /*
     *  Constructors
     */
    ARPoly() = default;
    ARPoly(std::map<int, my_float>, std::map<int, my_float>);
    ARPoly(std::map<int, my_float>, std::map<int, my_float>, my_float);

    /*
     *  Member functions
     */
    my_float next() override;                       // Get next value in sequence and update backend
};
