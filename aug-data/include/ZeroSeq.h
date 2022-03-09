#pragma once
#include "Seq.h"
#include "utils.h"
using utils::my_float;


/* 
 *  Generator for a sequence of zeros.
 */
class ZeroSeq : public Seq {
    /*
     *  Member functions
     */
    my_float next() override {
        return 0;
    }
};
