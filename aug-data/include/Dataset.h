#pragma once
#include <boost/random/mersenne_twister.hpp>


/*
 *  Base Dataset class that is extended for every variety of Dataset.
 */
class Dataset {
public:
    /* 
     *  Constructors and destructors
     */
    virtual ~Dataset() = 0;         // Remember to define pure virtual destructor!

    /*
     *  Member functions
     */
    virtual void write_csv() = 0;
    virtual void set_noise(unsigned char) = 0;
};
