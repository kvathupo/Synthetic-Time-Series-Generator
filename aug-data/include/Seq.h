#pragma once
#include "utils.h"
using utils::my_float;


/*
 *  Base sequence class that is extended for every variety of sequence.
 */
class Seq {
public:
    /*
     *  Member functions
     */
    virtual my_float next() = 0;        // get next member in sequence

    /*
     *  Constructors and destructors
     */
    virtual ~Seq() = 0;
};
