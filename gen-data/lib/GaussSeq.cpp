#include "GaussSeq.h"
#include "utils.h"
#include <boost/random/mersenne_twister.hpp>
using utils::normal;
using utils::my_float;


/*
 *  Member variables
 */
boost::random::mt19937 GaussSeq::gen {};        // define static generator

/*
 *  Constructors and destructors
 */
GaussSeq::GaussSeq(my_float mean, my_float std) {
    normal new_n(mean, std);
    this->n = new_n;
}
