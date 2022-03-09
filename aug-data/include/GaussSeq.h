#pragma once
#include <boost/multiprecision/cpp_dec_float.hpp> 
#include <boost/random/normal_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "utils.h"
#include "Seq.h"
using utils::my_float;
using utils::normal;


/*
 *  Generates a Gaussian sequence
 */ 

class GaussSeq : public Seq {
private:
    /*
     *  Member variables
     */
    static boost::random::mt19937 gen;
    normal n {};

public:
    /*
     *  Constructors and destructors
     */
    GaussSeq() = default;           // Distrib mean = 0, std = 1
    GaussSeq(my_float, my_float);   // Distrib mean and std

    /*
     *  Member functions
     */
    my_float next() override {
        return n(gen);
    }
};
