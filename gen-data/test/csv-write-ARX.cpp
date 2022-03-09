#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>

#include "DatasetAR.h"
#include "DatasetARX.h"
#include "GaussSeq.h"
#include "ARSeq.h"
#include "utils.h"

using utils::my_float;

int main() {
    using boost::multiprecision::cpp_bin_float_50;
    using boost::random::uniform_real_distribution;

    // Dataset write
    DatasetARX dat_1("testing_one_background", 1);
    DatasetARX dat_2("testing_two_background", 2);
    DatasetARX dat_2_2("testing_two_background_2", 2);
    DatasetARX dat_3("testing_three_background", 3);
    DatasetARX dat_3_2("testing_three_background_2", 3);
    DatasetARX dat_4("testing_four_background", 4);
    DatasetARX dat_4_2("testing_four_background_2", 4);

    dat_1.write_csv();
    dat_2.write_csv();
    dat_2_2.write_csv();
    dat_3.write_csv();
    dat_3_2.write_csv();
    dat_4.write_csv();
    dat_4_2.write_csv();
    
    return 0;
}
